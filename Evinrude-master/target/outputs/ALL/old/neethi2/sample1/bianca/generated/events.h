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
/*****************************************/

#endif /* End of include guard: EVENTS_H */

