/* -----------------------------------------------------------------------
 * Test file for Smithy card
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
    int testsPassed = 1;
    // Initialize game state
    r = initializeGame(NUM_PLAYERS, k, seed, &G); // Initialize a new game

    // Fill both players hands with the testHand cards
    for(i = 0; i < 2 ; i++){
        G.handCount[i] = MAX_HAND_COUNT;
        memcpy(G.hand[i], testHand, sizeof(int) * MAX_HAND_COUNT);
    }

    memcpy(&testG, &G, sizeof(struct gameState)); // Copy game state into test state

    printf ("TESTING Smithy Card:\n");

    handVal = handCard(0, &testG);
    r = cardEffect(smithy, -1, -1, -1, &testG, 0, 0);
    printf("Cardeffect Success: %d\n", r);
    #if (NOISY_TEST == 1)
    printf("1. Smithy Card Played - Value = %d, expected = %d\n", handVal, SMITHY_VAL);
    printf("2. Coins = %d, expected = %d\n", testG.coins, G.coins);
    printf("3. Player Num Actions - numActions = %d, expected = %d\n", testG.numActions, G.numActions);
    printf("4. Player Hand Count - handCount = %d, expected = %d\n", numHandCards(&testG), numHandCards(&G) + 2);
    #endif        
    myAssert(handVal == SMITHY_VAL, "Card tested is not Smithy Card!");    
    myAssert(testG.coins == G.coins, "Test Case 2");
    myAssert(testG.numActions == G.numActions, "Test Case 3");
    myAssert(numHandCards(&testG) == numHandCards(&G) + 2, "Test Case 4");

    if(handVal != SMITHY_VAL){
        testsPassed = 0;
    }
    if(testG.coins != G.coins){
        testsPassed = 0;
    }
    if(testG.numActions != G.numActions){
        testsPassed = 0;
    }
    if(testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - 3){
        testsPassed = 0;
    }
    if(numHandCards(&testG) != numHandCards(&G) + 2){
        testsPassed = 0;
    }
    if(testsPassed == 1){
        printf("\nAll tests passed!\n");
    }
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    return 0;
}