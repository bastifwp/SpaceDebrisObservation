#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "global.h"


/* Función para resetear las variables de las colas */
void restart_variables(problem_instance *pi){

    /* Recorremos todos los objetivos y Telescopios para reiniciar las variables*/
    int i;
    for(i=0; i < pi->nObj; i++){
        pi->objetos[i].Sn = -1;
        pi->objetos[i].Cn = -1;
        pi->objetos[i].next = NULL;
    }

    for(i=0; i < pi->nTel; i++){
        pi->telescopios[i].T = -1;
        pi->telescopios[i].queue = NULL;
        pi->telescopios[i].front = -1;
        pi->telescopios[i].back = 0; /*Esto no sé si está bien */
    }
}

/* Función que incerta obj al final de la cola del telescopio, retorna 1 si se puede y 0 si no*/
int enqueue_end(telescopio *tel, objeto *obj, problem_instance *pi){

    /* Si la cola está vacía */
    if(tel->front == -1){   
        tel->front = obj->id;
        tel->queue = obj;
        tel->back = obj->id;

        /* Asignamos los valores de observación del objeto  y del telescopio */
        obj->Sn = obj->O;
        obj->Cn = obj->O + 100;
        tel->T = obj->Cn;

        return 1;

    }else{

        /* Vemos si podemos poner el objeto en el fianal de la cola */
        objeto* last = &(pi->objetos[tel->back]);
        if(obj->D - last->Cn >= 100){
          
            /* Se actualizan valores objeto y telescopio*/
            obj->Sn = maximum(obj->O, last->Cn);
            obj->Cn = obj->Sn + 100;
            tel->T = obj->Cn;
            
            /* Agregamos la cola */
            last->next = obj; 
            tel->back = obj->id;

            return 1;
        }

        /* En caso que no se haya podido insertar retornamos 0 */
        else{
            return 0;
        }
    }
}

/* Función que incerta obj al inicio de la cola del telescopio */
int  enqueue_start(telescopio *tel, objeto *obj, problem_instance *pi){

    /* si la cola está vacía (nunca debería darse este caso)*/
    if(tel->front == -1){

        /*Actualizamos variables para los objetivos y para el telescopio*/
        obj->Sn = obj->O;
        obj->Cn = obj->Sn + 100;
        tel->T = obj->Cn;

        /*Lo agregamos a la cola */
        tel->front = obj->id;
        tel->queue = obj;
        tel->back = obj->id;


        return 1;
    }
    else{

        /* Vemos si podemos poner el objeto al principio de la cola */
        objeto* first = &(pi->objetos[tel->front]);

        if(obj->O  + 100 <= first->Sn){

            /*Actualizamos valores de las variables*/
            obj->Sn = obj->O;
            obj->Cn = obj->Sn + 100;

            /*Agruegamos el nuevo objeto en el inicio de la cola */
            obj->next = tel->queue;
            tel->front = obj->id;
            tel->queue = obj;

            return 1;
        }  

        /* En caso que no se haya podido insertar retornamos 0 */
        else{
            return 0;
        }


    }
}

/* Función para incertar un objeto entre medio de los objetos */
int enqueue_middle(telescopio *tel, objeto *obj, problem_instance *pi){
    /*el caso de cola vacíano debería pasar asi que asumiremos que la cola tiene elementos */
    objeto* actual = tel->queue;

    while(actual){

        /*Vemos si podemos ponerlo enre el actual y el next */
        objeto* next = actual->next;

        /* Condición de término si llegamos al final de la cola */
        if(!next) return 0;

        /*Vemos si está el "hueco" y si se alcanza a observar */
        if(minimum(next->Sn, obj->D) - maximum(obj->O, actual->Cn) >= 100){

            /*Actualizamos valores del objeto */
            obj->Sn = maximum(actual->Cn, obj->O);
            obj->Cn = obj->Sn + 100;

            /* Lo agregamos a la cola*/
            actual->next = obj;
            obj->next = next;

            return 1;

        }else{
            /*Pasamos al siguiente objeto*/
            actual = next;
        }
    }

    /*Si no ha podido ingresar entonces retornamos 0*/
    return 0;
}

/* Función para printear la cola */
void print_queue(telescopio *tel, problem_instance *pi){
    printf("\n\nTelescopio %d: ", tel->id);
    objeto* actual = tel->queue;
    printf("\tStart Cost: %d", actual->start_cost);
    while(actual){

        objeto *next = actual->next;

        printf("\nObjeto: %d ", actual->id);
        printf("\t l: %d \t Sn: %d \t Cn: %d ", actual->l, actual->Sn, actual->Cn);

        if(next){
            printf("\tCost_to_next: %d", pi->giro[actual->id][next->id]);
        }
        actual = actual->next;
    }


}
