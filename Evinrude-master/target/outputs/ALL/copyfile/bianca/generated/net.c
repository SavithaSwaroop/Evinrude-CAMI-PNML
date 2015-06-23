#include "net.h"

/*********************************************************************************
 * Déclaration statiques des ressources globales utilisées par l'application
 */
void init_resources(global_table_t* global_table) {
}

/*********************************************************************************
 * Détermine le marquage après le franchissement d'une transition sensible à EVENT
 */
unsigned int next(global_table_t* global_table, process_t* process, state_t* current, event_t event) {

  switch (current->place) {

    /* Place 1_92_2_278_fopen_pre */
    case P1_92_2_278_FOPEN_PRE: {

      switch (event.type) {
        case FOPEN: {
          /* On change l'état... */
            current->place = P1_92_2_278_FOPEN_POST;
            return P1_92_2_278_FOPEN_PRE;
        }
        default: return ERROR;
      }
    }

    /* Place sys_1_92_4_294___builtin_puts_reduc5_post */
    case PSYS_1_92_4_294___BUILTIN_PUTS_REDUC5_POST: {

      switch (event.type) {
        case FOPEN: {
          /* On change l'état... */
            current->place = P1_92_4_296_FOPEN_POST;
            return PSYS_1_92_4_294___BUILTIN_PUTS_REDUC5_POST;
        }
        case EXIT: {
          /* On change l'état... */
            current->place = PGLOBAL_EXIT;
            return PSYS_1_92_4_294___BUILTIN_PUTS_REDUC5_POST;
        }
        default: return ERROR;
      }
    }

    /* Place 1_92_2_278_fopen_post */
    case P1_92_2_278_FOPEN_POST: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = PSYS_1_92_4_294___BUILTIN_PUTS_REDUC5_POST;
            return P1_92_2_278_FOPEN_POST;
        }
        default: return ERROR;
      }
    }

    /* Place 1_92_4_296_fopen_post */
    case P1_92_4_296_FOPEN_POST: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = P1_92_9_335_FCLOSE_PRE;
            return P1_92_4_296_FOPEN_POST;
        }
        case FCLOSE: {
          /* On change l'état... */
            current->place = P1_92_5_307___BUILTIN_PUTS_PRE;
            return P1_92_4_296_FOPEN_POST;
        }
        default: return ERROR;
      }
    }

    /* Place 1_92_5_307___builtin_puts_pre */
    case P1_92_5_307___BUILTIN_PUTS_PRE: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = P1_92_5_308_EXIT_PRE;
            return P1_92_5_307___BUILTIN_PUTS_PRE;
        }
        default: return ERROR;
      }
    }

    /* Place 1_92_9_336_fclose_pre */
    case P1_92_9_336_FCLOSE_PRE: {

      switch (event.type) {
        case FCLOSE: {
          /* On change l'état... */
            current->place = PGLOBAL_EXIT;
            return P1_92_9_336_FCLOSE_PRE;
        }
        default: return ERROR;
      }
    }

    /* Place 1_92_9_335_fclose_pre */
    case P1_92_9_335_FCLOSE_PRE: {

      switch (event.type) {
        case FCLOSE: {
          /* On change l'état... */
            current->place = P1_92_9_336_FCLOSE_PRE;
            return P1_92_9_335_FCLOSE_PRE;
        }
        default: return ERROR;
      }
    }

    /* Place 1_92_ENTRY */
    case P1_92_ENTRY: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = P1_92_2_278_FOPEN_PRE;
            return P1_92_ENTRY;
        }
        default: return ERROR;
      }
    }

    /* Place 1_92_5_308_exit_pre */
    case P1_92_5_308_EXIT_PRE: {

      switch (event.type) {
        case EXIT: {
          /* On change l'état... */
            current->place = PGLOBAL_EXIT;
            return P1_92_5_308_EXIT_PRE;
        }
        default: return ERROR;
      }
    }

    case PGLOBAL_EXIT: return ERROR;
  }
  assert(0);
}


/***************************************************************************
 * Met à jour le marquage après le franchissement d'après les informations récupérées
 */
void update(global_table_t* global_table, state_t* current, event_t event) {
  switch (current->previous) {
    default: return;
  }
}

