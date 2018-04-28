/* -----------------------------------------------------------------------
 * Unit test for handCard()
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
    int NUM_PLAYERS = 2;
    int testHand[5] = {curse, estate, duchy, province, copper}; // 0-4 
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int MAX_HAND_COUNT = 5;

    // Initialize game state
    memset(&G, 23, sizeof(struct gameState)); // Clear game state
    r = initializeGame(NUM_PLAYERS, k, seed, &G); // Initialize a new game
    
    // Fill both players hands with the testHand cards
    for(i = 0; i < 2 ; i++){
        G.handCount[i] = MAX_HAND_COUNT;
        memcpy(G.hand[i], testHand, sizeof(int) * MAX_HAND_COUNT);
    }

    printf ("TESTING handCard():\n");
    
    // Case 1: Check that the first card is a curse card
    handVal = handCard(0, &G);
#if (NOISY_TEST == 1)
    printf("Curse - handVal = %d, expected = %d\n", handVal, 0);
#endif        
    assert(handVal == 0);

    // Case 2: Check that the first card is a estate card
    handVal = handCard(1, &G);
#if (NOISY_TEST == 1)
    printf("Estate - handVal = %d, expected = %d\n", handVal, 1);
#endif        
    assert(handVal == 1);

    // Case 3: Check tat the first card is a duchy card
    handVal = handCard(2, &G);
#if (NOISY_TEST == 1)
    printf("Duchy - handVal = %d, expected = %d\n", handVal, 2);
#endif        
    assert(handVal == 2);

    // Case 1: Check that the first card is a province card
    handVal = handCard(3, &G);
#if (NOISY_TEST == 1)
    printf("Province - handVal = %d, expected = %d\n", handVal, 3);
#endif        
    assert(handVal == 3);

    // Case 5: Check that the first card is a copper card
    handVal = handCard(4, &G);
#if (NOISY_TEST == 1)
    printf("Copper - handVal = %d, expected = %d\n", handVal, 4);
#endif        
    assert(handVal == 4);

    printf("All tests passed!\n");

    return 0;
}