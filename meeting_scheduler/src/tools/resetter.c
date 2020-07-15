#include "resetter.h"
#include "connector.h"

int resetter_reset(unsigned seed, unsigned num) {
    struct MT19937 gen;
    struct Entry ent;
    int ret = 0;
    mt19937_initialize(&gen, seed);
    ret = connector_delete();
    if (ret) {
        return ret;
    }
    for (unsigned i = 0; i < num; ++i) {
        generate_entry(&gen, &ent);
        ret = connector_insert(i, &ent);
        if (ret) {
            return ret;
        }
    }
    return 0;
}
