#include "process.h"
#include <dlfcn.h>

/***************************************************************************
 * Création d'une structure processus
 */
inline process_t* create_process(unsigned int id) {
        /* Allocation d'une zone mémoire pour les états du processus */
        process_t* process = (process_t*) malloc (sizeof(process_t));

        /* Allocation d'une zone mémoire pour les états du processus */
        state_t* states = (state_t*) malloc (INITIAL_SIZE * sizeof(state_t));

        /* Allocation d'une zone mémoire pour les états du processus */
        state_t* costates = (state_t*) malloc (INITIAL_SIZE * sizeof(state_t));
       
        /* Initialisation des champs du vecteur */
        process->id = id;
        process->size = 0;
        process->maxsize = INITIAL_SIZE;
        process->states = states;

        process->cosize = 0;
        process->comaxsize = INITIAL_SIZE;
        process->costates = costates;
       
        return process;
}

/***************************************************************************
 * Ajoute un état �  la liste des états du processus
 */
inline void add_costate(process_t* process, state_t state) {
        /* Doit-on allouer une nouvelle portion de tableau ? */
        if (process->cosize >= process->comaxsize) {
                state_t* newstates = (state_t*) malloc ((process->comaxsize * GROWTH_FACTOR) * sizeof(state_t));
                /* Recopie de l'ancien tableau dans le nouveau */
                memcpy(newstates, process->costates, process->comaxsize * sizeof(state_t));

                /* LibÚre l'ancienne zone mémoire */
                VERBOSE("[!] Free \n");
                _BIANCA_monitor_free(process->costates);

                /* Mise a jour des propriétés du vecteur */
                process->costates = newstates;
                process->comaxsize *= GROWTH_FACTOR;
        }
       
        /* Ajout de l'élément */
        process->costates[process->cosize] = state;
        process->cosize++;
}

/***************************************************************************
 * Initialise la liste des co-états
 */
inline void init_costates(process_t* process) {
        unsigned int i;
       
        VERBOSE("[?] Initialisation de la table des co-états\n");
        for (i = 0; i < process->size; i++) {
                add_costate(process, dup_state(process->states[i]));
        }
}

/***************************************************************************
 * Recherche un coétat du processus
 */
inline state_t* find_costate(process_t* process, state_t* adding_state) {
        unsigned int i;
               
        /* Recherche des coétats pour les comparer �  l'état en instance d'ajout */
        for (i = 0 ; i < process->cosize; i++) {
                if (compare_states(&(process->costates[i]), adding_state)) {
                        return &(process->costates[i]);
                }
        }
        return NULL;
}

/***************************************************************************
 * Ajoute un état �  la liste des états du processus
 */
inline void add_state(process_t* process, state_t state) {
        VERBOSE("[?] Demande de nouvel état...\n");
        VERBOSE("[?] Recherche dans les états précédents\n");
        if (find_costate(process, &state) != NULL) {
                VERBOSE("[?] @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ L'état %d a déj�  été parcouru\n",state.id);
                return;
        } 
       
        VERBOSE("[?] Ajout du nouvel état dans la table des co-états\n");
        add_costate(process, dup_state(state));
       
        VERBOSE("[?] Nouvel état %d\n",state.id);
        /* Doit-on allouer une nouvelle portion de tableau ? */
        if (process->size >= process->maxsize) {
                state_t* newstates = (state_t*) malloc ((process->maxsize * GROWTH_FACTOR) * sizeof(state_t));
                /* Recopie de l'ancien tableau dans le nouveau */
                memcpy(newstates, process->states, process->maxsize * sizeof(state_t));

                /* LibÚre l'ancienne zone mémoire */
                VERBOSE("[!] Free \n");
                _BIANCA_monitor_free(process->states);

                /* Mise a jour des propriétés du vecteur */
                process->states = newstates;
                process->maxsize *= GROWTH_FACTOR;
        }
       
        /* Ajout de l'élément */
        process->states[process->size] = state;
        process->size++;
}

/***************************************************************************
 * Supprime un état de la liste des états du processus
 */
inline void erase_state(process_t* process, state_t* state) {
        unsigned int i;
       
        // VERBOSE("[|] Processus (%d) avant modification :\n",process->id);
        // if (DEBUG_STATE) print_process(*process);
        // VERBOSE("[|]\n");
       
        if (state == NULL) { return; };
       
        /* Recherche de la case du vecteur concernée par la suppression */
        for (i = 0 ; i < process->size; i++) {
                /* Si l'élément a été trouvé, on peut le remplacer par le dernier élément du tableau */
                if (((process->states)+i) == state) { 
                        _BIANCA_monitor_free(process->states[i].lresources);
                        process->size -= 1;
                        process->states[i] = process->states[process->size];
                }
        }
       
        // VERBOSE("[|] Processus (%d) apres modificiation :\n",process->id);
        // if (DEBUG_STATE) print_process(*process);
        // VERBOSE("[|]\n");
}

/***************************************************************************
 * Supprime les états en double d'un processus
 */
inline void clean_states(process_t* process) {
        unsigned int i = 0, j, max = process->size;
       
        VERBOSE("[?] Suppression des co-états\n");
        for (i = 0; i < process->cosize; i++) {
                _BIANCA_monitor_free(process->costates[i].lresources);
        }
        process->cosize = 0;

        if (max <= 1) { return; };

        /* Comparaison des états du process */
       
        while (i < (max-1)) {
                j = i + 1;
                while ((i < j) && (j < max)) {
                        VERBOSE("[-] Comparaison des états %d et %d\n", process->states[i].id, process->states[j].id)
                        if (compare_states(&(process->states[i]),&(process->states[j]))) {
                                VERBOSE("[!] Etat %d (%d) �  supprimer !\n",process->states[j].id,j);
                                erase_state(process,&(process->states[j]));
                                max--;
                        } else {
                                j++;
                        }
                }
                i++;
        }
}

/***************************************************************************
 * Recherche un état du processus
 */
inline state_t* find_state(process_t* process, unsigned int place) {
        unsigned int i;
               
        /* Recherche de la case du vecteur concernée par la suppression */
        for (i = 0 ; i < process->size; i++) {
                /* Si l'élément a été trouvé, on peut le remplacer par le dernier élément du tableau */
                if (process->states[i].place == place) { 
                        return &(process->states[i]);
                }
        }
        return NULL;
}

/***************************************************************************
 * Affichage sur STDERR du contenu du vecteur (DEBUG)
 */
inline void print_process(process_t process) {
        unsigned int i;
       
        _BIANCA_monitor_fprintf(stderr,"  --- %3d ------------------------\n",process.id);
        _BIANCA_monitor_fprintf(stderr,"  Size : %d\n",process.size);
        _BIANCA_monitor_fprintf(stderr,"  Max-Size : %d\n",process.maxsize);
        _BIANCA_monitor_fprintf(stderr,"  States : \n");
        for (i=0 ; i<process.size; i++) {
                _BIANCA_monitor_fprintf(stderr,"\n    State ID --> %d\n",process.states[i].id);
                print_state(process.states[i]);
        }
        _BIANCA_monitor_fprintf(stderr,"\n  --------------------------------\n");
}

/***************************************************************************
 * Affichage sur STDERR du contenu du vecteur (DEBUG)
 */
inline void print_full_process(process_t process) {
        unsigned int i;
       
        _BIANCA_monitor_fprintf(stderr,"  --- %3d ------------------------\n",process.id);
        _BIANCA_monitor_fprintf(stderr,"  Size : %d\n",process.size);
        _BIANCA_monitor_fprintf(stderr,"  Max-Size : %d\n",process.maxsize);
        _BIANCA_monitor_fprintf(stderr,"  Costates : \n");
        for (i=0 ; i<process.cosize; i++) {
                _BIANCA_monitor_fprintf(stderr,"\n    Costate ID --> %d\n",process.costates[i].id);
                print_state(process.costates[i]);
        }
        _BIANCA_monitor_fprintf(stderr,"  States : \n");
        for (i=0 ; i<process.size; i++) {
                _BIANCA_monitor_fprintf(stderr,"\n    State ID --> %d\n",process.states[i].id);
                print_state(process.states[i]);
        }
        _BIANCA_monitor_fprintf(stderr,"\n  --------------------------------\n");
}
