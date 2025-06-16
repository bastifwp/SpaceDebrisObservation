/* Crossover routines */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "global.h"
# include "rand.h"


/* OX crossover: 
Se seleccionan dos indices, dentro de esos dos indices se pasan al hijo
Luego se agregan los genes del padre2 desde el corte hasta llegar al start dando la vuelta.

*/
void crossover_OX(individual *parent1, individual *parent2, individual *child1, individual *child2, problem_instance *pi) {

    /* Vemos si se realiza el crossover de acuerdo con su probabilidad */
    if (randomperc() < pcross){

        ncross++;

        int i, start, end, j, k;
        int *taken1 = (int *)calloc(pi->nObj, sizeof(int));  /*calloc inicializa valores con 0*/
        int *taken2 = (int *)calloc(pi->nObj, sizeof(int));


        /*Elegimos dos puntos de corte al azar*/
        start = rnd(0, pi->nObj-1);
        end = rnd(0, pi->nObj -1);

        /* Aseguramos el orden*/
        if(start > end){
            int tmp = start;
            start = end;
            end = tmp;
        }

        /*Compiamos lo de al medio al child1 */
        for(i = start; i <= end; i++){
            child1->rep[i] = parent1->rep[i];
            taken1[parent1->rep[i]] = 1;
        }

        /*LLenamos el resto de child1 con los genes de parent2*/
        j = (end + 1) % pi->nObj; /*Para recorrer al padre2*/
        k = (end + 1) % pi->nObj; /*Para recorrer al child 1*/

        /*Se termina cuando se da la vuelta completa*/
        while(k != start){

            /*si no ha sido copiado entonces lo copiamos */
            if(!taken1[parent2->rep[j]]){
                child1->rep[k] = parent2->rep[j];
                k = (k+1) % pi->nObj;
            }

            /*Pasamos al siguiente elemento del padre*/
            j = (j+1) % pi->nObj;
        }


        /* Ahora hacemos lo mismo para el child2:*/
        for (i = start; i <= end; i++) {
            child2->rep[i] = parent2->rep[i];
            taken2[parent2->rep[i]] = 1;
        }
        j = (end + 1) % pi->nObj;
        k = (end + 1) % pi->nObj;
        while (k != start) {
            if (!taken2[parent1->rep[j]]) {
                child2->rep[k] = parent1->rep[j];
                k = (k + 1) % pi->nObj;
            }
            j = (j + 1) % pi->nObj;
        }

        free(taken1);
        free(taken2);
    }    
    
    /*Si no se realiza mutación entonces simplemente se copia */
    else
    {   
        int i;
        for (i=0; i<pi->nObj; i++)
        {
            child1->rep[i] = parent1->rep[i];
            child2->rep[i] = parent2->rep[i];
        }
    }
}





/* Function to cross two individuals */
void crossover (individual *parent1, individual *parent2, individual *child1, individual *child2, problem_instance *pi)
{

    crossover_OX(parent1, parent2, child1, child2, pi);

    return;
}


