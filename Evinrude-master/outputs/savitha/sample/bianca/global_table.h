#ifndef GLOBAL_TABLE_H
#define GLOBAL_TABLE_H
       
#include "process.h"

        typedef struct {
                unsigned int size;      /* La taille du vecteur */
                unsigned int maxsize;   /* La capacité maximale du vecteur */
                process_t** processes;  /* Un pointeur sur le début de la table des états du proc */
        } global_table_t;
       
        inline global_table_t create_global_table(void);
       
        inline void add_process(global_table_t* global_table, process_t* process);
        inline void print_processes(global_table_t global_table);
        inline process_t* find_process_state(global_table_t* global_table_t, unsigned int place);
        inline process_t* find_process_id(global_table_t* global_table, unsigned int id);
        inline void erase_process(global_table_t* global_table, process_t* process);
        /*binding_t* find_resource(state_t state, unsigned int place, unsigned int id);*/

#endif /* GLOBAL_TABLE_H */
