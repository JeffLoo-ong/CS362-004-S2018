/* -----------------------------------------------------------------------
 * Unit test for Village card
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
    int testHand[10] = {village, village, village, village, village, village, village, village, village, village}; 
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    struct gameState testG;
    int NUM_PLAYERS = 2;
    int MAX_HAND_COUNT = 10;
    int VILLAGE_VAL = 14;
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

    printf ("TESTING Village Card:\n");
    
    // Case 1: Play the village card
    handVal = handCard(0, &testG);
    cardEffect(village, -1, -1, -1, &testG, 0, 0);

#if (NOISY_TEST == 1)
    printf("Village Card Played - Value = %d, expected = %d\n", handVal, VILLAGE_VAL);
    printf("Player Hand Count - handCount = %d, expected = %d\n", numHandCards(&testG), numHandCards(&G));
	printf("Deck Count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 1);
    printf("Coins = %d, expected = %d\n", testG.coins, G.coins);
    printf("Player Num Actions - numActions = %d, expected = %d\n", testG.numActions, G.numActions);
#endif        
    assert(handVal == VILLAGE_VAL);    
    assert(numHandCards(&testG) == numHandCards(&G));
    assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 1);
    assert(testG.coins == G.coins);
    assert(testG.numActions == G.numActions);

    printf("All tests passed!\n");

    return 0;
}