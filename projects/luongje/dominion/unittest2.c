/* -----------------------------------------------------------------------
 * Unit test for playCard()
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
// #define SMITHY_COST = 4
// #define VILLAGE_COST = 3

int main() {
    int i, r, handVal;
    int seed = 1234;
    // Create preset hand for player
    int testHand[5] = {village, village, duchy, village, village}; 
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    struct gameState testG;
    int NUM_PLAYERS = 2;
    int MAX_HAND_COUNT = 5;
    
    // Initialize game state
    memset(&G, 23, sizeof(struct gameState)); // Clear game state
    r = initializeGame(NUM_PLAYERS, k, seed, &G); // Initialize a new game

    // Fill both players hands with the testHand cards
    // Give both Players COIN_BONUS coins to buy with
    for(i = 0; i < 2 ; i++){
        G.handCount[i] = MAX_HAND_COUNT;
        memcpy(G.hand[i], testHand, sizeof(int) * MAX_HAND_COUNT);
    }

    memcpy(&testG, &G, sizeof(struct gameState)); // Copy game state into test state

    printf ("TESTING playCard():\n");
    // Case 1: playCard should return 0 when phase is 0, and -1 otherwise
#if (NOISY_TEST == 1)
    printf("Phase set to 0 - phase = %d, expected = %d\n", playCard(0, -1,-1, -1, &testG), 0);
#endif  
    assert(playCard(0, -1,-1, -1, &G) == 0);
#if (NOISY_TEST == 1)
    // Reset numActions 
    G.numActions = 1;
    testG.numActions = 1;
    G.phase = 1;
    testG.phase = 1;
    printf("Phase set to 1 - phase = %d, expected = %d\n", playCard(0, -1,-1, -1, &testG), -1);
#endif  
    assert(playCard(0, -1,-1, -1, &G) == -1);
    
    // Case 2: playCard should return 0 when numActions > 1 and -1 otherwise
#if (NOISY_TEST == 1)
    // Reset numActions 
    G.numActions = 1;
    testG.numActions = 1;
    // Reset phase
    G.phase = 0;
    testG.phase = 0;
    printf("numActions set to 1 - numActions = %d, expected = %d\n", playCard(3, -1,-1, -1, &testG), 0);
#endif  
    assert(playCard(3, -1,-1, -1, &G) == 0);
#if (NOISY_TEST == 1)
    G.numActions = 0;
    testG.numActions = 0;
    printf("numActions set to 0 - numActions = %d, expected = %d\n", playCard(4, -1,-1, -1, &testG), -1);
#endif  
    assert(playCard(4, -1,-1, -1, &G) == -1);
    
//     // Case 2: Play the first card which is smithy
//     // Player should end up with 7 Cards 
//     // Player should end up with 1 action left
//     handVal = handCard(0, &G);
//     playCard(0, -1, -1, -1, &G);
// #if (NOISY_TEST == 1)
//     printf("Smithy Card Played - handVal = %d, expected = %d\n", handVal, SMITHY_VAL);
// #endif        
//     assert(handVal == SMITHY_VAL);
// #if (NOISY_TEST == 1)
//     printf("Player Hand Count - handCount = %d, expected = %d\n", numHandCards(&G), 7);
// #endif        
//     assert(numHandCards(&G) == 7);

// #if (NOISY_TEST == 1)
//     printf("Player Num Actions - numActions = %d, expected = %d\n", G.numActions, 1);
// #endif   
//     assert(G.numActions == 1);

    printf("All tests passed!\n");

    return 0;
}