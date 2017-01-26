#include <failpoint.h>
#include <stdio.h>

void
foo()
{
    FAILPOINT(foo_bananas, "Peel bananas", {
            printf("foo bananas enabled with %ld\n", __failpoint_value__);
        });
              
    FAILPOINT(foo_errors, "Make errors", {
            printf("foo errors enabled with %ld\n", __failpoint_value__);
        });
}
