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

    /* Place 0_24_2_73___builtin_puts_post */
    case P0_24_2_73___BUILTIN_PUTS_POST: {

      switch (event.type) {
        case PRINTF: {
          /* On change l'�tat... */
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
          /* On change l'�tat... */
            current->place = PGLOBAL_EXIT;
            return P0_24_7;
        }
        case PRINTF: {
          /* On change l'�tat... */
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
          /* On change l'�tat... */
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
 * Met � jour le marquage apr�s le franchissement d'apr�s les informations r�cup�r�es
 */
void update(global_table_t* global_table, state_t* current, event_t event) {
  switch (current->previous) {
    default: return;
  }
}

