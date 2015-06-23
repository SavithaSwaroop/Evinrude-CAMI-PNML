/* capsule.h */

#ifndef CAPSULE_H
#define CAPSULE_H

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <dirent.h>

#include "../game.h"

/* DO NOT REMOVE */
void __attribute__ ((constructor)) bianca_init(void);

/* TO CATCH */

#define MAIN_ENTRY P0_6_ENTRY


#endif /* end of include guard: CAPSULE_H */
