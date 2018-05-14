/* -----------------------------------------------------------------------
 * Random testing for Smithy card
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_RUNS 1000000
#define NUM_GAME_CARDS 10
#define NUM_PLAYERS 2
#define SEED_VAL 12345

int main() {
	
    struct gameState G;
    int curPlayer = 0;
	int k[NUM_GAME_CARDS] = { adventurer, great_hall, village, ambassador, mine, 
            gardens, tribute, baron, smithy, steward };  
    int deckSize, handSize, handPos;
    int deckCountBefore, handCountBefore, cardsPlayedCountBefore;
    int deckCountAfter, handCountAfter, cardsPlayedCountAfter;
    int i;
    int deckCountFailure = 0;
    int handCountFailure = 0;
    int discardCountFailure = 0;
    int testsPassed = 0;
    int passed = 1;
    
    srand(time(NULL));

    for(i = 0; i < TOTAL_RUNS; i++){
        initializeGame(NUM_PLAYERS, k, SEED_VAL, &G);
        // Adding variability to deck size
        deckSize = rand() % (MAX_DECK + 1);

        // Adding variability to handsize as this matters for Adventurer Card
        handSize = rand() % (deckSize + 1);
      
        // Init player one's deck and hand
        G.deckCount[0] = deckSize - handSize;
        G.handCount[0] = handSize;
        
        // Set the current hand position to the last card in the player's hand
        handPos = G.hand[curPlayer][G.handCount[curPlayer] - 1];

        // Set Before values 
        deckCountBefore = G.deckCount[0];
        handCountBefore = G.handCount[0];
        cardsPlayedCountBefore = G.playedCardCount;
        
        // Play Smithy Card
        SmithyCard(curPlayer, &G, handPos);
        
        // Obtain values of deck, hand, and cards played after Smithy effect
        deckCountAfter = G.deckCount[0];
        handCountAfter = G.handCount[0];
        cardsPlayedCountAfter = G.playedCardCount;
        
        // 1) Make sure we don't play more than 1 card
        if(cardsPlayedCountAfter != (cardsPlayedCountBefore + 1))
        {
            printf("Fail: Should only discard one card after play\n");
            discardCountFailure++;
            passed = 0;
        }

        // 2) Make sure we only take 3 cards from the deck
        if(deckCountAfter < (deckCountBefore - 3))
        {
            printf("Fail: Too many cards removed from deck\n");
            deckCountFailure++;
            passed = 0;
        } 
        else if(deckCountAfter > (deckCountBefore - 3))
        {
            printf("Fail: Too little cards removed from deck\n");
            deckCountFailure++;
            passed = 0;
        }

        // 3) Make sure we add only add 2 cards into hand 
        if(handCountAfter < (handCountBefore + 2))
        {
            printf("Fail: Too few cards drawn\n");
            handCountFailure++;
            passed = 0;
        }
        else if (handCountAfter > (handCountBefore + 2))
        {
            printf("Fail: Too many cards drawn\n");
            handCountFailure++;
            passed = 0;
        }
        
        if(passed == 1){
            printf("All Tests Passed!! Horray lucky us!\n");
            testsPassed++;
        }
    }
        
   printf("\n");
   printf("# of Tests Passed: %d\n", testsPassed);
   printf("# of Cards Drawn To Hand Fails: %d\n", handCountFailure);
   printf("# of Cards Discarded Fails: %d\n", discardCountFailure);        
   
   return 0;
}