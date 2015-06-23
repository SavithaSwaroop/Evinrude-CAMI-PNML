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

    /* Place 0_46_9_335_fclose_post */
    case P0_46_9_335_FCLOSE_POST: {

      switch (event.type) {
        case FCLOSE: {
          /* On change l'état... */
            current->place = PGLOBAL_EXIT;
            return P0_46_9_335_FCLOSE_POST;
        }
        default: return ERROR;
      }
    }

    /* Place 0_46_5_307___builtin_puts_post */
    case P0_46_5_307___BUILTIN_PUTS_POST: {

      switch (event.type) {
        case EXIT: {
          /* On change l'état... */
            current->place = PGLOBAL_EXIT;
            return P0_46_5_307___BUILTIN_PUTS_POST;
        }
        default: return ERROR;
      }
    }

    /* Place 0_46_5_306_fclose_post */
    case P0_46_5_306_FCLOSE_POST: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = P0_46_5_307___BUILTIN_PUTS_POST;
            return P0_46_5_306_FCLOSE_POST;
        }
        default: return ERROR;
      }
    }

    /* Place 0_46_9_334___builtin_puts_post */
    case P0_46_9_334___BUILTIN_PUTS_POST: {

      switch (event.type) {
        case FCLOSE: {
          /* On change l'état... */
            current->place = P0_46_9_335_FCLOSE_POST;
            return P0_46_9_334___BUILTIN_PUTS_POST;
        }
        default: return ERROR;
      }
    }

    /* Place 0_46_ENTRY */
    case P0_46_ENTRY: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = P0_46_2_276___BUILTIN_PUTS_POST;
            return P0_46_ENTRY;
        }
        default: return ERROR;
      }
    }

    /* Place 0_46_4_296_fopen_post */
    case P0_46_4_296_FOPEN_POST: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = P0_46_9_334___BUILTIN_PUTS_POST;
            return P0_46_4_296_FOPEN_POST;
        }
        case FCLOSE: {
          /* On change l'état... */
            current->place = P0_46_5_306_FCLOSE_POST;
            return P0_46_4_296_FOPEN_POST;
        }
        default: return ERROR;
      }
    }

    /* Place 0_46_2_276___builtin_puts_post */
    case P0_46_2_276___BUILTIN_PUTS_POST: {

      switch (event.type) {
        case FOPEN: {
          /* On change l'état... */
            current->place = P0_46_2_278_FOPEN_POST;
            return P0_46_2_276___BUILTIN_PUTS_POST;
        }
        default: return ERROR;
      }
    }

    /* Place sys_0_46_4_294___builtin_puts_reduc5_post */
    case PSYS_0_46_4_294___BUILTIN_PUTS_REDUC5_POST: {

      switch (event.type) {
        case FOPEN: {
          /* On change l'état... */
            current->place = P0_46_4_296_FOPEN_POST;
            return PSYS_0_46_4_294___BUILTIN_PUTS_REDUC5_POST;
        }
        case EXIT: {
          /* On change l'état... */
            current->place = PGLOBAL_EXIT;
            return PSYS_0_46_4_294___BUILTIN_PUTS_REDUC5_POST;
        }
        default: return ERROR;
      }
    }

    /* Place 0_46_2_278_fopen_post */
    case P0_46_2_278_FOPEN_POST: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = PSYS_0_46_4_294___BUILTIN_PUTS_REDUC5_POST;
            return P0_46_2_278_FOPEN_POST;
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

