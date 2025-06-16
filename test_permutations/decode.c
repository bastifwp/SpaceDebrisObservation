/* El objetivo de esta cosa será procesar a un individuo de una población */
/* Esto significa llenar las colas de los telescopios de acuerdo con la permutación */



# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "global.h"





/* función para decodificar una permutación tal que se llenen las colas de los telescopios para después evaluar */
void decode_perm (int *perm, problem_instance *pi)
{
    /*Por cada objeto recorremos todos los telescopios hasta que en alguno se pueda ingresar */
    int i, j;
    for(i = 0; i < pi->nObj; i++){
        objeto* actual_obj = &(pi->objetos[perm[i]]);
        int added = 0;
        
        for(j = 0; j < pi->nTel; j++){            
            telescopio* actual_tel  = &(pi->telescopios[j]);


            /*Intentamos ingresarlo al final de la cola */
            if(enqueue_end(actual_tel, actual_obj, pi)){
                printf("\n%d Added at end", actual_obj->id);
                added = 1;
                break;
            }

            /*Intentamos ingresarlo al principio de la cola */
            if(enqueue_start(actual_tel, actual_obj, pi)){
                printf("\n%d Added at end", actual_obj->id);
                added = 1;
                break;
            }
            
            /*Intentamos ingresarlo entremedio de los objetos */
            if(enqueue_middle(actual_tel, actual_obj, pi)){
                printf("\n%d Added at middle", actual_obj->id);
                added = 1;
                break;
            }

        }

        /* Si después de recorrer todos los telescopios no se agrego entonces meterlo en una lista de unnobserved */
        /* TODO: En cada individuo agregar una lista unobserved */

    }

    return;
}
