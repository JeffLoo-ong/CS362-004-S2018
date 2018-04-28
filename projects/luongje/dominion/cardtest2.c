/* -----------------------------------------------------------------------
 * Test file for Smithy card
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i, r, handVal;
    int seed = 1234;
    // Create preset hand for player
    int testHand[10] = {smithy, smithy, smithy, smithy, smithy, smithy, smithy, smithy, smithy, smithy}; 
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    struct gameState testG;
    int NUM_PLAYERS = 2;
    int MAX_HAND_COUNT = 10;
    int SMITHY_VAL = 13;
    int thisPlayer = 0;

    // Initialize game state
    r = initializeGame(NUM_PLAYERS, k, seed, &G); // Initialize a new game
    assert(r == 0);

    // Fill both players hands with the testHand cards
    for(i = 0; i < 2 ; i++){
        G.handCount[i] = MAX_HAND_COUNT;
        memcpy(G.hand[i], testHand, sizeof(int) * MAX_HAND_COUNT);
    }

    memcpy(&testG, &G, sizeof(struct gameState)); // Copy game state into test state

    printf ("TESTING Smithy Card:\n");

    handVal = handCard(0, &testG);
    cardEffect(smithy, -1, -1, -1, &testG, 0, 0);

#if (NOISY_TEST == 1)
    printf("Smithy Card Played - Value = %d, expected = %d\n", handVal, SMITHY_VAL);
    printf("Coins = %d, expected = %d\n", testG.coins, G.coins);
    printf("Player Num Actions - numActions = %d, expected = %d\n", testG.numActions, G.numActions);
	printf("Deck Count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 3);
    printf("Player Hand Count - handCount = %d, expected = %d\n", numHandCards(&testG), numHandCards(&G) + 3);
#endif        
    assert(handVal == SMITHY_VAL);    
    assert(testG.coins == G.coins);
    assert(testG.numActions == G.numActions);
    assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 3);
    assert(numHandCards(&testG) == numHandCards(&G) + 3);

    printf("All tests passed!\n");

    return 0;
}