#include <stdio.h>
#include "generator.h"

int generate_entry(struct MT19937 *gen, struct Entry *out) {
    if (!gen || !out) {
        return 1;
    }
    unsigned h1, m1, h2, m2;
    unsigned t1, t2;
    h1 = mt19937_gen(gen) % 24;
    m1 = mt19937_gen(gen) % 60;
    h2 = mt19937_gen(gen) % 24;
    m2 = mt19937_gen(gen) % 60;
    t1 = h1 * 60 + m1;
    t2 = h2 * 60 + m2;
    if (t1 > t2) {
        snprintf(out->start_time, 6, "%02d:%02d", h2, m2);
        snprintf(out->end_time, 6, "%02d:%02d", h1, m1);
    } else {
        snprintf(out->start_time, 6, "%02d:%02d", h1, m1);
        snprintf(out->end_time, 6, "%02d:%02d", h2, m2);
    }
    return 0;
}
