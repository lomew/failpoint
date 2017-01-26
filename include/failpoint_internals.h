#pragma once

#include "linker_set.h"
#include <stdbool.h>

struct failpoint {
    const char *name;
    const char *doc;
    bool enabled;
    long value;
};
