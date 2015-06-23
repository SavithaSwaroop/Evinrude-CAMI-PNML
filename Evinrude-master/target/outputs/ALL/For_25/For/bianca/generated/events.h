#ifndef EVENTS_H
#define EVENTS_H

#include "../process.h"

typedef struct {
  process_t* owner;
  unsigned int type;
  unsigned int id;
  unsigned int value;
} event_t;

/*************** GENERATED ***************/
#define PRINTF 1
#define __BUILTIN_PUTS 2
/*****************************************/

#endif /* End of include guard: EVENTS_H */

