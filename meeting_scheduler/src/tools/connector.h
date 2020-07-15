#ifndef _CONNECTOR_H_
#define _CONNECTOR_H_

#include "mysql.h"
#include "../util/generator.h"

int connector_initialize(void);
int connector_delete(void);
int connector_insert(unsigned id, struct Entry *e);
int connector_retrieve(MYSQL_RES **res);
void connector_finalize(void);

#endif
