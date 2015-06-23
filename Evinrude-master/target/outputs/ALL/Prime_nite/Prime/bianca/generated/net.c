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

    /* Place 0_39_2_94___builtin_puts_post */
    case P0_39_2_94___BUILTIN_PUTS_POST: {
      state_t struct_state;
      /* Duplique l'�tat courant du process (Pour la transition structurelle 0_39_2_to_0_39_4 */
      struct_state = dup_state(*current);
      struct_state.place = P0_39_12;
      add_state(process, struct_state);

      switch (event.type) {
        case PRINTF: {
          /* On change l'�tat... */
            current->place = P0_39_3_107___BUILTIN_PUTS_PRE;
            return P0_39_2_94___BUILTIN_PUTS_POST;
        }
        default: return ERROR;
      }
    }

    /* Place 0_39_3_107___builtin_puts_pre */
    case P0_39_3_107___BUILTIN_PUTS_PRE: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'�tat... */
            current->place = P0_39_12;
            return P0_39_3_107___BUILTIN_PUTS_PRE;
        }
        default: return ERROR;
      }
    }

    /* Place 0_39_ENTRY */
    case P0_39_ENTRY: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'�tat... */
            current->place = P0_39_2_94___BUILTIN_PUTS_POST;
            return P0_39_ENTRY;
        }
        default: return ERROR;
      }
    }

    /* Place 0_39_12 */
    case P0_39_12: {
      state_t struct_state;
      /* Duplique l'�tat courant du process (Pour la transition structurelle 0_39_12_to_0_39_13 */
      struct_state = dup_state(*current);
      struct_state.place = PGLOBAL_EXIT;
      add_state(process, struct_state);

      switch (event.type) {
        case PRINTF: {
          /* On change l'�tat... */
            current->place = P0_39_12;
            return P0_39_12;
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

