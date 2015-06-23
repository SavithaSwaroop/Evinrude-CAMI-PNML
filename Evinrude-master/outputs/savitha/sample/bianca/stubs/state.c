#include "state.h"
#include "generated/net.h"

static unsigned short id = 0;

/***************************************************************************
 * Initialise un vecteur pour stocker tous les bindings de l'état
 */
state_t create_state(void) {
        state_t state;
       
        /* Allocation d'une zone mémoire pour le tableau de bindings */
        binding_t* bindings = (binding_t*) malloc (INITIAL_SIZE * sizeof(binding_t));
       
        /* Initialisation des champs du vecteur */
        state.id = id++;
        state.size = 0;
        state.maxsize = INITIAL_SIZE;
        state.bindings = bindings;
        state.previous = 0;
               
        return state;
}

/***************************************************************************
 * Duplique un état (opie profonde des bindings)
 */
state_t dup_state(state_t state) {
        state_t newstate;
       
        /* Allocation d'une zone mémoire pour le tableau de bindings */
        binding_t* bindings = (binding_t*) malloc (state.size * sizeof(binding_t));
       
        /* Recopie des bindings */
        memcpy(bindings, state.bindings, state.size * sizeof(binding_t));
       
        /* Initialisation des champs du vecteur */
        newstate.id = id++;
        newstate.size = state.size;
        newstate.maxsize = state.size;
        newstate.bindings = bindings;
        newstate.previous = state.previous;
       
        return newstate;
}

/***************************************************************************
 * Ajoute un binding dans l'état
 */
void add_binding(state_t* state, binding_t binding) {
        binding_t* old_binding;
       
        /* Doit-on allouer une nouvelle portion de tableau ? */
        if (state->size == state->maxsize) {
                binding_t* bindings = (binding_t*) malloc ((state->maxsize * GROWTH_FACTOR) * sizeof(binding_t));
                /* Recopie de l'ancien tableau dans le nouveau */
                memcpy(bindings, state->bindings, state->maxsize * sizeof(binding_t));

                /* LibÚre l'ancienne zone mémoire */
                free(state->bindings);

                /* Mise a jour des propriétés du vecteur */
                state->bindings = bindings;
                state->maxsize *= GROWTH_FACTOR;
        }
       
        if ((old_binding = find_binding(*state, binding.id)) != NULL) {
                *old_binding = binding;
        } else {
                /* Ajout de l'élément */
                state->bindings[state->size] = binding;
                state->size++;
        }
}

/***************************************************************************
 * Supprime un binding de l'état
 */
void erase_binding(state_t* state, binding_t* pbinding) {
        int i;
       
        if (pbinding == NULL) { return; };
       
        /* Recherche de la case du vecteur concernée par la suppression */
        for (i=0 ; i<state->size; i++) {
                /* Si l'élément a été trouvé, on peut le remplacer par le dernier élément du tableau */
                if (((state->bindings)+i) == pbinding) { 
                        state->size -= 1;
                        state->bindings[i] = state->bindings[(state->size)];
                }
        }
}

/***************************************************************************
 * Recherche un élément identifié par un identifiant de processus.
 */
binding_t* find_binding(state_t state, unsigned int id) {
        int i;
       
        /* Recherche de la case du vecteur identifiée  */
        for (i=0 ; i<state.size; i++) {
                /* Si l'élément a été trouvé, on peut le remplacer par le dernier élément du tableau */
                if (state.bindings[i].id == id) {
                        return &state.bindings[i];
                }
        }
       
        return NULL;
}

/***************************************************************************
 * Recherche un élément identifié par un identifiant de place (ressource).
 */
binding_t* find_resource(state_t state, unsigned int place, unsigned int id) {
        int i;
       
        /* Recherche de la case du vecteur identifiée  */
        for (i=0 ; i < state.size; i++) {
                /* Si l'élément a été trouvé, on peut le remplacer par le dernier élément du tableau */
                if (state.bindings[i].place == place) {
                        if ((id <= 0) || (state.bindings[i].id == id)) {
                                return &(state.bindings[i]);
                        }
                }
        }
       
        return NULL;
}



/***************************************************************************
 * Affichage sur STDERR du contenu du vecteur (DEBUG)
 */
void print_state(state_t state) {
        int i;
       
        fprintf(stderr,"  ......................\n");
        fprintf(stderr,"  Size     : %d\n",state.size);
        fprintf(stderr,"  Max-Size : %d\n",state.maxsize);
        fprintf(stderr,"  Bindings : ");
        for (i=0 ; i<(state.size - 1); i++) {
                fprintf(stderr,"(%d,%s),",state.bindings[i].id,places[state.bindings[i].place]);
        }
        fprintf(stderr,"(%d,%s)\n",state.bindings[(state.size - 1)].id,places[state.bindings[(state.size - 1)].place]);
        fprintf(stderr,"  ......................\n");
}
