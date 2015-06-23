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

    /* Place 3_146_7 */
    case P3_146_7: {
      state_t struct_state;
      /* Duplique l'état courant du process (Pour la transition structurelle 3_146_7_to_3_146_8 */
      struct_state = dup_state(*current);
      struct_state.place = PGLOBAL_EXIT;
      add_state(process, struct_state);

      switch (event.type) {
        case PRINTF: {
          /* On change l'état... */
            current->place = P3_146_7;
            return P3_146_7;
        }
        default: return ERROR;
      }
    }

    /* Place 3_146_ENTRY */
    case P3_146_ENTRY: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = P3_146_2_73___BUILTIN_PUTS_POST;
            return P3_146_ENTRY;
        }
        default: return ERROR;
      }
    }

    /* Place 3_146_2_73___builtin_puts_post */
    case P3_146_2_73___BUILTIN_PUTS_POST: {

      switch (event.type) {
        case PRINTF: {
          /* On change l'état... */
            current->place = P3_146_7;
            return P3_146_2_73___BUILTIN_PUTS_POST;
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

