/* -----------------------------------------------------------------------
 * Unit test for playCard()
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
// #define SMITHY_COST = 4
// #define VILLAGE_COST = 3

int main() {
    int i, r;
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

    printf ("\nTESTING playCard():\n");
    // Case 1: playCard should return 0 when phase is 0, and -1 otherwise
#if (NOISY_TEST == 1)
    printf("1. Phase set to 0 - phase = %d, expected = %d\n", playCard(0, -1,-1, -1, &testG), 0);
#endif  
    myAssert(playCard(0, -1,-1, -1, &G) == 0, "Test case 1");
#if (NOISY_TEST == 1)
    // Reset numActions 
    G.numActions = 1;
    testG.numActions = 1;
    G.phase = 1;
    testG.phase = 1;
    printf("2. Phase set to 1 - phase = %d, expected = %d\n", playCard(0, -1,-1, -1, &testG), -1);
#endif  
    myAssert(playCard(0, -1,-1, -1, &G) == -1, "Test case 2");
    
    // Case 2: playCard should return 0 when numActions > 1 and -1 otherwise
#if (NOISY_TEST == 1)
    // Reset numActions 
    G.numActions = 1;
    testG.numActions = 1;
    // Reset phase
    G.phase = 0;
    testG.phase = 0;
    printf("3. numActions set to 1 - numActions = %d, expected = %d\n", playCard(3, -1,-1, -1, &testG), 0);
#endif  
    myAssert(playCard(3, -1,-1, -1, &G) == 0, "Test case 3");

#if (NOISY_TEST == 1)
    G.numActions = 0;
    testG.numActions = 0;
    printf("4. numActions set to 0 - numActions = %d, expected = %d\n", playCard(4, -1,-1, -1, &testG), -1);
#endif  
    myAssert(playCard(4, -1,-1, -1, &G) == -1,  "Test case 4");

    printf("\nAll tests passed!\n");

    return 0;
}