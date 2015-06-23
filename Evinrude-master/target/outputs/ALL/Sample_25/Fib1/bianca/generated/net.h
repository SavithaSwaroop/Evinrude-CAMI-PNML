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
#define P0_20_ENTRY 1
#define P0_12_EXIT 2
#define P0_18_ENTRY 3
#define P0_5_EXIT 4
#define P0_16_EXIT 5
#define P0_1_ENTRY 6
#define P0_14_ENTRY 7
#define P0_20_EXIT 8
#define P0_4_EXIT 9
#define P0_10_EXIT 10
#define P0_15_ENTRY 11
#define P0_19_EXIT 12
#define P0_18_EXIT 13
#define P0_16_ENTRY 14
#define P0_12_ENTRY 15
#define P0_17_EXIT 16
#define P0_2_ENTRY 17
#define P0_22_EXIT 18
#define P0_0_EXIT 19
#define P0_1_EXIT 20
#define P0_3_EXIT 21
#define P0_24_9 22
#define P0_24_8 23
#define P0_24_EXIT 24
#define P0_24_7 25
#define P0_9_ENTRY 26
#define P0_24_6 27
#define P0_24_5 28
#define P0_24_4 29
#define P0_9_EXIT 30
#define P0_24_3 31
#define P0_23_ENTRY 32
#define P0_22_ENTRY 33
#define P0_24_2 34
#define P0_13_EXIT 35
#define P0_8_ENTRY 36
#define P0_6_ENTRY 37
#define P0_17_ENTRY 38
#define P0_8_EXIT 39
#define P0_7_ENTRY 40
#define P0_19_ENTRY 41
#define P0_14_EXIT 42
#define P0_4_ENTRY 43
#define P0_24_ENTRY 44
#define P0_3_ENTRY 45
#define P0_11_EXIT 46
#define P0_11_ENTRY 47
#define P0_2_EXIT 48
#define P0_0_ENTRY 49
#define P0_6_EXIT 50
#define P0_15_EXIT 51
#define P0_21_ENTRY 52
#define P0_7_EXIT 53
#define P0_5_ENTRY 54
#define P0_23_EXIT 55
#define PGLOBAL_EXIT 56
#define P0_21_EXIT 57
#define P0_13_ENTRY 58
#define P0_10_ENTRY 59
/*****************************************/

#endif /* end of include guard: NET_H */

