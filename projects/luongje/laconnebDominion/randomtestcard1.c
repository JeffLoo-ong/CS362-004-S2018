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
	int kingCardsCheck;

	int totalCardsFailCount =0;
	int handFailCount = 0;
	int deckFailCount = 0;
	int actionsFailCount = 0;
	int victoryPileFailCount = 0;
	int kingCardsFailCount = 0;
	int testFailure;

	srand(time(NULL));
	printf("\n----------------------------------------------------------\n");
	printf("----------------- Testing Great Hall Card ----------------\n");
	printf("----------------------------------------------------------\n");

	int x;
	for(x = 0; x < iterations; x++)
	{

		playerCount = (rand() % (MAX_PLAYERS - 2 + 1)) + 2;

		initializeGame(playerCount, k, seed, &S);

		minNum = 1;
		maxNum = MAX_DECK;
		range = maxNum - minNum;

		S.deckCount[0] = (rand() % (range + 1)) + minNum;

		S.handCount[player] = (rand() % (S.deckCount[player] + 1));

		int i;

		for(i=0; i<S.deckCount[0]; i++)
		{
			
			int randCard = rand() % 10;

			S.deck[player][i] = k[randCard];	

		}

		shuffle(player, &S);

		OriginalS = S;

		cardEffect(great_hall, 0, 0, 0, &S, 0, &bonus);


		preTotalCards = 0;
		postTotalCards = 0;


		//fails 1
		preTotalCards = OriginalS.deckCount[player] - 1  + OriginalS.discardCount[player] + OriginalS.handCount[player];
		postTotalCards = S.deckCount[player] + S.discardCount[player] + S.handCount[player];

		if (preTotalCards != postTotalCards)
			totalCardsFailCount++;

		//fails 2
		//hand count should be the same as before because you discard a card and draw a card
		if (OriginalS.handCount[player] != S.handCount[player])
			handFailCount++;

		//fails 3
		if (OriginalS.deckCount[player] - 1  != S.deckCount[player])
			deckFailCount++;

		//fails 4
		if(OriginalS.numActions + 1 != S.numActions)
			actionsFailCount++;

		//fails 5
		if(OriginalS.supplyCount[province] != S.supplyCount[province] 
			|| OriginalS.supplyCount[duchy] != S.supplyCount[duchy]
			|| OriginalS.supplyCount[estate] != S.supplyCount[estate])
		{
			victoryPileFailCount++;
		}

		//fails 6
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
	testFailure = totalCardsFailCount + handFailCount + deckFailCount + actionsFailCount + victoryPileFailCount + kingCardsFailCount;

	if (testFailure != 0)
	{
		printf("\n----- TEST FAILED -----\n\n");
		printf("Number of iterations: %d\n\n", iterations);
		printf("Total cards count fails: %d\n", totalCardsFailCount);
		printf("Hand count fails: %d\n", handFailCount);
		printf("Deck count fails: %d\n", deckFailCount);
		printf("Actions count fails: %d\n", actionsFailCount);
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