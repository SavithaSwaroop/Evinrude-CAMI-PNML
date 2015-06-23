#ifndef PLACE_H
#define PLACE_H
#include "place.h"
#endif

/**
 * Initialisation du marquage d'une place (place)
**/
t_marking* init_place_marking(t_place* place) {
        int i;
       
        /* Allocation et initialisation d'un marquage */
        t_marking* marking = (t_marking*) malloc (sizeof(t_marking));
        memset(marking,0,sizeof(t_marking));
       
        marking->place = place;
        marking->nb_tokens = 0;
       
        /* Mise �  zéro de toutes les places pour les jetons */
        for (i = 0; i < SIZEMARKING; i++) {
                marking->tokens[i] = 0;
        }
        return marking;
}

/**
 * Initialisation d'un nouveau marquage (avec recopie d'un marquage précédent)
 **/
t_marking* dup_marking(t_marking* old_marking, t_place* place) {
        int i;
       
        VERBOSE("[?] Duplication du marquage de la place %s pour la place %s\n", old_marking->place->name, place->name);       
       
        /* Allocation d'un nouvel etat */
        t_marking* new_marking = init_place_marking(place);
       
        /* Recopie de tous les tokens du marquage */
        for (i = 0; i < old_marking->nb_tokens; i++) {
                add_token(new_marking, old_marking->tokens[i]);
        }
        return new_marking;
}

/**
 * Ajout du jeton (token) dans le marquage (marking)
 * - token < 0 => on supprime le jeton s'il existe
 * - tolen > 0 => on ajoute le jeton au marquage
**/
t_marking* add_token(t_marking* marking, t_token token) {
//      int j;
        int i,tmp_size;
       
        /* Si le jeton est < 0... On le supprime du tableau (si on le trouve) */
        if (token < 0) {
                VERBOSE("[-] Retrait du jeton %d pour le marquage de %s\n",token, marking->place->name);
                for (i = 0; i < marking->nb_tokens; i++) {
                        VERBOSE("[-] Detection du token %d (recherche de %d)\n",marking->tokens[i], -(token));
                        if (marking->tokens[i] == -(token)) {
                                tmp_size = marking->nb_tokens;
                                /* Suppression d'un token et compactage du tableau de tokens */
                                //for (j = i; j < tmp_size; j++) { marking->tokens[j] = marking->tokens[j+1]; }
                                marking->tokens[i] = marking->tokens[tmp_size-1];
                                marking->tokens[tmp_size] = 0;
                               
                                marking->nb_tokens--;
                                return marking;
                        }
                }
                /* On a pas trouvé le jeton dans le marquage */
                VERBOSE("[!] Impossible de trouver le jeton %d pour le marquage de %s\n",token, marking->place->name);
                return marking;
        }
       
        /* Si on ajoute un token dans la palce de sortie */
        if (marking->place->flag == FLAG_END) {
                VERBOSE("[!] Ajout dans la place EXIT\n");
                return marking;
        }
       
        /* Ajout du jeton dans la table */
        VERBOSE("[-] Ajout du jeton %d pour le marquage de %s\n",token, marking->place->name);
        marking->tokens[marking->nb_tokens] = token;
        marking->nb_tokens++;
        return marking;
}

/**
 * Initialisation du marquage initial d'une place (place)
**/
t_marking* set_initial_place_marking(t_place* place, t_token token) {
        if (place->initial_marking == NULL) {
                t_marking* initial_marking = init_place_marking(place);
                place->initial_marking = initial_marking;
        }
        add_token(place->initial_marking, token);
        return place->initial_marking;
}

void set_flag(t_place* place, int flag) {
        place->flag = flag;
}

/**
 * Supprime les tokens nuls dans le marquage (marking)
**/
void clean_place_marking(t_marking* marking) {
        int i;
        for (i = 0; i < marking->nb_tokens; i++) {
                if (marking->tokens[i] == 0) {
                        int size_tmp = marking->nb_tokens;
                        //int j;
                        //for (j = i; j < size_tmp; j++) { marking->tokens[j] = marking->tokens[j+1]; }

                        marking->tokens[i] = marking->tokens[size_tmp];
                        marking->tokens[size_tmp] = 0;

                        marking->nb_tokens--;
                }
        }
}

/**
 * Retourne le nombre d'occurence du token (token)
**/
int get_cardtoken(t_marking* marking, t_token token) {
        int i, cpt = 0;
        for (i = 0; i < marking->nb_tokens; i++) {
                if (marking->tokens[i] == token) { cpt++; }
        }
        return cpt;
}

/**
 * Affichage du marquage (marking)
**/
void print_marking(t_marking* marking) {
        int i;
       
        if (marking == NULL) { VERBOSE("-?-"); return; }
       
        VERBOSE("(%d) ", marking->nb_tokens);
        for (i = 0; i < marking->nb_tokens; i++) {
                if (marking->tokens[i] != 0) {
                        VERBOSE("%d | ", marking->tokens[i]);
                }
        }
}
