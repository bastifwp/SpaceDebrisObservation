/* Routine for mergeing two populations */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "global.h"
# include "rand.h"

/* Routine to merge two populations into one */
void merge(population *pop1, population *pop2, population *pop3, problem_instance *pi)
{
    int i, k;
    for (i=0; i<popsize; i++)
    {
        copy_ind (&(pop1->ind[i]), &(pop3->ind[i]), pi);
    }
    for (i=0, k=popsize; i<popsize; i++, k++)
    {
        copy_ind (&(pop2->ind[i]), &(pop3->ind[k]), pi);
    }
    return;
}


/* Routine to copy an individual 'ind1' into another individual 'ind2' */
void copy_ind (individual *ind1, individual *ind2, problem_instance *pi)
{
    
    int i;

    /* Copiamos variables básicas */
    ind2->rank = ind1->rank;
    ind2->constr_violation = ind1->constr_violation;
    ind2->crowd_dist = ind1->crowd_dist;

    /* Copiamos la representación */
    for(i = 0; i < pi->nObj; i++){
        ind2->rep[i] = ind1->rep[i];
    }

    /* Copiamos las funciones objetivo */
    for (i=0; i<nobj; i++){
        ind2->obj[i] = ind1->obj[i];
    }

    return;
}
