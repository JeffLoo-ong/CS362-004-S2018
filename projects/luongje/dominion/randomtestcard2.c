/* -----------------------------------------------------------------------
 * Random testing for Vilage card
 * -----------------------------------------------------------------------
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "myAssert.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TOTAL_RUNS 1000000

int main() {
    int a, i, n;
    int curPlayer = 0;
    int handPos = 0;
    int result;
    int discardCount = 0;
	struct gameState G;
    struct gameState testG;
    
    for (n = 0; n < TOTAL_RUNS; n++) {

        // Create a Random game state
        for (i = 0; i < sizeof(struct gameState); i++) {
          ((char*)&G)[i] = floor(Random() * 256);
        }

        // Set the hand and decks
        int deckSize = rand() % (MAX_DECK + 1);
        int handSize = rand() % (deckSize + 1);
        
        // Reset values to watch to 0;
        G.discardCount[curPlayer] = 0;
        G.playedCardCount = 0;
        G.numActions = 0;

		G.deckCount[curPlayer] = deckSize;
		G.handCount[curPlayer] = deckSize;
        
        // Fill deck and hand with random playable cards
		for(a = 0; a < deckSize; a++)
            G.deck[curPlayer][a] = floor(Random() * (treasure_map + 1));

		for(a = 0; a < handSize; a++)
            G.hand[curPlayer][a] = floor(Random() * (treasure_map + 1));

        // Set first card in hand as village card
        G.hand[curPlayer][0] = village;

        // Copy regular game state into test 
        memcpy (&testG, &G, sizeof(struct gameState));

        result = VillageCard(curPlayer, &testG, handPos);

        // Artificially play Village card and simulate some effects
        drawCard(curPlayer, &G);
        G.numActions += 2;
        discardCard(0, curPlayer, &G, 0);
        discardCount++;

        // BEGIN TEST CASES
        // Case 0: Village card returns 0
        myAssert (result == 0, "Test Case 0");

        // Case 1: Discarded card is Village card
        printf("Discarded card value - Actual: %d, Expected: %d\n", 
            testG.playedCards[testG.playedCardCount - 1], village);
        myAssert(testG.playedCards[testG.playedCardCount - 1] == village, "Test Case 1");
        
        // Case 2: Actions left 
        printf("Action(s) count - Actual: %d, Expected: %d\n", 
            testG.numActions, G.numActions + 1);
        myAssert(testG.numActions != G.numActions + 1, "Test Case 2");

        // Case 3: Discarded cards
        printf("Discarded card count - Actual: %d, Expected: %d\n", 
            testG.playedCardCount, G.playedCardCount);
        myAssert(testG.playedCardCount == G.playedCardCount, "Test Case 3");
        
        // Case 4: Cards in hand 
        printf("Cards in hand - Actual: %d, Expected: %d\n", 
            testG.handCount[curPlayer], G.handCount[curPlayer]);
        myAssert(testG.handCount[curPlayer] == G.handCount[curPlayer], "Test Case 4");

        // Case 5: Cards in discard pile
        printf("Cards in discard pile - Actual: %d, Expected: %d\n", 
            testG.discardCount[curPlayer], G.discardCount[curPlayer]);
        myAssert(testG.discardCount[curPlayer] == G.discardCount[curPlayer], 
            "Test Case 5");
        
        // Case 6: Cards in deck
        printf("Cards in deck - Actual: %d, Expected: %d\n", 
            testG.deckCount[curPlayer], G.deckCount[curPlayer]);
        myAssert(testG.deckCount[curPlayer] == G.deckCount[curPlayer], "Test Case 6");
        // END TEST CASES
    } // for
	return 0;
} // main()