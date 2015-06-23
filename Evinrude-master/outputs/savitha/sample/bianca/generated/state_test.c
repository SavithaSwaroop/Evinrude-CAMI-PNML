#include <time.h>
#include "../state.h"
#include "../global_state.h"

int main (void) {
        state_t vec1, vec2, vec3;
        binding_t b;
        int i;
       
        srand(time(NULL));
        fprintf(stdout, "--- Debut\n");
       
        /* Creation du vecteur */
        vec1 = create_state();
        vec2 = create_state();
        vec3 = create_state();
       
        /* Remplissage */
        for (i=0; i<15; i++) {
                b.id = i;
                b.place = (int) rand() % 40;
                add_binding(&vec1, b);
                add_binding(&vec3, b);
        }
       
        /* Remplissage */
        for (i=0; i<15; i++) {
                b.id = i;
                b.place = (int) rand() % 40;
                add_binding(&vec2, b);
        }
       
        print_state(vec1);
        print_state(vec2);

        /* Suppression */
        for (i=0; i<10; i++) {
                int r = (int) rand() % 15;
                fprintf(stdout,"Suppression du %d\n",r);
                erase_binding(&vec1, find_binding(vec1,r));
                erase_binding(&vec3, find_binding(vec3,r));
        }

        /* Suppression */
        for (i=0; i<10; i++) {
                int r = (int) rand() % 15;
                fprintf(stdout,"Suppression du %d\n",r);
                erase_binding(&vec2, find_binding(vec2,r));
        }

        print_state(vec1);
        print_state(vec2);
       
        /* Comparaison */
        if (compare_states(&vec1, &vec2)) { fprintf(stdout, "VEC1 = VEC2\n"); } else { fprintf(stdout, "VEC1 != VEC2\n"); }
        if (compare_states(&vec1, &vec3)) { fprintf(stdout, "VEC1 = VEC3\n"); } else { fprintf(stdout, "VEC1 != VEC3\n"); }

        return 1;
}
