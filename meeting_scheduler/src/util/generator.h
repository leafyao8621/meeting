#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include "mt19937.h"

struct Entry {
    char start_time[10];
    char end_time[10];
};

int generate_entry(struct MT19937 *gen, struct Entry *out);

#endif
