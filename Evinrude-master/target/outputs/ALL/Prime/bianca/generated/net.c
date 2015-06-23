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

    /* Place 7_216_2_94___builtin_puts_post */
    case P7_216_2_94___BUILTIN_PUTS_POST: {
      state_t struct_state;
      /* Duplique l'état courant du process (Pour la transition structurelle 7_216_2_to_7_216_4 */
      struct_state = dup_state(*current);
      struct_state.place = P7_216_12;
      add_state(process, struct_state);

      switch (event.type) {
        case PRINTF: {
          /* On change l'état... */
            current->place = P7_216_3_106_PRINTF_POST;
            return P7_216_2_94___BUILTIN_PUTS_POST;
        }
        default: return ERROR;
      }
    }

    /* Place 7_216_ENTRY */
    case P7_216_ENTRY: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = P7_216_2_94___BUILTIN_PUTS_POST;
            return P7_216_ENTRY;
        }
        default: return ERROR;
      }
    }

    /* Place 7_216_12 */
    case P7_216_12: {
      state_t struct_state;
      /* Duplique l'état courant du process (Pour la transition structurelle 7_216_14_to_7_216_EXIT */
      struct_state = dup_state(*current);
      struct_state.place = PGLOBAL_EXIT;
      add_state(process, struct_state);

      switch (event.type) {
        case PRINTF: {
          /* On change l'état... */
            current->place = P7_216_12;
            return P7_216_12;
        }
        default: return ERROR;
      }
    }

    /* Place 7_216_3_106_printf_post */
    case P7_216_3_106_PRINTF_POST: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = P7_216_12;
            return P7_216_3_106_PRINTF_POST;
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

