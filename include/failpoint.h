#pragma once

#include "failpoint_internals.h"
#include <stdio.h>

#define FAILPOINT(name, doc, code) do {                         \
    static struct failpoint __failpoint_##name = {              \
        #name,                                                  \
        doc ? doc : "undocumented",                             \
        false,                                                  \
        0,                                                      \
    };                                                          \
    SET_ENTRY(failpoints, __failpoint_##name);                  \
    if (__builtin_expect(__failpoint_##name.enabled, false)) {  \
        long __failpoint_value__ = __failpoint_##name.value;    \
        code;                                                   \
    }                                                           \
} while (0)

extern void failpoint_parse_setting(const char *setting);
extern void failpoint_set(const char *name, long value);

extern void failpoint_print_all(FILE *f);
extern void failpoint_print_all_full(FILE *f);

extern void failpoint_print_matching(const char *glob, FILE *f);
extern void failpoint_print_matching_full(const char *glob, FILE *f);
