/* -----------------------------------------------------------------------
 * Test file for Mine card
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include "myAssert.h"

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
    int testsPassed = 1;

    // Initialize game state
    r = initializeGame(NUM_PLAYERS, k, seed, &G); // Initialize a new game

    // Fill both players hands with the testHand cards
    for(i = 0; i < 2 ; i++){
        G.handCount[i] = MAX_HAND_COUNT;
        memcpy(G.hand[i], testHand, sizeof(int) * MAX_HAND_COUNT);
        updateCoins(i, &G, 0);
    }

    memcpy(&testG, &G, sizeof(struct gameState)); // Copy game state into test state

    printf ("TESTING Mine Card:\n");

    handVal = handCard(0, &testG);

    // Case 1: Upgrade a copper to a silver coin
    printf ("Test 1: Updating Copper --> Silver\n");
    r = cardEffect(mine, copperPosition, silver, -1, &testG, 0, 0);
    printf("Cardeffect Success: %d\n", r);
    
    #if (NOISY_TEST == 1)
    printf("Mine Card Played - Value = %d, expected = %d\n", handVal, MINE_VAL);
    printf("1. Coins = %d, expected = %d\n", testG.coins, G.coins + 1);
    printf("2. Player Num Actions - numActions = %d, expected = %d\n", testG.numActions, G.numActions);
    printf("3. Player Hand Count - handCount = %d, expected = %d\n", numHandCards(&testG), numHandCards(&G));
    printf("4. Copper card should now be silver card(5): %d\n", testG.hand[0][copperPosition]);
    #endif        
    myAssert(handVal == MINE_VAL, "Card tests is not Mine card!");    
    myAssert(testG.coins == G.coins + 1, "Test Case 1");
    myAssert(testG.numActions == G.numActions, "Test Case 2");
    myAssert(numHandCards(&testG) == numHandCards(&G), "Test Case 3");
    myAssert(testG.hand[0][copperPosition] == silver, "Test Case 4");

    // Case 2: Upgrade a silver to a gold coin
    printf ("\nTest 2: Updating Silver --> Gold\n");
    r = cardEffect(mine, silverPosition, gold, -1, &testG, silverPosition, 0);
    updateCoins(0, &testG, 0);
    printf("Cardeffect Success: %d\n", r);
    #if (NOISY_TEST == 1)
    printf("Mine Card Played - Value = %d, expected = %d\n", handVal, MINE_VAL);
    printf("1. Coins = %d, expected = %d\n", testG.coins, G.coins + 1);
    printf("2. Player Num Actions - numActions = %d, expected = %d\n", testG.numActions, G.numActions);
    printf("3. Player Hand Count - handCount = %d, expected = %d\n", numHandCards(&testG), numHandCards(&G));
    printf("4. Silver card should now be Gold card(6): %d\n", testG.hand[0][silverPosition]);
    #endif        
    myAssert(handVal == MINE_VAL, "Card tested is not Mine Card!");    
    myAssert(testG.coins == G.coins + 1, "Test Case 1");
    myAssert(testG.numActions == G.numActions, "Test Case 2");
    myAssert(numHandCards(&testG) == numHandCards(&G), "Test Case 3");
    myAssert(testG.hand[0][silverPosition] == gold, "Test Case 4");

    if(handVal != MINE_VAL){
        testsPassed = 0;
    }
    if(testG.coins != G.coins + 1){
        testsPassed = 0;
    }
    if(testG.numActions != G.numActions){
        testsPassed = 0;
    }
    if(numHandCards(&testG) != numHandCards(&G)){
        testsPassed = 0;
    }
    if(testG.hand[0][silverPosition] != gold){
        testsPassed = 0;
    }
    if(testsPassed == 1){
        printf("\nAll tests passed!\n");
    }
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    return 0;
}