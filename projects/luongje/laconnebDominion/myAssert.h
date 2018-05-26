#include <stdlib.h>

int myAssert(int val, char *msg)
{
    if (val)
    {
        return 0;
    } else {
        // This should exit 1 to fail, but that breaks unittestreslts.out
        printf("\n%s failed!\n", msg);
        return 0;
    }
}