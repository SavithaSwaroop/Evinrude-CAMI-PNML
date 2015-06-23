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
#define EXIT 1
#define FCLOSE 2
#define __BUILTIN_PUTS 3
#define FOPEN 4
/*****************************************/

#endif /* End of include guard: EVENTS_H */

