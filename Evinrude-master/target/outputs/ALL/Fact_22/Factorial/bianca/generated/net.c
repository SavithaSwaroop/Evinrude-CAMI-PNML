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
            current->place = P0_15_2_58___BUILTIN_PUTS_POST;
            return P0_15_ENTRY;
        }
        default: return ERROR;
      }
    }

    /* Place 0_15_2_58___builtin_puts_post */
    case P0_15_2_58___BUILTIN_PUTS_POST: {
      state_t caller_state;

      caller_state = dup_state(*current);
      caller_state.place = P0_28_ENTRY;
      add_local_resource(&caller_state, P0_15_4_76_FACTORIAL_PATH, 1);
      add_state(process, caller_state);

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = PGLOBAL_EXIT;
            return P0_15_2_58___BUILTIN_PUTS_POST;
        }
        default: return ERROR;
      }
    }

    /* Place 0_28_EXIT */
    case P0_28_EXIT: {
      local_resource_t* local_resource0 = get_local_resource(current, P0_15_4_76_FACTORIAL_PATH);
      local_resource_t* local_resource1 = get_local_resource(current, P0_28_4_160_FACTORIAL_PATH);

      /* Transition return_0_15_4_76_factorial */
      if ((local_resource0 != NULL) && (local_resource1 == NULL) && 1) {
        VERBOSE("Franchissement de la transition : return_0_15_4_76_factorial\n");
        state_t return_state = dup_state(*current);

        /* On consomme la ressource (0_15_4_76_factorial_path) */
        delete_local_resource(&return_state, local_resource0, 1);

      /* On change l'état... */
        return_state.place = P0_15_4_76_FACTORIAL_RETURN;
        add_state(process, return_state);
      }

      /* Transition return_0_28_4_160_factorial */
      if ((local_resource1 == NULL) && (local_resource1 == NULL) && 1) {
        VERBOSE("Franchissement de la transition : return_0_28_4_160_factorial\n");
        state_t return_state = dup_state(*current);


      /* On change l'état... */
        return_state.place = P0_28_EXIT;
        add_state(process, return_state);
      }

      switch (event.type) {
        default: return ERROR;
      }
    }

    /* Place 0_15_4_76_factorial_return */
    case P0_15_4_76_FACTORIAL_RETURN: {

      switch (event.type) {
        case PRINTF: {
          /* On change l'état... */
            current->place = PGLOBAL_EXIT;
            return P0_15_4_76_FACTORIAL_RETURN;
        }
        default: return ERROR;
      }
    }

    /* Place 0_28_ENTRY */
    case P0_28_ENTRY: {
      state_t struct_state;
      /* Duplique l'état courant du process (Pour la transition structurelle 0_28_2_to_0_28_3 */
      struct_state = dup_state(*current);
      struct_state.place = P0_28_EXIT;
      add_state(process, struct_state);
      state_t caller_state;

      caller_state = dup_state(*current);
      caller_state.place = P0_28_ENTRY;
      add_local_resource(&caller_state, P0_28_4_160_FACTORIAL_PATH, 1);
      add_state(process, caller_state);

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

