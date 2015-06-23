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

    /* Place 0_20_ENTRY */
    case P0_20_ENTRY: {

    }

    /* Place 0_12_EXIT */
    case P0_12_EXIT: {

    }

    /* Place 0_18_ENTRY */
    case P0_18_ENTRY: {

    }

    /* Place 0_5_EXIT */
    case P0_5_EXIT: {

    }

    /* Place 0_16_EXIT */
    case P0_16_EXIT: {

    }

    /* Place 0_1_ENTRY */
    case P0_1_ENTRY: {

    }

    /* Place 0_14_ENTRY */
    case P0_14_ENTRY: {

    }

    /* Place 0_20_EXIT */
    case P0_20_EXIT: {

    }

    /* Place 0_4_EXIT */
    case P0_4_EXIT: {

    }

    /* Place 0_10_EXIT */
    case P0_10_EXIT: {

    }

    /* Place 0_15_ENTRY */
    case P0_15_ENTRY: {

    }

    /* Place 0_19_EXIT */
    case P0_19_EXIT: {

    }

    /* Place 0_18_EXIT */
    case P0_18_EXIT: {

    }

    /* Place 0_16_ENTRY */
    case P0_16_ENTRY: {

    }

    /* Place 0_12_ENTRY */
    case P0_12_ENTRY: {

    }

    /* Place 0_17_EXIT */
    case P0_17_EXIT: {

    }

    /* Place 0_2_ENTRY */
    case P0_2_ENTRY: {

    }

    /* Place 0_22_EXIT */
    case P0_22_EXIT: {

    }

    /* Place 0_0_EXIT */
    case P0_0_EXIT: {

    }

    /* Place 0_1_EXIT */
    case P0_1_EXIT: {

    }

    /* Place 0_3_EXIT */
    case P0_3_EXIT: {

    }

    /* Place 0_24_9 */
    case P0_24_9: {
      state_t struct_state;
      /* Duplique l'état courant du process (Pour la transition structurelle 0_24_9_to_0_24_EXIT */
      struct_state = dup_state(*current);
      struct_state.place = P0_24_EXIT;
      add_state(process, struct_state);

      switch (event.type) {
        default: return ERROR;
      }
    }

    /* Place 0_24_8 */
    case P0_24_8: {
      state_t struct_state;
      /* Duplique l'état courant du process (Pour la transition structurelle 0_24_8_to_0_24_9 */
      struct_state = dup_state(*current);
      struct_state.place = P0_24_9;
      add_state(process, struct_state);

      switch (event.type) {
        default: return ERROR;
      }
    }

    /* Place 0_24_EXIT */
    case P0_24_EXIT: {

    }

    /* Place 0_24_7 */
    case P0_24_7: {
      state_t struct_state;
      /* Duplique l'état courant du process (Pour la transition structurelle 0_24_7_to_0_24_8 */
      struct_state = dup_state(*current);
      struct_state.place = P0_24_8;
      add_state(process, struct_state);
      /* Duplique l'état courant du process (Pour la transition structurelle 0_24_7_to_0_24_3 */
      struct_state = dup_state(*current);
      struct_state.place = P0_24_3;
      add_state(process, struct_state);

      switch (event.type) {
        default: return ERROR;
      }
    }

    /* Place 0_9_ENTRY */
    case P0_9_ENTRY: {

    }

    /* Place 0_24_6 */
    case P0_24_6: {
      state_t struct_state;
      /* Duplique l'état courant du process (Pour la transition structurelle 0_24_6_to_0_24_7 */
      struct_state = dup_state(*current);
      struct_state.place = P0_24_7;
      add_state(process, struct_state);

      switch (event.type) {
        default: return ERROR;
      }
    }

    /* Place 0_24_5 */
    case P0_24_5: {
      state_t struct_state;
      /* Duplique l'état courant du process (Pour la transition structurelle 0_24_5_to_0_24_6 */
      struct_state = dup_state(*current);
      struct_state.place = P0_24_6;
      add_state(process, struct_state);

      switch (event.type) {
        default: return ERROR;
      }
    }

    /* Place 0_24_4 */
    case P0_24_4: {
      state_t struct_state;
      /* Duplique l'état courant du process (Pour la transition structurelle 0_24_4_to_0_24_6 */
      struct_state = dup_state(*current);
      struct_state.place = P0_24_6;
      add_state(process, struct_state);

      switch (event.type) {
        default: return ERROR;
      }
    }

    /* Place 0_9_EXIT */
    case P0_9_EXIT: {

    }

    /* Place 0_24_3 */
    case P0_24_3: {
      state_t struct_state;
      /* Duplique l'état courant du process (Pour la transition structurelle 0_24_3_to_0_24_4 */
      struct_state = dup_state(*current);
      struct_state.place = P0_24_4;
      add_state(process, struct_state);
      /* Duplique l'état courant du process (Pour la transition structurelle 0_24_3_to_0_24_5 */
      struct_state = dup_state(*current);
      struct_state.place = P0_24_5;
      add_state(process, struct_state);

      switch (event.type) {
        default: return ERROR;
      }
    }

    /* Place 0_23_ENTRY */
    case P0_23_ENTRY: {

    }

    /* Place 0_22_ENTRY */
    case P0_22_ENTRY: {

    }

    /* Place 0_24_2 */
    case P0_24_2: {
      state_t struct_state;
      /* Duplique l'état courant du process (Pour la transition structurelle 0_24_2_to_0_24_7 */
      struct_state = dup_state(*current);
      struct_state.place = P0_24_7;
      add_state(process, struct_state);

      switch (event.type) {
        default: return ERROR;
      }
    }

    /* Place 0_13_EXIT */
    case P0_13_EXIT: {

    }

    /* Place 0_8_ENTRY */
    case P0_8_ENTRY: {

    }

    /* Place 0_6_ENTRY */
    case P0_6_ENTRY: {

    }

    /* Place 0_17_ENTRY */
    case P0_17_ENTRY: {

    }

    /* Place 0_8_EXIT */
    case P0_8_EXIT: {

    }

    /* Place 0_7_ENTRY */
    case P0_7_ENTRY: {

    }

    /* Place 0_19_ENTRY */
    case P0_19_ENTRY: {

    }

    /* Place 0_14_EXIT */
    case P0_14_EXIT: {

    }

    /* Place 0_4_ENTRY */
    case P0_4_ENTRY: {

    }

    /* Place 0_24_ENTRY */
    case P0_24_ENTRY: {
      state_t struct_state;
      /* Duplique l'état courant du process (Pour la transition structurelle 0_24_ENTRY_to_0_24_2 */
      struct_state = dup_state(*current);
      struct_state.place = P0_24_2;
      add_state(process, struct_state);

      switch (event.type) {
        default: return ERROR;
      }
    }

    /* Place 0_3_ENTRY */
    case P0_3_ENTRY: {

    }

    /* Place 0_11_EXIT */
    case P0_11_EXIT: {

    }

    /* Place 0_11_ENTRY */
    case P0_11_ENTRY: {

    }

    /* Place 0_2_EXIT */
    case P0_2_EXIT: {

    }

    /* Place 0_0_ENTRY */
    case P0_0_ENTRY: {

    }

    /* Place 0_6_EXIT */
    case P0_6_EXIT: {

    }

    /* Place 0_15_EXIT */
    case P0_15_EXIT: {

    }

    /* Place 0_21_ENTRY */
    case P0_21_ENTRY: {

    }

    /* Place 0_7_EXIT */
    case P0_7_EXIT: {

    }

    /* Place 0_5_ENTRY */
    case P0_5_ENTRY: {

    }

    /* Place 0_23_EXIT */
    case P0_23_EXIT: {

    }

    /* Place 0_21_EXIT */
    case P0_21_EXIT: {

    }

    /* Place 0_13_ENTRY */
    case P0_13_ENTRY: {

    }

    /* Place 0_10_ENTRY */
    case P0_10_ENTRY: {

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

