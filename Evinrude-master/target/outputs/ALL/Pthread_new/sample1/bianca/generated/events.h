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
#define PTHREAD_JOIN 1
#define PRINTF 2
#define __BUILTIN_PUTS 3
#define PTHREAD_CREATE 4
#define __BUILTIN_FWRITE 5
/*****************************************/

#endif /* End of include guard: EVENTS_H */

