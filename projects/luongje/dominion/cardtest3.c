/* -----------------------------------------------------------------------
 * Test file for Adventurer card
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
    int testHand[10] = {adventurer, smithy, smithy, smithy, smithy, smithy, smithy, smithy, smithy, smithy}; 
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    struct gameState testG;
    int NUM_PLAYERS = 2;
    int MAX_HAND_COUNT = 10;
    int ADVENTURER_VAL = 7;
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

    printf ("TESTING Adventurer Card:\n");

    handVal = handCard(0, &testG);
    cardEffect(adventurer, -1, -1, -1, &testG, 0, 0);

#if (NOISY_TEST == 1)
    printf("Adventurer Card Played - Value = %d, expected = %d\n", handVal, ADVENTURER_VAL);
    printf("Coins = %d, expected = %d\n", testG.coins, G.coins);
    printf("Player Num Actions - numActions = %d, expected = %d\n", testG.numActions, G.numActions);
    printf("Player Hand Count - handCount = %d, expected = %d\n", numHandCards(&testG), numHandCards(&G) + 2);
    printf("First Drawn Card Value - Value = %d, expected = 4,5,or 6\n", testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1]);
    printf("Second Drawn Card Value - Value = %d, expected = 4,5,or 6\n", testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2]);
#endif        
    assert(handVal == ADVENTURER_VAL);    
    assert(testG.coins == G.coins);
    assert(testG.numActions == G.numActions);
    assert(numHandCards(&testG) == numHandCards(&G) + 2);
    assert(testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == copper 
        || testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == silver
        || testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == gold);
    assert(testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2] == copper 
        || testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2] == silver
        || testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2] == gold);
    printf("All tests passed!\n");

    return 0;
}