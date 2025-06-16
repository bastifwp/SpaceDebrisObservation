/* Mutation routines */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "global.h"
# include "rand.h"

/* Function to perform mutation in a population */
void mutation_pop (population *pop, problem_instance *pi)
{
    int i;
    for (i=0; i<popsize; i++)
    {
        mutation_ind(&(pop->ind[i]), pi);
    }
    return;
}


/*Función para mutar una permutación (swap simple)*/
void random_swap(individual *ind, problem_instance *pi){
    
    /*Obtenemos un número entre 0 y 1 para ver si mutarlo*/
    double rand_val = randomperc();

    if(rand_val < pmut){
        nmut++;

        int i = rnd(0, pi->nObj-1);
        int j = rnd(0, pi->nObj-1);

        while(i == j){
            j = rnd(0, pi->nObj-1);
        }

        int k;
        
        /*Intercambiamos la permutacion*/
        int temp = ind->rep[i];
        ind->rep[i] = ind->rep[j];
        ind->rep[j] = temp;

    }

}


/* Function to perform mutation of an individual */
void mutation_ind (individual *ind, problem_instance *pi)
{
    random_swap(ind, pi);
    return;
}

