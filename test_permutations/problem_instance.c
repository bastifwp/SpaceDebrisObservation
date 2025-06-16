/* Routine for evaluating population members  */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include "global.h"




int getIndexbyId(int id, problem_instance pi, char* type){

    if(type == "objeto"){
        int i; 
        for(i=0; i <  pi.nObj; i++){
            if(pi.objetos[i].id == id){
                return i;
            }
        }
        printf("ERROR: objeto %d Not found! \n", id);

    }else if(type == "telescopio"){

        int i; 
        for(i=0; i <  pi.nTel; i++){
            if(pi.telescopios[i].id == id){
                return i;
            }
        }
        printf("ERROR: telescopio %d Not found! \n", id);
    }
}




void printProblemInstance(problem_instance *pi){

    /*Mostramos los objetos*/
    printf("Cantidad Objetos: %d\n", pi->nObj);
    int i, j;
    for(i=0; i < pi->nObj; i++){
        printf("Objeto %d:\n", pi->objetos[i].id);
        printf("l: %d\n", pi->objetos[i].l);
        printf("O: %d\n", pi->objetos[i].O);
        printf("D: %d\n", pi->objetos[i].D);
        printf("Start_cost: %d\n", pi->objetos[i].start_cost);
        printf("\n");
    }


    /* Mostramos los telescopios */
    printf("Cantidad telescopios: %d\n", pi->nTel);
    for(i=0; i < pi->nTel; i++){
        printf("Telescopio %d: \n", pi->nTel);
    }

    /* Mostramos el parámetro de giro */
    printf("Costos de giro: \n");
    for(i=0; i < pi->nObj; i++){
        for(j=0; j < pi->nObj; j++){
            printf("%d ", pi->giro[i][j]);
        }
        printf("\n");
    }

}





