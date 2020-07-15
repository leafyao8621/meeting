#include <stdio.h>
#include "tools/connector.h"
#include "tools/resetter.h"
#include "tools/scheduler.h"

int main(void) {
    int ret = connector_initialize();
    ret = resetter_reset(100, 100);
    unsigned num;
    scheduler_schedule(&num, 1, stdout);
    printf("num: %d\n", num);
    connector_finalize();
}
