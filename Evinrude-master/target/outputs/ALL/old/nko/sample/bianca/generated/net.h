#ifndef NET_H
#define NET_H

#include "events.h"
#include "../process.h"
#include "../state.h"
#include "../global_resource.h"
#include "../global_table.h"

void init_resources(global_table_t* global_table);
unsigned int next(global_table_t* global_table, process_t* process, state_t* current, event_t event);
void update(global_table_t* global_table, state_t* current, event_t event);

/*************** GENERATED ***************/
#define PGLOBAL_EXIT 1
#define P0_6_ENTRY 2
/*****************************************/

#endif /* end of include guard: NET_H */

