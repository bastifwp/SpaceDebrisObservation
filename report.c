/* Routines for storing population data into files */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "global.h"
# include "rand.h"

/* Function to print the information of a population in a file */
void report_pop (population *pop, FILE *fpt, problem_instance *pi)
{
    /*Recorremos los individuos */
    int i, j, k;
    for (i=0; i<popsize; i++)
    {
        /*Mostamos Las funciones obj*/
        for (j=0; j<nobj; j++)
        {
            fprintf(fpt,"%e\t",pop->ind[i].obj[j]);
        }

        /* Mostrmos la representación */
        for (j=0; j < pi->nObj; j++)
        {
            fprintf(fpt,"%d ",pop->ind[i].rep[j]);
        }
        

        fprintf(fpt,"\tRank: %d\t",pop->ind[i].rank);
        fprintf(fpt,"CDD: %e",pop->ind[i].crowd_dist);
        fprintf(fpt, "\n");
    }
    return;
}

/* Function to print the information of feasible and non-dominated population in a file */
void report_feasible (population *pop, FILE *fpt, problem_instance *pi)
{
    int i, j, k;
    for (i=0; i<popsize; i++)
    {
        if (pop->ind[i].constr_violation == 0.0 && pop->ind[i].rank==1)
        {
            for (j=0; j<nobj; j++)
            {
                fprintf(fpt,"%e\t",pop->ind[i].obj[j]);
            }

            /* Mostrmos la representación */
            for (j=0; j < pi->nObj; j++)
            {
                fprintf(fpt,"%d ",pop->ind[i].rep[j]);
            }
            

            fprintf(fpt,"\tRank: %d\t",pop->ind[i].rank);
            fprintf(fpt,"CDD: %e",pop->ind[i].crowd_dist);
            fprintf(fpt, "\n");
            }
    }
    return;
}
