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
#define P7_216_2_94___BUILTIN_PUTS_POST 1
#define P7_216_ENTRY 2
#define P7_216_12 3
#define P7_216_3_106_PRINTF_POST 4
#define PGLOBAL_EXIT 5
/*****************************************/

#endif /* end of include guard: NET_H */

