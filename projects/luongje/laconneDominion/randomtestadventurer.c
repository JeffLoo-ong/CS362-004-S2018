#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>


int main()
{

	struct gameState S;
	struct gameState OriginalS;

	int k[10] = {adventurer, council_room, feast, gardens, mine, 
				remodel, smithy, village, baron, great_hall};

	int playerCount;
	int player = 0;
	int seed = 500;
	int minNum;
	int maxNum;
	int range;
	int bonus = 0;
	int iterations = 50000;

	int preTotalCards;
	int postTotalCards;
	int preTreasureCards;
	int postTreasureCards;
	int kingCardsCheck;

	int totalCardsFailCount =0;
	int handFailCount = 0;
	int treasureFailCount = 0;
	int victoryPileFailCount = 0;
	int kingCardsFailCount = 0;
	int testFailure;

	srand(time(NULL));
	printf("\n----------------------------------------------------------\n");
	printf("----------------- Testing Adventurer Card ----------------\n");
	printf("----------------------------------------------------------\n");

	int x;
	for(x = 0; x < iterations; x++)
	{

		playerCount = (rand() % (MAX_PLAYERS - 2 + 1)) + 2;

		initializeGame(playerCount, k, seed, &S);

		minNum = 3;
		maxNum = MAX_DECK;
		range = maxNum - minNum;

		S.deckCount[player] = (rand() % (range + 1)) + minNum;

		S.handCount[player] = (rand() % (S.deckCount[player] + 1));


		int i;

		for(i=0; i<S.deckCount[0]; i++)
		{
			int randCard = rand() % 10;

			if (i == 0)
			{
				S.deck[player][i] = copper;
			}
			else if (i == 1)
			{
				S.deck[player][i] = silver;
			}
			else if (i == 2)
			{
				S.deck[player][i] = gold;
			}
			else
			{
				S.deck[player][i] = k[randCard];
			}

		}


		shuffle(player, &S);

		OriginalS = S;

		cardEffect(adventurer, 0, 0, 0, &S, 0, &bonus);

		
		preTotalCards = 0;
		postTotalCards = 0;
		preTreasureCards = 0;
		postTreasureCards = 0;

		//fails 1
		preTotalCards = OriginalS.deckCount[player] + OriginalS.discardCount[player] + OriginalS.handCount[player];
		postTotalCards = S.deckCount[player] + S.discardCount[player] + S.handCount[player];

		if (preTotalCards != postTotalCards)
			totalCardsFailCount++;

		//fails 2
		if (OriginalS.handCount[player] + 2 != S.handCount[player])
			handFailCount++;

		//fails 3
		for(i = 0; i < OriginalS.handCount[player]; i++)
		{
			if(OriginalS.hand[player][i] == copper
				|| OriginalS.hand[player][i] == silver
				|| OriginalS.hand[player][i] == gold)
			{
				preTreasureCards++;
			}
		}

		for(i = 0; i < S.handCount[player]; i++)
		{
			if(S.hand[player][i] == copper
				|| S.hand[player][i] == silver
				|| S.hand[player][i] == gold)
			{
				postTreasureCards++;
			}
		}


		if (preTreasureCards + 2 != postTreasureCards)
			treasureFailCount++;

		//fails 4
		if(OriginalS.supplyCount[province] != S.supplyCount[province] 
			|| OriginalS.supplyCount[duchy] != S.supplyCount[duchy]
			|| OriginalS.supplyCount[estate] != S.supplyCount[estate])
		{
			victoryPileFailCount++;
		}

		//fails 5
		kingCardsCheck = 0;
		for (i=0; i < 10; i++)
	    {
	    	
	    	if (OriginalS.supplyCount[k[i]] != S.supplyCount[k[i]])
	    		kingCardsCheck++;
	    	
	    }

	    if(kingCardsCheck)
	    	kingCardsFailCount++;
	}

	//Count up all test failures
	testFailure = totalCardsFailCount + handFailCount + treasureFailCount + victoryPileFailCount + kingCardsFailCount;

	if (testFailure != 0)
	{
		printf("\n----- TEST FAILED -----\n\n");
		printf("Number of iterations: %d\n\n", iterations);
		printf("Total cards count fails: %d\n", totalCardsFailCount);
		printf("Hand count fails: %d\n", handFailCount);
		printf("Treasure count fails: %d\n", treasureFailCount);
		printf("Victory Pile count fails: %d\n", victoryPileFailCount);
		printf("Kingdom Pile count fails: %d\n", kingCardsFailCount);
		printf("\n\n");
	}
	else
	{
		printf("\n----- TEST SUCCESSFUL -----\n\n");
		printf("Number of iterations: %d\n\n", iterations);
		printf("NO FAILURES");
		printf("\n\n");
	}


	return 0;
}