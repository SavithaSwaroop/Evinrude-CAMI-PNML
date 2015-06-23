#include "global_table.h"
/*******************************************************************************
 * Initialise un vecteur pour stocker tous les processus
 */
inline global_table_t create_global_table(void) {
        global_table_t global_table;
       
        /* Allocation d'une zone mémoire pour le tableau de processus */
        process_t** processes = (process_t**) malloc (INITIAL_SIZE * sizeof(process_t*));

        /* Initialisation des champs du vecteur */
        global_table.size = 0;
        global_table.maxsize = INITIAL_SIZE;
        global_table.processes = processes;
       
        return global_table;
}

/***************************************************************************
 * Ajoute un processus �  la liste des processus
 */
inline void add_process(global_table_t* global_table, process_t* process) {
       
        /* Doit-on allouer une nouvelle portion de tableau ? */
        if (global_table->size == global_table->maxsize) {
                process_t** newprocesses = (process_t**) malloc ((global_table->maxsize * GROWTH_FACTOR) * sizeof(process_t*));
                /* Recopie de l'ancien tableau dans le nouveau */
                memcpy(newprocesses, global_table->processes, global_table->maxsize * sizeof(state_t*));

                /* LibÚre l'ancienne zone mémoire */
                VERBOSE("[!] Free \n");
                _BIANCA_monitor_free(global_table->processes);

                /* Mise a jour des propriétés du vecteur */
                global_table->processes = newprocesses;
                global_table->maxsize *= GROWTH_FACTOR;
        }
       
        /* Ajout de l'élément */
        global_table->processes[global_table->size] = process;
        global_table->size++;
}

/***************************************************************************
 * Ajoute un processus �  la liste des processus
 */
inline void erase_process(global_table_t* global_table, process_t* process) {
        unsigned int i,j;
       
        /* Recherche de la case du vecteur concernée par la suppression */
        for (i = 0 ; i < global_table->size; i++) {
                if (global_table->processes[i] == process) {
                        for (j = 0; i < process->size; j++) {
                                erase_state(process, &(process->states[i]));
                        }
                        global_table->size -= 1;
                        global_table->processes[i] = global_table->processes[global_table->size];
                }
        }
}

/***************************************************************************
 * Recherche un processus dont au moins un état correspond �  la place
 */
inline process_t* find_process_state(global_table_t* global_table, unsigned int place) {
        unsigned int i;
               
        /* Recherche de la case du vecteur concernée par la suppression */
        for (i = 0 ; i < global_table->size; i++) {
                /* Si l'élément a été trouvé, on peut le remplacer par le dernier élément du tableau */
                if (find_state(global_table->processes[i], place) != NULL) {
                        return global_table->processes[i];
                }
        }
        return NULL;
}

/***************************************************************************
 * Recherche un processus �  partir de son ID
 */
inline process_t* find_process_id(global_table_t* global_table, unsigned int id) {
        unsigned int i;
               
        /* Recherche de la case du vecteur concernée par la suppression */
        for (i = 0 ; i < global_table->size; i++) {
                if (global_table->processes[i]->id == id) {
                        return global_table->processes[i];
                }
        }
        return NULL;
}

/***************************************************************************
 * Affichage sur STDERR du contenu du tableau de processus (DEBUG)
 */
inline void print_processes(global_table_t global_table) {
        unsigned int i;
       
        _BIANCA_monitor_fprintf(stderr,"=== GLOBAL =======================\n");
        _BIANCA_monitor_fprintf(stderr,"Size : %d\n",global_table.size);
        _BIANCA_monitor_fprintf(stderr,"Max-Size : %d\n",global_table.maxsize);
        _BIANCA_monitor_fprintf(stderr,"Processes : \n");
        for (i=0 ; i<global_table.size; i++) {
                _BIANCA_monitor_fprintf(stderr,"\n  Proc ID --> %d\n",global_table.processes[i]->id);
                print_process(*(global_table.processes[i]));
        }
        _BIANCA_monitor_fprintf(stderr,"\n================================\n");
}
