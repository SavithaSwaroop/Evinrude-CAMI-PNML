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

    /* Place 0_15_ENTRY */
    case P0_15_ENTRY: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = P0_15_4;
            return P0_15_ENTRY;
        }
        default: return ERROR;
      }
    }

    /* Place 0_15_4 */
    case P0_15_4: {

      switch (event.type) {
        case PRINTF: {
          /* On change l'état... */
            current->place = P0_15_4;
            return P0_15_4;
        }
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = PGLOBAL_EXIT;
            return P0_15_4;
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

