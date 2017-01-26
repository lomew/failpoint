#include <failpoint.h>
#include <stdio.h>

extern void run(void);

int
main(int argc, char *argv[])
{
    int i;

    printf("-- INITIAL SETTINGS --\n");
    failpoint_print_all_full(stdout);
    printf("\n");

    for (i = 1; i < argc; i++) {
        failpoint_parse_setting(argv[i]);
    }
    if (argc > 1) {
        printf("-- MODIFIED SETTINGS --\n");
        failpoint_print_all(stdout);
        printf("\n");
    }

    printf("-- RUNNING PROGRAM --\n");
    run();
    printf("\n");

    return 0;
}
