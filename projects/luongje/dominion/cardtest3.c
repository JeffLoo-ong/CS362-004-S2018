/* -----------------------------------------------------------------------
 * Test file for Adventurer card
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
    int testHand[5] = {adventurer, smithy, smithy, smithy, smithy}; 
    int k[10] = {adventurer, council_room, feast, gardens, mine, 
            remodel, smithy, village, baron, great_hall};
    struct gameState G;
    struct gameState testG;
    int NUM_PLAYERS = 2;
    int MAX_HAND_COUNT = 5;
    int ADVENTURER_VAL = 7;
    int thisPlayer = 0;

    // Initialize game state
    r = initializeGame(NUM_PLAYERS, k, seed, &G); // Initialize a new game

    // Fill both players hands with the testHand cards
    for(i = 0; i < 2 ; i++){
        G.handCount[i] = MAX_HAND_COUNT;
        memcpy(G.hand[i], testHand, sizeof(int) * MAX_HAND_COUNT);
    }

    memcpy(&testG, &G, sizeof(struct gameState)); // Copy game state into test state

    printf ("TESTING Adventurer Card:\n");

    handVal = handCard(0, &testG);
    r = cardEffect(adventurer, -1, -1, -1, &testG, 0, 0);
    printf("Cardeffect Success: %d\n", r);

    #if (NOISY_TEST == 1)
    printf("Adventurer Card Played - Value = %d, expected = %d\n", handVal, ADVENTURER_VAL);
    printf("1. Coins = %d, expected = %d\n", testG.coins, G.coins);
    printf("2. Player Num Actions - numActions = %d, expected = %d\n", testG.numActions, G.numActions);
    printf("3. Player Hand Count - handCount = %d, expected = %d\n", numHandCards(&testG), numHandCards(&G) + 2);
    printf("4. First Drawn Card Value - Value = %d, expected = 4,5,or 6\n", testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1]);
    printf("5. Second Drawn Card Value - Value = %d, expected = 4,5,or 6\n", testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2]);
    #endif        
    myAssert(handVal == ADVENTURER_VAL, "Card tested is not Adventurer Card!");    
    myAssert(testG.coins == G.coins, "Test Case 1");
    myAssert(testG.numActions == G.numActions, "Test Case 2");
    myAssert(numHandCards(&testG) == numHandCards(&G) + 2, "Test Case 3");
    myAssert(testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == copper 
        || testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == silver
        || testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == gold, "Test Case 4");
    myAssert(testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2] == copper 
        || testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2] == silver
        || testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2] == gold, "Test Case 5");
    printf("\nAll tests passed!\n");

    return 0;
}