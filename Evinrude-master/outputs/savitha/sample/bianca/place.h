/** place.h **/

#ifndef HEADERS_H
#define HEADERS_H
#include "headers.h"
#endif

#define BLACK_TOKEN 1
#define ID_TOKEN  2
#define NEWID_TOKEN 3

#define NO_FLAG 0
#define FLAG_END 1

/**
 * Définition de l'identité d'un thread / process
**/
typedef int t_token;

/** Définition d'un marquage */
struct marking {
        struct place* place;
        int nb_tokens;
        t_token tokens[SIZEMARKING];
};

/**
 * Définition d'une place
**/
struct place {
        char* name;
        struct marking* initial_marking;
        int flag;
};

typedef struct marking t_marking;
typedef struct place t_place;

/* --- FONCTIONS ---- */
t_marking* add_token(t_marking* marking, t_token token);
void print_marking(t_marking* marking);
t_marking* dup_marking(t_marking* old_marking, t_place* place);
void set_flag(t_place* place, int flag);

t_marking* init_place_marking(t_place* place);
t_marking* set_initial_place_marking(t_place* place, t_token token);
void clean_place_marking(t_marking* marking);
int get_cardtoken(t_marking* marking, t_token token);
