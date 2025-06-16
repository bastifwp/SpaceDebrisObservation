/* NSGA-II routine (implementation of the 'main' function) */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>

# include "global.h"


int main (int argc, char **argv)
{
    
    problem_instance *pi = malloc (sizeof(problem_instance));

    if (argc< 3)
    {
        /*printf("\n Usage ./nsga2r instance_route random_seed popsize ngen nobj pcross_bin pmut_bin\n./nsga2r 0.123 b-Instancia14_cap2_relacion7UnoUnoUnoTodosDistintos.dat 100 100 2 0.6 0.01\n");*/
        /* printf("\n For debug queues: ./nsga2r 0.123 test_data.dat 100 100 2 \n"); */
        printf("\n Usage ./main instance_file permutation_file \n Example:");
        printf("\n ./main test_data.dat perm.txt\n");
        exit(1);
    }

    /*Lectura de la instancia*/
    char* instance_route = argv[1];
    readInputFile(instance_route, pi);


    /*Lectura de permutación*/
    char* permutation_route = argv[2];
    int* perm = malloc(pi->nObj*sizeof(int));
    readPermFile(permutation_route, perm, pi->nObj);

    /* Asignamos los objetos a los telescopios */
    restart_variables(pi);
    evaluate_ind(perm, pi);

    /* Vemos que tiene cada telescopio */
    int i;
    for(i=0; i < pi->nTel; i++){
        print_queue( &(pi->telescopios[i]), pi);
    }


    free(perm);
    free(pi);
    

    return (0);
}
