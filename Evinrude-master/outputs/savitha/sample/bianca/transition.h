/** transition.h **/

#ifndef HEADERS_H
#define HEADERS_H
#include "headers.h"
#endif

#ifndef PLACE_H
#define PLACE_H
#include "place.h"
#endif

/**
 * Définition d'une précondition
**/
typedef struct {
        t_token token;
        t_place *place;
        struct t_precond *next;
} t_precond;

/**
 * Définition d'une postcondition
**/
typedef struct {
        t_token token;
        t_place *place;
        struct t_postcond *next;
} t_postcond;

/**
 * Définition d'une transition
**/
typedef struct {
        char* name;
        t_event event;
        t_precond *head_precond;
        t_postcond *head_postcond;
        short has_been_fired;
} t_transition;


/* ------ FONCTIONS ------- */
t_precond* add_precond(t_transition* transition, t_place* place, t_token token);
t_postcond* add_postcond(t_transition* transition, t_place* place, t_token token);
