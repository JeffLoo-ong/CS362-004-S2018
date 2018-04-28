/* -----------------------------------------------------------------------
 * Test file for Mine card
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
    int testHand[10] = {mine, copper, silver, gold, smithy, smithy, smithy, smithy, smithy, smithy}; 
    // Indices for the money cards
    int copperPosition = 1;
    int silverPosition = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine, 
                    remodel, smithy, village, baron, great_hall};
    struct gameState G;
    struct gameState testG;
    int NUM_PLAYERS = 2;
    int MAX_HAND_COUNT = 10;
    int MINE_VAL = 11;

    // Initialize game state
    r = initializeGame(NUM_PLAYERS, k, seed, &G); // Initialize a new game
    assert(r == 0);

    // Fill both players hands with the testHand cards
    for(i = 0; i < 2 ; i++){
        G.handCount[i] = MAX_HAND_COUNT;
        memcpy(G.hand[i], testHand, sizeof(int) * MAX_HAND_COUNT);
    }

    memcpy(&testG, &G, sizeof(struct gameState)); // Copy game state into test state

    printf ("TESTING Mine Card:\n");

    handVal = handCard(0, &testG);

    // Case 1: Upgrade a copper to a silver coin
    printf ("Test 1: Updating Copper --> Silver\n");
    cardEffect(mine, copperPosition, silver, -1, &testG, copperPosition, 0);
    updateCoins(testG.whoseTurn, &testG, 0);
#if (NOISY_TEST == 1)
    printf("Mine Card Played - Value = %d, expected = %d\n", handVal, MINE_VAL);
    printf("Coins = %d, expected = %d\n", testG.coins, G.coins + 2);
    printf("Player Num Actions - numActions = %d, expected = %d\n", testG.numActions, G.numActions);
    printf("Player Hand Count - handCount = %d, expected = %d\n", numHandCards(&testG), numHandCards(&G));
#endif        
    assert(handVal == MINE_VAL);    
    assert(testG.coins == G.coins + 2);
    assert(testG.numActions == G.numActions);
    assert(numHandCards(&testG) == numHandCards(&G));

    // Case 2: Upgrade a silver to a gold coin
    printf ("Test 2: Updating Silver --> Gold\n");
    cardEffect(mine, silverPosition, gold, -1, &testG, silverPosition, 0);
    updateCoins(testG.whoseTurn, &testG, 0);
#if (NOISY_TEST == 1)
    printf("Mine Card Played - Value = %d, expected = %d\n", handVal, MINE_VAL);
    printf("Coins = %d, expected = %d\n", testG.coins, G.coins + 3);
    printf("Player Num Actions - numActions = %d, expected = %d\n", testG.numActions, G.numActions);
    printf("Player Hand Count - handCount = %d, expected = %d\n", numHandCards(&testG), numHandCards(&G));
#endif        
    assert(handVal == MINE_VAL);    
    assert(testG.coins == G.coins + 3);
    assert(testG.numActions == G.numActions);
    assert(numHandCards(&testG) == numHandCards(&G));

    printf("All tests passed!\n");

    return 0;
}