/* -----------------------------------------------------------------------
 * Unit test for Village card
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
    int testHand[10] = {village, village, village, village, village, village, village, village, village, village}; 
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    struct gameState testG;
    int NUM_PLAYERS = 2;
    int MAX_HAND_COUNT = 10;
    int VILLAGE_VAL = 14;
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

    printf ("TESTING Village Card:\n");
    
    // Case 1: Play the village card
    handVal = handCard(0, &testG);
    r = cardEffect(village, -1, -1, -1, &testG, 0, 0);
    printf("Cardeffect Success: %d\n", r);

#if (NOISY_TEST == 1)
    printf("1. Village Card Played - Value = %d, expected = %d\n", handVal, VILLAGE_VAL);
    printf("2. Player Hand Count - handCount = %d, expected = %d\n", numHandCards(&testG), numHandCards(&G));
    printf("3. Deck Count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 1);
    printf("4. Coins = %d, expected = %d\n", testG.coins, G.coins);
    //Bug
    printf("5. Player Num Actions - numActions = %d, expected = %d\n", testG.numActions, G.numActions + 2);
#endif        
    myAssert(handVal == VILLAGE_VAL, "Card tested is not Village card!\n");    
    myAssert(numHandCards(&testG) == numHandCards(&G), "Test Case 2");
    myAssert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 1, "Test Case 3");
    myAssert(testG.coins == G.coins, "Test Case 4");
    myAssert(testG.numActions == G.numActions + 2, "Test Case 5");

    if(handVal != VILLAGE_VAL){
        testsPassed = 0;
    }
    if(numHandCards(&testG) != numHandCards(&G)){
        testsPassed = 0;
    }
    if(testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - 1){
        testsPassed = 0;
    }
    if(testG.coins != G.coins){
        testsPassed = 0;
    }
    if(testG.numActions != G.numActions + 2){
        testsPassed = 0;
    }
    if(testsPassed == 1){
        printf("\nAll tests passed!\n");
    }
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    return 0;
}