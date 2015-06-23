/* state.h */

#ifndef STATE_H
#define STATE_H

#include "headers.h"

        typedef struct {
                unsigned int place;             /* Place où est stockée la ressource                                  */
                unsigned int card;              /* Cardinalité de la ressource                                                 */
        } lresource_t;

        typedef struct {
                unsigned int id;                        /* L'identifiant de l'état                                                             */
                unsigned int place;                     /* La place marquée pour cet identifiant                               */
                unsigned int previous;          /* La place marquée avant le dernier franchissement    */

                lresource_t* lresources;        /* Un pointeur sur le début de la table des ressources locales �  cet état */
                unsigned int size;                      /* Le nombre de ressources associées �  l'état                        */
                unsigned int maxsize;           /* Le nombre maximum de ressources associées �  l'état        */
        } state_t;
       
        inline state_t create_state(unsigned int place);
        inline state_t dup_state(state_t state);
        inline short compare_states(state_t* state1, state_t* state2);
        inline void add_local_resource(state_t* state, lresource_t resource);
        inline void erase_local_resource(state_t* state, lresource_t* resource,unsigned int card);
        inline lresource_t* find_local_resource(state_t* state, unsigned int place);
        inline void print_state(state_t state);
       
#endif /* STATE_H */
