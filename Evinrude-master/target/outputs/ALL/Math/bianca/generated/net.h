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
#define P5_169_2_74_PRINTF_PRE 1
#define P5_169_2_77_PRINTF_PRE 2
#define P5_169_2_73_PRINTF_PRE 3
#define P5_169_2_75_PRINTF_PRE 4
#define PGLOBAL_EXIT 5
#define P5_169_ENTRY 6
/*****************************************/

#endif /* end of include guard: NET_H */

