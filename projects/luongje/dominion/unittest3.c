/* -----------------------------------------------------------------------
 * Unit test for fullDeckCount()
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "myAssert.h"
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i, r;
    int seed = 1234;
    int NUM_PLAYERS = 2;
    int testHand[5] = {duchy, duchy, duchy, smithy, smithy};
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int MAX_HAND_COUNT = 5;
    int DUTCHY_VAL = 2;
    int SMITHY_VAL = 13;

    // Initialize game state
    memset(&G, 23, sizeof(struct gameState)); // Clear game state
    r = initializeGame(NUM_PLAYERS, k, seed, &G); // Initialize a new game
    myAssert(r = 0, "initializeGame");
    // Fill both players hands with the testHand cards
    for(i = 0; i < 2 ; i++){
        G.handCount[i] = MAX_HAND_COUNT;
        memcpy(G.hand[i], testHand, sizeof(int) * MAX_HAND_COUNT);
    }

    printf ("\nTESTING fullDeckCount():\n");
    
    // Case 1: Check that there are 3 dutchy and 2 smithy 
    // cards total when discard and deck are empty
#if (NOISY_TEST == 1)
    printf("1. Hand only - Dutchy = %d, Smithy = %d, expected = %d, %d \n", fullDeckCount(0,DUTCHY_VAL, &G), fullDeckCount(0,SMITHY_VAL, &G), 3, 2);
#endif        
    myAssert(fullDeckCount(0,DUTCHY_VAL, &G) == 3, "Test Case 1 (Duchy)");
    myAssert(fullDeckCount(0,SMITHY_VAL, &G) == 2, "Test Case 1 (Smithy)");

    // Case 2: Check that having cards in discard increase the count
    // Add 2 cards to dicard pile, Dutchy and Smithy
    G.discardCount[0] = 2;
    G.discard[0][0] = DUTCHY_VAL;
    G.discard[0][1] = SMITHY_VAL;
    
#if (NOISY_TEST == 1)
    printf("2. Hand + Discard - Dutchy = %d, Smithy = %d, expected = %d, %d \n", fullDeckCount(0,DUTCHY_VAL, &G), fullDeckCount(0,SMITHY_VAL, &G), 4, 3);
#endif        
    myAssert(fullDeckCount(0,DUTCHY_VAL, &G) == 4, "Test Case 2 (Duchy)");
    myAssert(fullDeckCount(0,SMITHY_VAL, &G) == 3, "Test Case 2 (Smithy)");

    // Case 3: Check that having cards in deck increase the count
    // Add 2 cards to deck pile, Dutchy and Smithy
    G.deckCount[0] = 2;
    G.deck[0][0] = DUTCHY_VAL;
    G.deck[0][1] = SMITHY_VAL;
    
#if (NOISY_TEST == 1)
    printf("3. Hand + Discard + Deck - Dutchy = %d, Smithy = %d, expected = %d, %d \n", fullDeckCount(0,DUTCHY_VAL, &G), fullDeckCount(0,SMITHY_VAL, &G), 5, 4);
#endif        
    myAssert(fullDeckCount(0,DUTCHY_VAL, &G) == 5, "Test Case 3 (Duchy)");
    myAssert(fullDeckCount(0,SMITHY_VAL, &G) == 4, "Test Case 3 (Smithy)");

    printf("\nAll tests passed!\n");

    return 0;
}