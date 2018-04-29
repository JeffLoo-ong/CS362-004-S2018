/* -----------------------------------------------------------------------
 * Unit test for getCost()
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
    printf ("\nTESTING getCost():\n");
    
    // Case 1: Check curse
#if (NOISY_TEST == 1)
    printf("1. Retrieved value of Curse = %d, expected = %d\n", getCost(0), 0);
#endif        
    myAssert(getCost(0) == 0, "Test Case 1");

    // Case 2: Check estate
#if (NOISY_TEST == 1)
    printf("2. Retrieved value of Estate = %d, expected = %d\n", getCost(1), 2);
#endif        
    myAssert(getCost(1) == 2, "Test Case 2");

    // Case 3: Check adventurer
#if (NOISY_TEST == 1)
    printf("3. Retrieved value of Adventurer = %d, expected = %d\n", getCost(7), 6);
#endif        
    myAssert(getCost(7) == 6, "Test Case 3");

    printf("\nAll tests passed!\n");

    return 0;
}