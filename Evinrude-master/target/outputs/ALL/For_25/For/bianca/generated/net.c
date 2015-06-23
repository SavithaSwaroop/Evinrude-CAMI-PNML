#include "net.h"

/*********************************************************************************
 * D�claration statiques des ressources globales utilis�es par l'application
 */
void init_resources(global_table_t* global_table) {
}

/*********************************************************************************
 * D�termine le marquage apr�s le franchissement d'une transition sensible � EVENT
 */
unsigned int next(global_table_t* global_table, process_t* process, state_t* current, event_t event) {

  switch (current->place) {

    /* Place 0_15_ENTRY */
    case P0_15_ENTRY: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'�tat... */
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
          /* On change l'�tat... */
            current->place = P0_15_4;
            return P0_15_4;
        }
        case __BUILTIN_PUTS: {
          /* On change l'�tat... */
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
 * Met � jour le marquage apr�s le franchissement d'apr�s les informations r�cup�r�es
 */
void update(global_table_t* global_table, state_t* current, event_t event) {
  switch (current->previous) {
    default: return;
  }
}

