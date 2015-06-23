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
#define P0_15_ENTRY 1
#define P0_15_2_58___BUILTIN_PUTS_POST 2
#define P0_28_EXIT 3
#define P0_15_4_76_FACTORIAL_RETURN 4
#define P0_28_4_160_FACTORIAL_PATH 5
#define P0_28_ENTRY 6
#define PGLOBAL_EXIT 7
#define P0_15_4_76_FACTORIAL_PATH 8
/*****************************************/

#endif /* end of include guard: NET_H */

