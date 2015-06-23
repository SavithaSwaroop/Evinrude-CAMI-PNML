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
#define P1_92_2_278_FOPEN_PRE 1
#define PSYS_1_92_4_294___BUILTIN_PUTS_REDUC5_POST 2
#define P1_92_2_278_FOPEN_POST 3
#define P1_92_4_296_FOPEN_POST 4
#define P1_92_5_307___BUILTIN_PUTS_PRE 5
#define P1_92_9_336_FCLOSE_PRE 6
#define P1_92_9_335_FCLOSE_PRE 7
#define P1_92_ENTRY 8
#define P1_92_5_308_EXIT_PRE 9
#define PGLOBAL_EXIT 10
/*****************************************/

#endif /* end of include guard: NET_H */

