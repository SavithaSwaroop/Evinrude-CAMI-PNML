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

    /* Place 0_24_2_73___builtin_puts_post */
    case P0_24_2_73___BUILTIN_PUTS_POST: {

      switch (event.type) {
        case PRINTF: {
          /* On change l'état... */
            current->place = P0_24_7;
            return P0_24_2_73___BUILTIN_PUTS_POST;
        }
        default: return ERROR;
      }
    }

    /* Place 0_24_7 */
    case P0_24_7: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = PGLOBAL_EXIT;
            return P0_24_7;
        }
        case PRINTF: {
          /* On change l'état... */
            current->place = P0_24_7;
            return P0_24_7;
        }
        default: return ERROR;
      }
    }

    /* Place 0_24_ENTRY */
    case P0_24_ENTRY: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = P0_24_2_73___BUILTIN_PUTS_POST;
            return P0_24_ENTRY;
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

