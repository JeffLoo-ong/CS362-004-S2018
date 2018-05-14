/* -----------------------------------------------------------------------
 * Random testing for Adventurer card
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "myAssert.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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
    int deckSize, handSize, potentialGoldCard, numCoinCardsBefore, 
        numCoinCardsAfter, randomGameCard, discardedCoinCount;
    int b, i, x;    // Iterators

    // Test counters
    int testsPassed = 0;
    int drawTestsFailed = 0;
    int discardTestsFailed = 0;
    
    int allTestsPassed = 1; // Bool for all tests passing or any failures

    srand(time(NULL));
    
    for(i = 0; i < TOTAL_RUNS; i++){
        // Reset Coin Cards Before
        numCoinCardsBefore = 0;
        
        initializeGame(NUM_PLAYERS, k, SEED_VAL, &G);
        
        // Adding variability to deck size
        deckSize = rand() % (MAX_DECK + 1);

        // Adding variability to handsize as this matters for Adventurer Card
        handSize = rand() % (deckSize + 1);
        
        // Init player one's deck and hand
        G.deckCount[0] = deckSize - handSize;
        G.handCount[0] = handSize;
        
        // Fill player one's deck with a random number of gold cards or cards 
        // available in the game
        for(b = 0;b < G.deckCount[curPlayer]; b++)
        {
            potentialGoldCard = rand() % (60 + 1); // Chosen to give a 5% chance of adding a coin card
            randomGameCard = rand() % (NUM_GAME_CARDS); // Select a random card from the possible game cards
            
            switch(potentialGoldCard)
            {
                case 1:
                    G.deck[curPlayer][b] = copper;
                    break;
                case 2:
                    G.deck[curPlayer][b] = silver;
                    break;
                case 3:
                    G.deck[curPlayer][b] = gold;
                    break;
                // Take a card from the possible game cards
                default:
                    G.deck[curPlayer][b] = k[randomGameCard];
                    break;
            } // switch
        } // for
        
        // Determine number of coin cards in hand before Adventurer Card is played
        for(x = 0; x < G.handCount[curPlayer]; x++){
            if(G.hand[curPlayer][x] == copper || G.hand[curPlayer][x] == silver || G.hand[curPlayer][x] == gold){
                numCoinCardsBefore++;
            }
        }

        // Play card
        AdventurerCard(curPlayer, &G);   
        
        // Reset Coin Cards After
        numCoinCardsAfter = 0;
        
        // Determine number of coin cards in hand after Adventurer Card is played
        for(x = 0; x < G.handCount[curPlayer]; x++){
            if(G.hand[curPlayer][x] == copper || G.hand[curPlayer][x] == silver || G.hand[curPlayer][x] == gold){
                numCoinCardsAfter++;
            }
        }
       
        // Reset Discarded Coin Card Counts
        discardedCoinCount = 0;
        
        // Count all the coins in the discard pile. There should be none here
        // This would indicate an error in the adventurer card since you should 
        // only ever discard NON-coin cards.
        for(x = 0; x < G.discardCount[curPlayer]; x++){
            if(G.discard[curPlayer][x] == copper) {
                discardedCoinCount++;
            } else if(G.discard[curPlayer][x] == silver) {
                discardedCoinCount++;
            } else if(G.discard[curPlayer][x] == gold) {
                discardedCoinCount++;
            }
        }

        // Case 1: Make sure we don't draw more than 2 coin cards
        printf("Coin card count - Actual: %d, Expected: %d\n", 
            numCoinCardsAfter, numCoinCardsBefore + 2);
        myAssert(numCoinCardsAfter ==  numCoinCardsBefore + 2, "Test Case 1");
        
        // Case 2: Make sure we don't end up discarding coin cards since we only draw 2 of them
        printf("Discarded coin count - Actual: %d, Expected: %d\n", 
            discardedCoinCount, 0);
        myAssert(discardedCoinCount == 0, "Test Case 2");

        if(allTestsPassed == 1){
            printf("All Tests: Passed\n");
            testsPassed++;
        }
   } // for
   
   printf("-----------------------------------------\n");
   printf("# of Tests Passed: %d\n", testsPassed);
   printf("# of Cards Drawn To Hand Failed: %d\n", drawTestsFailed);
   printf("# of Smithy Discarded Fails: %d\n\n", discardTestsFailed);
   
   return 0;
} // main()