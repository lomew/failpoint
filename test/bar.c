#include <failpoint.h>
#include <stdio.h>

void
bar()
{
    long b = false;
    FAILPOINT(bar_set, NULL, b = __failpoint_value__);
    printf("bar.b is %ld\n", b);
}
