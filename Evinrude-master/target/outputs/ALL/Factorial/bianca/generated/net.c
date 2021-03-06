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

    /* Place 2_121_EXIT */
    case P2_121_EXIT: {
      local_resource_t* local_resource0 = get_local_resource(current, P2_121_4_160_FACTORIAL_PATH);
      local_resource_t* local_resource1 = get_local_resource(current, P2_108_4_76_FACTORIAL_PATH);

      /* Transition return_2_121_4_160_factorial */
      if ((local_resource0 == NULL) && (local_resource0 == NULL) && 1) {
        VERBOSE("Franchissement de la transition : return_2_121_4_160_factorial\n");
        state_t return_state = dup_state(*current);


      /* On change l'�tat... */
        return_state.place = P2_121_EXIT;
        add_state(process, return_state);
      }

      /* Transition return_2_108_4_76_factorial */
      if ((local_resource1 != NULL) && (local_resource0 == NULL) && 1) {
        VERBOSE("Franchissement de la transition : return_2_108_4_76_factorial\n");
        state_t return_state = dup_state(*current);

        /* On consomme la ressource (2_108_4_76_factorial_path) */
        delete_local_resource(&return_state, local_resource1, 1);

      /* On change l'�tat... */
        return_state.place = P2_108_4_76_FACTORIAL_RETURN;
        add_state(process, return_state);
      }

      switch (event.type) {
        default: return ERROR;
      }
    }

    /* Place 2_108_ENTRY */
    case P2_108_ENTRY: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'�tat... */
            current->place = P2_108_2_58___BUILTIN_PUTS_POST;
            return P2_108_ENTRY;
        }
        default: return ERROR;
      }
    }

    /* Place 2_108_4_76_factorial_return */
    case P2_108_4_76_FACTORIAL_RETURN: {

      switch (event.type) {
        case PRINTF: {
          /* On change l'�tat... */
            current->place = PGLOBAL_EXIT;
            return P2_108_4_76_FACTORIAL_RETURN;
        }
        default: return ERROR;
      }
    }

    /* Place 2_121_ENTRY */
    case P2_121_ENTRY: {
      state_t struct_state;
      /* Duplique l'�tat courant du process (Pour la transition structurelle 2_121_2_to_2_121_3 */
      struct_state = dup_state(*current);
      struct_state.place = P2_121_EXIT;
      add_state(process, struct_state);
      state_t caller_state;

      caller_state = dup_state(*current);
      caller_state.place = P2_121_ENTRY;
      add_local_resource(&caller_state, P2_121_4_160_FACTORIAL_PATH, 1);
      add_state(process, caller_state);

      switch (event.type) {
        default: return ERROR;
      }
    }

    /* Place 2_108_2_58___builtin_puts_post */
    case P2_108_2_58___BUILTIN_PUTS_POST: {
      state_t caller_state;

      caller_state = dup_state(*current);
      caller_state.place = P2_121_ENTRY;
      add_local_resource(&caller_state, P2_108_4_76_FACTORIAL_PATH, 1);
      add_state(process, caller_state);

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'�tat... */
            current->place = PGLOBAL_EXIT;
            return P2_108_2_58___BUILTIN_PUTS_POST;
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

