#include "failpoint.h"

#include <fnmatch.h>
#include <stdlib.h>
#include <string.h>

SET_DECLARE(failpoints, struct failpoint);

void
failpoint_parse_setting(const char *setting)
{
    char *name = strdup(setting);
    char *colon = strchr(name, ':');
    long value = 1;
    if (colon) {
        *colon = '\0';
        value = strtol(colon+1, NULL, 0);
    }
    failpoint_set(name, value);
    free(name);
}

void
failpoint_set(const char *name, long value)
{
    struct failpoint **item;
    SET_FOREACH(item, failpoints) {
        struct failpoint *fp = *item;
        if (strcmp(fp->name, name) == 0) {
            fp->enabled = true;
            fp->value = value;
        }
    }
}

static void
do_print(const char *glob, bool with_doc, FILE *f)
{
    struct failpoint **item;
    SET_FOREACH(item, failpoints) {
        struct failpoint *fp = *item;
        if (glob && fnmatch(glob, fp->name, 0) != 0) {
            continue;
        }
        fprintf(f, "%s", fp->name);
        if (fp->enabled) {
            fprintf(f, ":%ld", fp->value);
        } else {
            fprintf(f, ":off");
        }
        if (with_doc) {
            fprintf(f, " (%s)", fp->doc);
        }
        fprintf(f, "\n");
    }
}

void
failpoint_print_all(FILE *f)
{
    do_print(NULL, false, f);
}

void
failpoint_print_all_full(FILE *f)
{
    do_print(NULL, true, f);
}

void
failpoint_print_matching(const char *glob, FILE *f)
{
    do_print(glob, false, f);
}

void
failpoint_print_matching_full(const char *glob, FILE *f)
{
    do_print(glob, true, f);
}
