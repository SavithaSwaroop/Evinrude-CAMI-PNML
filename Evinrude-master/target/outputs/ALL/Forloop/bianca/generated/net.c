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

    /* Place 4_162_4 */
    case P4_162_4: {
      state_t struct_state;
      /* Duplique l'état courant du process (Pour la transition structurelle 4_162_4_to_4_162_5 */
      struct_state = dup_state(*current);
      struct_state.place = PGLOBAL_EXIT;
      add_state(process, struct_state);

      switch (event.type) {
        case PRINTF: {
          /* On change l'état... */
            current->place = P4_162_4;
            return P4_162_4;
        }
        default: return ERROR;
      }
    }

    /* Place 4_162_ENTRY */
    case P4_162_ENTRY: {
      state_t struct_state;
      /* Duplique l'état courant du process (Pour la transition structurelle 4_162_ENTRY_to_4_162_2 */
      struct_state = dup_state(*current);
      struct_state.place = P4_162_4;
      add_state(process, struct_state);

      switch (event.type) {
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

