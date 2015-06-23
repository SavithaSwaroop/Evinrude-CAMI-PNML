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
#define P0_46_9_335_FCLOSE_POST 1
#define P0_46_5_307___BUILTIN_PUTS_POST 2
#define P0_46_5_306_FCLOSE_POST 3
#define P0_46_9_334___BUILTIN_PUTS_POST 4
#define P0_46_ENTRY 5
#define P0_46_4_296_FOPEN_POST 6
#define P0_46_2_276___BUILTIN_PUTS_POST 7
#define PSYS_0_46_4_294___BUILTIN_PUTS_REDUC5_POST 8
#define P0_46_2_278_FOPEN_POST 9
#define PGLOBAL_EXIT 10
/*****************************************/

#endif /* end of include guard: NET_H */

