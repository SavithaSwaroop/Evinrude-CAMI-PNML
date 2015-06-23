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

    /* Place 5_169_2_74_printf_pre */
    case P5_169_2_74_PRINTF_PRE: {

      switch (event.type) {
        case PRINTF: {
          /* On change l'état... */
            current->place = P5_169_2_75_PRINTF_PRE;
            return P5_169_2_74_PRINTF_PRE;
        }
        default: return ERROR;
      }
    }

    /* Place 5_169_2_77_printf_pre */
    case P5_169_2_77_PRINTF_PRE: {

      switch (event.type) {
        case PRINTF: {
          /* On change l'état... */
            current->place = PGLOBAL_EXIT;
            return P5_169_2_77_PRINTF_PRE;
        }
        default: return ERROR;
      }
    }

    /* Place 5_169_2_73_printf_pre */
    case P5_169_2_73_PRINTF_PRE: {

      switch (event.type) {
        case PRINTF: {
          /* On change l'état... */
            current->place = P5_169_2_74_PRINTF_PRE;
            return P5_169_2_73_PRINTF_PRE;
        }
        default: return ERROR;
      }
    }

    /* Place 5_169_2_75_printf_pre */
    case P5_169_2_75_PRINTF_PRE: {

      switch (event.type) {
        case PRINTF: {
          /* On change l'état... */
            current->place = P5_169_2_77_PRINTF_PRE;
            return P5_169_2_75_PRINTF_PRE;
        }
        default: return ERROR;
      }
    }

    /* Place 5_169_ENTRY */
    case P5_169_ENTRY: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = P5_169_2_73_PRINTF_PRE;
            return P5_169_ENTRY;
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

