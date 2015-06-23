
#ifndef PROCESS_H
#define PROCESS_H

#include "state.h"

        typedef struct {
                unsigned int id;                /* L'identifiant du processus */

                /* Etats di process */
                unsigned int size;              /* La taille du vecteur */
                unsigned int maxsize;   /* La capacité maximale du vecteur */
                state_t* states;                /* Un pointeur sur le début de la table des états du process */

                /* Etats déj�  parcouru */
                unsigned int cosize;            /* La taille du vecteur */
                unsigned int comaxsize;         /* La capacité maximale du vecteur */
                state_t* costates;                      /* Un pointeur sur le début de la table des états du process */
        } process_t;

        inline process_t* create_process(unsigned int id);
        inline void init_costates(process_t* process);
        inline void print_process(process_t process);
        inline void print_full_process(process_t process);
        inline void add_state(process_t* process, state_t state);
        inline void erase_state(process_t* process, state_t* state);
        inline state_t* find_state(process_t* process, unsigned int place);
        inline void clean_states(process_t* process);

#endif /* PROCESS_H */
