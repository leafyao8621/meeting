#include <stdlib.h>
#include <string.h>
#include "scheduler.h"
#include "connector.h"

int scheduler_schedule(unsigned *out, char verbose, FILE *fout) {
    if (!out || (verbose && !fout)) {
        return 1;
    }
    MYSQL_RES *res;
    if (connector_retrieve(&res)) {
        return 2;
    }
    unsigned long long n_row = mysql_num_rows(res);
    char *allocation = malloc(6 * n_row);
    char *allocation_end = allocation;
    char *allocation_iter = allocation;
    unsigned assignment;
    unsigned val = 0;
    MYSQL_ROW row;
    for (; row = mysql_fetch_row(res);) {
        assignment = 0;
        for (allocation_iter = allocation;
             allocation_iter != allocation_end &&
             strncmp(row[1], allocation_iter, 6) < 0;
             ++assignment, allocation_iter += 6);
        strncpy(allocation_iter, row[2], 6);
        if (assignment == val) {
            ++val;
            allocation_end += 6;
        }
        if (verbose) {
            fprintf(fout, "id: %s start: %s end: %s assignment: %u\n",
                    row[0], row[1], row[2], assignment);
            if (verbose > 1) {
                fputs("ending times:\n", fout);
                for (allocation_iter = allocation;
                     allocation_iter != allocation_end;
                     puts(allocation_iter), allocation_iter += 6);
            }
        }
    }
    free(allocation);
    *out = val;
    return 0;
}
