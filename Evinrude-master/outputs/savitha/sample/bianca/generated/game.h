/* game.h */

#ifndef GAME_H
#define GAME_H

#define _GNU_SOURCE

#include "global_table.h"
#include "generated/event.h"
#include "generated/net.h"

        inline global_table_t init(unsigned int id, unsigned int place);
        inline process_t* fire (global_table_t* global_table, event_t event);
        inline process_t* post_fire (global_table_t* global_table, event_t event);
        inline void trace (int event);
        inline void trace_init (int state);
       
#endif /* GAME_H */
