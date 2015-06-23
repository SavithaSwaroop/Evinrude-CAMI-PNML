#ifndef HEADERS_H
#define HEADERS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

/* Surcharge des appels internes (EXTERN) */
extern void (*_BIANCA_monitor_free) (void *);
extern int (*_BIANCA_monitor_fprintf) (FILE *, const char *, ...);
extern int (*_BIANCA_monitor_pthread_mutex_init) (pthread_mutex_t *, const pthread_mutexattr_t *);
extern pthread_t (*_BIANCA_monitor_pthread_self) (void);

/* Nombre de threads maximum pouvant être gérés par BIANCA */
#define MAXTHREADS 100

#define INITIAL_SIZE 50         /* Taille initiale d'un vecteur */
#define GROWTH_FACTOR 2         /* Facteur d'augmentation de la taille du vecteur */
#define ERROR 0
#define SUCCESS 1
       
/* Macros pour les affichage du DEBUG */
#define DEBUG_STATE 1    /* Etat du DEBUG (1=>TRUE) */
#define VERBOSE(format...) if (DEBUG_STATE) { _BIANCA_monitor_fprintf(stderr,format); }

/* Macros pour les dump de TRACE */
#define TRACE_STATE 1    /* Etat du dump des TRACES (1=>TRUE) */
#define TRACE(event) if (TRACE_STATE) { trace(event); }
#define TRACE_INIT(state) if (TRACE_STATE) { trace_init(state); }

#endif /* HEADERS_H */
