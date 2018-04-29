/* -----------------------------------------------------------------------
 * Unit test for handCard()
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
    myAssert(r = 0, "initializeGame");
    // Fill both players hands with the testHand cards
    for(i = 0; i < 2 ; i++){
        G.handCount[i] = MAX_HAND_COUNT;
        memcpy(G.hand[i], testHand, sizeof(int) * MAX_HAND_COUNT);
    }

    printf ("\nTESTING handCard():\n");
    
    // Case 1: Check that the first card is a curse card
    handVal = handCard(0, &G);
#if (NOISY_TEST == 1)
    printf("1. Curse - handVal = %d, expected = %d\n", handVal, 0);
#endif        
    myAssert(handVal == 0, "Test case 1");

    // Case 2: Check that the first card is a estate card
    handVal = handCard(1, &G);
#if (NOISY_TEST == 1)
    printf("2. Estate - handVal = %d, expected = %d\n", handVal, 1);
#endif        
    myAssert(handVal == 1, "Test case 2");

    // Case 3: Check tat the first card is a duchy card
    handVal = handCard(2, &G);
#if (NOISY_TEST == 1)
    printf("3. Duchy - handVal = %d, expected = %d\n", handVal, 2);
#endif        
    myAssert(handVal == 2, "Test case 3");

    // Case 4: Check that the first card is a province card
    handVal = handCard(3, &G);
#if (NOISY_TEST == 1)
    printf("4. Province - handVal = %d, expected = %d\n", handVal, 3);
#endif        
    myAssert(handVal == 3, "Test case 4");

    // Case 5: Check that the first card is a copper card
    handVal = handCard(4, &G);
#if (NOISY_TEST == 1)
    printf("5. Copper - handVal = %d, expected = %d\n", handVal, 4);
#endif        
    myAssert(handVal == 4, "Test case 5");

    printf("\nAll tests passed!\n");

    return 0;
}