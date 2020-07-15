#include <stdio.h>
#include "connector.h"

static MYSQL conn;
static const char *insert_template =
    "INSERT INTO Meetings VALUES (%u, \"%s\", \"%s\")";
static char insert_buf[100];
static const char *retrieve_template =
    "SELECT * FROM Meetings GROUP BY id ORDER BY start_time ASC";

int connector_initialize(void) {
    mysql_init(&conn);
    int ret = !mysql_real_connect(&conn,
                                  "localhost",
                                  "temp",
                                  "tmep_eptm",
                                  "Temp", 0, 0, 0);
    if (ret) {
        return 1;
    }
    return 0;
}

void connector_finalize(void) {
    mysql_close(&conn);
}

int connector_delete(void) {
    int ret = mysql_query(&conn, "DELETE FROM Meetings");
    if (ret) {
        puts(mysql_error(&conn));
    }
    return ret;
}

int connector_insert(unsigned id, struct Entry *e) {
    snprintf(insert_buf, 99, insert_template,
             id, e->start_time, e->end_time);
    int ret = mysql_query(&conn, insert_buf);
    if (ret) {
        puts(mysql_error(&conn));
        return ret;
    }
    return ret;
}

int connector_retrieve(MYSQL_RES **res) {
    int ret = mysql_query(&conn, retrieve_template);
    if (ret) {
        puts(mysql_error(&conn));
        return ret;
    }
    *res = mysql_store_result(&conn);
    return ret;
}
