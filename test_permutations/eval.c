/* Routine for evaluating population members  */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "global.h"



/* Routine to evaluate objective function values and constraints for an individual */
void evaluate_ind (int* perm, problem_instance *pi){

    /*printf("\nLets restart the variables");*/

    /* Borramos lo que haya estado en la cola */
    restart_variables(pi);

    /*Insertamos los objetos de la permutación en las colas */
    decode_perm(perm, pi);

    /*Ahora podemos evaluar recorriendo todas las colas de telescopios */
    int i;
    double total_value = 0;
    double total_cost = 0;
    

    for(i=0; i < pi->nTel; i++){
    
        objeto* actual = pi->telescopios[i].queue;

        /*Verificamos que haya un objeto en la cola*/
        if(actual){
            total_cost += actual->start_cost;
        }

        /* Si no hay entonces hay que salir del ciclo*/
        else{
            break;
        }
    
        /*Recorremos la cola del telescopio actual*/
        while(actual){
            total_value += actual ->l;

            objeto* next = actual->next;

            if(next == NULL) break;

            /*Ahora sumamos el costo de pasar al siguiente*/
            total_cost += pi->giro[actual->id][next->id];

            /*Pasamos al siguiente objeto*/
            actual = next;           
        }
    }
    
    /* Luego de pasar por todo asignamos los valores de las funciones objetivo */
    
    /*Mostamos la permutación y después los valores de la función objetivo*/
    printf("\nPermutation: ");
    for(i=0; i < pi->nObj; i++){
        printf("%d ", perm[i]);
    }
    printf("\t value: %f\t cost: %f\t", -total_value, total_cost);

    return;
}


