#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "../game.h"

#define MAX 30
#define TRUE 1
#define FALSE 0

char* next_line(FILE *stream, char* buffer) {
        if (fgets (buffer, MAX, stream) == NULL) {
                /* Determine si on a atteint la fin du fichier */
                if (feof(stream)) { return NULL; } 
                fprintf(stderr,"[!] Erreur lors de la lecture du fichier\n");
                exit(-1);
        }
        fprintf(stdout, "[?] Lecture de la ligne %s", buffer);
        return buffer;
}

char* find_init(FILE *stream, char* buffer) {
        char *init = NULL, *tmp = NULL;
        int correct_token = FALSE;
       
        if (stream != NULL) {
                /* Lecture d'une ligne du fichier de TRACE */
                while (!correct_token && ((tmp = next_line(stream,buffer)) != NULL)) {
                        if (!strncmp(tmp,"@@@",3)) {
                                /* Suppression du caractÚre de saut de ligne */
                                init = buffer + 4;
                                buffer[strlen(buffer)-1] = '\0';
                                correct_token = TRUE;
                        }
                }
                return init;
        }
        fprintf(stderr,"[!] Erreur lors de l'invocation de get_next_line\n");
        exit(-1);
}

char* next_token (FILE *stream, char* buffer) {
        int correct_token = FALSE;
        char *init = NULL, *tmp = NULL;

        if (stream != NULL) {
                /* Lecture d'une ligne du fichier de TRACE */
                while (!correct_token && ((tmp = next_line(stream,buffer)) != NULL)) {
                        if (!strncmp(tmp,"###",3)) {
                                /* Suppression du caractÚre de saut de ligne */
                                init = buffer + 4;
                                buffer[strlen(buffer)-1] = '\0';
                                correct_token = TRUE;
                        }
                }
                return init;
        }
        fprintf(stderr,"[!] Erreur lors de l'invocation de next_token\n");
        exit(-1);
}

int main (int argc, char** argv) {
        char buffer[MAX] = "";
        char* init_pt;
        int start_state = 0;
        event_t e;
        process_t *p;
       
        FILE* trace_file;
       
        if (argc < 2) {
                fprintf(stderr, "[!] Le nom du fichier de TRACE est requis !\n");
                exit(-1);
        }
       
        /* Ouverture du fichier de trace */
        trace_file = fopen(argv[1], "r");
        if (trace_file == NULL) {
                fprintf(stderr, "[!] Echec lors de l'ouverture du fichier de TRACE\n");
                exit(-1);
        }
        fprintf(stdout, "[?] Fichier %s ouvert\n",argv[1]);
       
        /* Recherche de l'initialisation */
        init_pt = find_init(trace_file, buffer);
        if (init_pt == NULL) { fprintf(stderr,"[!] Aucune initialisation !\n"); exit(-1); }
        start_state = atoi(init_pt);
        fprintf(stdout, "[?] Initialisation : %d\n", start_state);
       
        fseek(trace_file, 0L, SEEK_SET);
       
        /* Jeu dans le réseau */
        global_table_t global = init(1, start_state);
        p = find_process_id(&global, 1);

        while((init_pt = next_token(trace_file, buffer)) != NULL) {
                fprintf(stdout, "[-] Next Token: %s\n", init_pt);
                e.type = atoi(init_pt);
                e.owner = p;
                fire(&global, e);
        }

        return EXIT_SUCCESS;
}
