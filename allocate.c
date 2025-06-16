/* Memory allocation and deallocation routines */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "global.h"
# include "rand.h"

/* Function to allocate memory to a population */
void allocate_memory_pop (population *pop, int size, problem_instance *pi)
{
    int i;
    pop->ind = (individual *)malloc(size*sizeof(individual));
    for (i=0; i<size; i++)
    {
        allocate_memory_ind (&(pop->ind[i]), pi);
    }
    return;
}

/* Function to allocate memory to an individual */
void allocate_memory_ind (individual *ind, problem_instance *pi)
{

    /* Creamos espacio para la representación */
    ind->rep = (int *)malloc(pi->nObj*sizeof(int));
    
    /*Creamos espacio para los objetivos*/
    ind->obj = (double *)malloc(2*sizeof(double));
    return;

}

/* Function to deallocate memory to a population */
void deallocate_memory_pop (population *pop, int size, problem_instance *pi)
{
    int i;
    for (i=0; i<size; i++)
    {
        deallocate_memory_ind (&(pop->ind[i]), pi);
    }
    free (pop->ind);
    return;
}

/* Function to deallocate memory to an individual */
void deallocate_memory_ind (individual *ind, problem_instance *pi)
{
    free(ind->rep);
    free(ind->obj);
    return;
}
