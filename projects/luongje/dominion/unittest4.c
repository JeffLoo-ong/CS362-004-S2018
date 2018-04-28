/* -----------------------------------------------------------------------
 * Unit test for getCost()
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
    printf ("TESTING getCost():\n");
    
    // Case 1: Check curse
#if (NOISY_TEST == 1)
    printf("Retrieved value of Curse = %d, expected = %d\n", getCost(0), 0);
#endif        
    assert(getCost(0) == 0);

    // Case 2: Check estate
#if (NOISY_TEST == 1)
    printf("Retrieved value of Estate = %d, expected = %d\n", getCost(1), 2);
#endif        
    assert(getCost(1) == 2);

    // Case 3: Check adventurer
#if (NOISY_TEST == 1)
    printf("Retrieved value of Adventurer = %d, expected = %d\n", getCost(7), 6);
#endif        
    assert(getCost(7) == 6);

    printf("All tests passed!\n");

    return 0;
}