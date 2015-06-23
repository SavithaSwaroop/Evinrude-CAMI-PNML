#include "net.h"

/*********************************************************************************
 * Déclaration statiques des ressources globales utilisées par l'application
 */
void init_resources(global_table_t* global_table) {
  declare_global_resource(global_table, PRES_ATTACHED_THREADS);
}

/*********************************************************************************
 * Détermine le marquage après le franchissement d'une transition sensible à EVENT
 */
unsigned int next(global_table_t* global_table, process_t* process, state_t* current, event_t event) {

  switch (current->place) {

    /* Place 0_12_ENTRY */
    case P0_12_ENTRY: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = PGLOBAL_EXIT;
            return P0_12_ENTRY;
        }
        default: return ERROR;
      }
    }

    /* Place 0_34_ENTRY */
    case P0_34_ENTRY: {

      switch (event.type) {
        case PRINTF: {
          /* On change l'état... */
            current->place = P0_34_2_155_PTHREAD_CREATE_PRE;
            return P0_34_ENTRY;
        }
        default: return ERROR;
      }
    }

    /* Place 0_34_5_183_pthread_join_pre */
    case P0_34_5_183_PTHREAD_JOIN_PRE: {

      switch (event.type) {
        case PTHREAD_JOIN: {
          global_resource_t* global_resource0 = fetch_global_resource(global_table, PRES_ATTACHED_THREADS);
          assert(global_resource0 != NULL);
          global_token_t* cond0 = get_global_token(global_resource0, event.id);
          unsigned int state1 = PGLOBAL_EXIT;
          process_t* cond1 = find_process_state(global_table, event.id, state1);
          /* Gestion des noeuds early */

          if ((cond0 != NULL) && (cond1 != NULL) && 1) {
            /* On consomme les ressources */
            delete_global_token(global_resource0, cond0);
            delete_state(cond1, find_state(cond1, state1));
            /* On produit les ressources (non-dynamiques) */
            /* On change l'état... */
            current->place = P0_34_5_183_PTHREAD_JOIN_POST;
            return P0_34_5_183_PTHREAD_JOIN_PRE;
          }
        }
        default: return ERROR;
      }
    }

    /* Place 0_34_5_183_pthread_join_post */
    case P0_34_5_183_PTHREAD_JOIN_POST: {

      switch (event.type) {
        case PRINTF: {
          /* On change l'état... */
            current->place = PGLOBAL_EXIT;
            return P0_34_5_183_PTHREAD_JOIN_POST;
        }
        case __BUILTIN_FWRITE: {
          /* On change l'état... */
            current->place = PGLOBAL_EXIT;
            return P0_34_5_183_PTHREAD_JOIN_POST;
        }
        default: return ERROR;
      }
    }

    /* Place 0_34_2_155_pthread_create_pre */
    case P0_34_2_155_PTHREAD_CREATE_PRE: {

      switch (event.type) {
        case PTHREAD_CREATE: {
          /* On change l'état... */
            current->place = P0_34_2_155_PTHREAD_CREATE_POST;
            return P0_34_2_155_PTHREAD_CREATE_PRE;
        }
        default: return ERROR;
      }
    }

    /* Place 0_34_2_155_pthread_create_post */
    case P0_34_2_155_PTHREAD_CREATE_POST: {

      switch (event.type) {
        case __BUILTIN_PUTS: {
          /* On change l'état... */
            current->place = P0_34_5_183_PTHREAD_JOIN_PRE;
            return P0_34_2_155_PTHREAD_CREATE_POST;
        }
        case __BUILTIN_FWRITE: {
          /* On change l'état... */
            current->place = PGLOBAL_EXIT;
            return P0_34_2_155_PTHREAD_CREATE_POST;
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
    /* Place 0_34_2_155_PTHREAD_CREATE_PRE */
    case P0_34_2_155_PTHREAD_CREATE_PRE: {
      switch (event.type) {
        case PTHREAD_CREATE: {
          process_t* newprocess = find_process_id(global_table, event.id);
          if (newprocess == NULL) {
            newprocess = init_process(event.id, P0_12_ENTRY);
            add_process(global_table, newprocess);
          } else {
            newprocess->context = TRUE;
            state_t new_state = create_state(P0_12_ENTRY);
            add_state(newprocess, new_state);
          }
          global_resource_t* global_resource = fetch_global_resource(global_table, PRES_ATTACHED_THREADS);
          assert(global_resource != NULL);
          set_global_token(global_resource, event.id, 1);
          return;
        }
        default: return;
      }
    }
    default: return;
  }
}

