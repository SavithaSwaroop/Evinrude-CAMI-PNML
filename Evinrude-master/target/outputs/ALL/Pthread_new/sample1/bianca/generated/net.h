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
#define P0_12_ENTRY 1
#define P0_34_ENTRY 2
#define P0_34_5_183_PTHREAD_JOIN_PRE 3
#define PRES_ATTACHED_THREADS 4
#define P0_34_5_183_PTHREAD_JOIN_POST 5
#define P0_34_2_155_PTHREAD_CREATE_PRE 6
#define P0_34_2_155_PTHREAD_CREATE_POST 7
#define PGLOBAL_EXIT 8
/*****************************************/

#endif /* end of include guard: NET_H */

