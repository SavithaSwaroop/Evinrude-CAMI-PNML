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
#define P2_121_EXIT 1
#define P2_108_4_76_FACTORIAL_PATH 2
#define P2_108_ENTRY 3
#define P2_108_4_76_FACTORIAL_RETURN 4
#define P2_121_ENTRY 5
#define P2_121_4_160_FACTORIAL_PATH 6
#define P2_108_2_58___BUILTIN_PUTS_POST 7
#define PGLOBAL_EXIT 8
/*****************************************/

#endif /* end of include guard: NET_H */

