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

    /* Place 0_45_5_144___builtin_puts_post */
    case P0_45_5_144___BUILTIN_PUTS_POST: {
      state_t struct_state;
      /* Duplique l'état courant du process (Pour la transition structurelle 0_45_12_to_0_45_13 */
      struct_state = dup_state(*current);
      struct_state.place = P0_45_13;
      add_state(process, struct_state);

      switch (event.type) {
        case PRINTF: {
          /* On change l'état... */
            current->place = P0_45_13;
            return P0_45_5_144___BUILTIN_PUTS_POST;
        }
        default: return ERROR;
      }
    }

    /* Place 0_45_2_119_printf_post */
    case P0_45_2_119_PRINTF_POST: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = P0_45_5_144___BUILTIN_PUTS_POST;
            return P0_45_2_119_PRINTF_POST;
        }
        default: return ERROR;
      }
    }

    /* Place 0_45_13 */
    case P0_45_13: {
      state_t struct_state;
      /* Duplique l'état courant du process (Pour la transition structurelle 0_45_13_to_0_45_15 */
      struct_state = dup_state(*current);
      struct_state.place = PGLOBAL_EXIT;
      add_state(process, struct_state);

      switch (event.type) {
        case PRINTF: {
          /* On change l'état... */
            current->place = PGLOBAL_EXIT;
            return P0_45_13;
        }
        default: return ERROR;
      }
    }

    /* Place 0_45_ENTRY */
    case P0_45_ENTRY: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = P0_45_2_116___BUILTIN_PUTS_POST;
            return P0_45_ENTRY;
        }
        default: return ERROR;
      }
    }

    /* Place 0_45_2_116___builtin_puts_post */
    case P0_45_2_116___BUILTIN_PUTS_POST: {

      switch (event.type) {
        case PRINTF: {
          /* On change l'état... */
            current->place = P0_45_2_119_PRINTF_POST;
            return P0_45_2_116___BUILTIN_PUTS_POST;
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

