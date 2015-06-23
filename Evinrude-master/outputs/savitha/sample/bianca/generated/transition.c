#ifndef TRANSITION_H
#define TRANSITION_H
#include "transition.h"
#endif

/**
 * Ajout d'une précondition �  la transition
 */
t_precond* add_precond(t_transition* transition, t_place* place, t_token token) {
        t_precond *pre;
       
        if (transition == NULL) {
                VERBOSE("[!] Ajout d'une precondition : La transition est nulle !\n");
                exit(EXIT_FAILURE);
        }

        if (place == NULL) {
                VERBOSE("[!] Ajout d'une precondition : La place est nulle !\n");
                exit(EXIT_FAILURE);
        }
       
        VERBOSE("[?] Ajout d'une precondition pour %s : (%s,%d) !\n",transition->name, place->name, token);
       
        /* Creation de la précondition */
        pre = (t_precond*) malloc (sizeof(t_precond));
        memset(pre,0,sizeof(t_precond));
       
        pre->token = token;
        pre->place = place;
       
        /* Insertion de la nouvelle précondition en tête de liste ! */
        pre->next = (struct t_precond*) transition->head_precond;
        transition->head_precond = pre;
        return pre;
}

/**
 * Ajout d'une postcondition �  la transition
**/
t_postcond* add_postcond(t_transition* transition, t_place* place, t_token token) {
        t_postcond *post;
       
        if (transition == NULL) {
                VERBOSE("[!] Ajout d'une postcondition : La transition est nulle !\n");
                exit(EXIT_FAILURE);
        }
       
        if (place == NULL) {
                VERBOSE("[!] Ajout d'une postcondition : La place est nulle !\n");
                exit(EXIT_FAILURE);
        }
       
        VERBOSE("[?] Ajout d'une postcondition pour %s : (%s,%d) !\n",transition->name, place->name, token);
       
       
        /* Création de la postcondition */
        post = (t_postcond*) malloc (sizeof(t_postcond));
        memset(post,0,sizeof(t_postcond));
       
        post->token = token;
        post->place = place;
       
        /* Insertion de la nouvelle postcondition en tête de liste ! */
        post->next = (struct t_postcond*) transition->head_postcond;
        transition->head_postcond = post;
        return post;
}
