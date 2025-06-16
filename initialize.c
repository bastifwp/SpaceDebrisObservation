/* Data initializtion routines */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "global.h"
# include "rand.h"

/* Function to initialize a population randomly */
void initialize_pop (population *pop, problem_instance *pi)
{
    int i;
    for (i=0; i<popsize; i++)
    {
        initialize_ind (&(pop->ind[i]), pi);
    }
    return;
}

/* Function to initialize an individual randomly */
void initialize_ind (individual *ind, problem_instance *pi)
{

    /*Creamos una permutación aleatorea*/
    int i;
    for(i=0; i <  pi->nObj; i++){
        ind->rep[i] = i;
    }

    /*Ahora le hacemos un swap con uno random*/
    for(i = 0; i < pi->nObj; i++){

        /*Elegimos uno random*/
        int j = rnd(0, pi->nObj-1);

        /*Realizamos el swap*/
        int temp = ind->rep[i];
        ind->rep[i] = ind->rep[j];
        ind->rep[j] = temp;
    }

    /*Le asignamos el constr_violation = 0*/
    ind->constr_violation = 0;
    
    return;
}

