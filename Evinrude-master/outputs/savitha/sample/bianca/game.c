#include "game.h"

#define _GNU_SOURCE
#include <dlfcn.h>

/* Declaration des symboles internes */
void (*_BIANCA_monitor_free) (void *);
int (*_BIANCA_monitor_fprintf) (FILE *, const char *, ...);
int (*_BIANCA_monitor_pthread_mutex_init) (pthread_mutex_t *, const pthread_mutexattr_t *);
pthread_t (*_BIANCA_monitor_pthread_self) (void);

/* Variable globale: compteur d'occurences pour déclencher le garbage */
int collapse;

/***************************************************************************
 * Initialisation de la structure représentant un RdP
 */
inline global_table_t init(unsigned int id, unsigned int place) {
        global_table_t global_table;
        state_t initial_state;
        process_t* process;
        collapse = 0;
       
        /* Définition et surcharge des fonctions systÚme */
        if (!_BIANCA_monitor_fprintf) {
                _BIANCA_monitor_fprintf = (int (*)(FILE *, const char *, ...)) dlsym (RTLD_NEXT, "fprintf");
                if (_BIANCA_monitor_fprintf == NULL) { exit(-1); } else { VERBOSE("[!] Surcharge de FPRINTF : OK !\n"); }
        } else {
                VERBOSE("[!] Surcharge de FPRINTF : Already DONE !\n");
        }

        if (!_BIANCA_monitor_free) {
                _BIANCA_monitor_free = (void (*)(void *)) dlsym (RTLD_NEXT, "free");
                if (_BIANCA_monitor_free == NULL) { exit(-1); } else { VERBOSE("[!] Surcharge de FREE : OK !\n"); }
        } else {
                VERBOSE("[!] Surcharge de FREE : Already DONE !\n");
        }
       
        TRACE_INIT(place);
       
        /* Création du super-état */
        global_table = create_global_table();
        /* Création du processus pÚre */
        process = create_process(id);
        /* Création de l'état initial */
        initial_state = create_state(place);
        /* Ajout du marquage initial �  l'état initial */
        add_state(process, initial_state);
        /* Ajout du processus �  la table des processus */
        add_process(&global_table, process);
       
        return global_table;
}

/***************************************************************************
 * Tentative de franchissement en tenant compte de l'événement EVENT
 */
inline process_t* fire (global_table_t* global_table, event_t event) {
        unsigned int i = 0;
        unsigned int place;
       
        process_t* process = event.owner;
        assert(process != NULL);
       
        /* Extraction des stats */
        TRACE(event.type);

        /* Nettoyage */
        clean_states(process);

        VERBOSE("\n\n---------------------------------> Franchissement %s (Process:%d)\n",events[event.type],process->id);
        init_costates(process);
        VERBOSE("[?] Etat du processus:\n");
        if (DEBUG_STATE) print_full_process(*process);

        /* Parcours des états du processus ? */
        VERBOSE("[?] Parcours des etats:\n");
        while (i < process->size) {
                collapse++; /* Pour le GC */
                VERBOSE("[?] Focus sur l'etat %d\n",(process->states[i]).id);
                process->states[i].previous = 0; /* Reset de l'indicateur de franchissement */

                /* Tentative de franchissement */
                place = next(global_table, process, &(process->states[i]), event);
                               
                /* Si aucun franchissement n'est possible pour cet état et cet événement */
                if (!place) {
                        VERBOSE("----------------->  ETAT MORT (%d) ! (Evenement: %s)\n",process->states[i].id,events[event.type]);
                        if (process->size == 1) { print_process(*process); }
                        erase_state(process,&(process->states[i]));
                        --i; /* Attention �  l'indice de boucle qui doit être mis �  jour */
                        if (process->size == 0) {
                                _BIANCA_monitor_fprintf(stderr,"Dernier evenement recu: %s\n",events[event.type]);
                                print_processes(*global_table);
                        }
                        assert(process->size != 0);
                } else {
                        /* On marque que le marquage vient d'être mi �  jour pour un éventuelle postfire() */
                        process->states[i].previous = place;
                }
               
                /* Etat suivant */
                i++;
                if (DEBUG_STATE) { print_process(*process); }
        }
       
        return process;
}

/***************************************************************************
 * Mise �  jour des informations dans le RdP
 */
inline process_t* post_fire (global_table_t* global_table, event_t event) {
        unsigned int i = 0;
       
        process_t* process = event.owner;
        assert(process != NULL);

        VERBOSE("---------------------------------| Post Franchissement %s (Proc:%d)\n",events[event.type],process->id);

        /** Parcours de tous les états du processus **/
        while (i < process->size) {
                /* Est-ce que la marquage de cet état a été mis �  jour */
                if (process->states[i].previous != 0) {
                        VERBOSE("[?] Etat pendant trouvé !\n");
                        update(global_table, &(process->states[i]), event);
                        VERBOSE("[?] Fin de traitement\n");
                }
                /* Etat suivant */
                i++;
                if (DEBUG_STATE) { print_process(*process); }
        }
       
        return process;
}

/* Fonctions de TRACE */
void trace(int event) {
        VERBOSE("[INTERCEPT] --> %s\n",events[event]);
        _BIANCA_monitor_fprintf(stdout,"### %d\n",event);
}

void trace_init(int state) {
        VERBOSE("[INITIALISATION] --> %s\n",places[state]);
        _BIANCA_monitor_fprintf(stdout,"@@@ %d\n",state);
}
