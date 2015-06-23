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
      state_t struct_state;
      /* Duplique l'�tat courant du process (Pour la transition structurelle 0_15_2_to_0_15_4 */
      struct_state = dup_state(*current);
      struct_state.place = P0_15_4;
      add_state(process, struct_state);

      switch (event.type) {
        default: return ERROR;
      }
    }

    /* Place 0_15_4 */
    case P0_15_4: {
      state_t struct_state;
      /* Duplique l'�tat courant du process (Pour la transition structurelle 0_15_6_to_0_15_EXIT */
      struct_state = dup_state(*current);
      struct_state.place = PGLOBAL_EXIT;
      add_state(process, struct_state);

      switch (event.type) {
        case PRINTF: {
          /* On change l'�tat... */
            current->place = P0_15_4;
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

