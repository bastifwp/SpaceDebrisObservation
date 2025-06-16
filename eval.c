/* Routine for evaluating population members  */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "global.h"
# include "rand.h"


/* Routine to evaluate objective function values and constraints for a population */
void evaluate_pop (population *pop, problem_instance * pi)
{
    int i;
    for (i=0; i<popsize; i++)
    {
        /* Aquí posiblemente se deba llamar a restart variables */
        /*printf("\nLlamando a evaluate_ind: ");*/
        evaluate_ind (&(pop->ind[i]), pi);
        /*printf("\nFinished evaluate_ind");*/
    }
    return;
}



/* Routine to evaluate objective function values and constraints for an individual */
void evaluate_ind (individual *ind, problem_instance *pi){

    /*printf("\nLets restart the variables");*/

    /* Borramos lo que haya estado en la cola */
    restart_variables(pi);

    /*Insertamos los objetos de la permutación en las colas */
    decode_perm(ind->rep, pi);


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
    ind->obj[0] = -total_value; /* Porque estamos minimizando */
    ind->obj[1] = total_cost; 

    return;
}


/* --------------- PERMUTATION PHASE -----------------*/

/*Ocuparemos esto por mientras para valorar las secuencias ordenadas*/

int ordered_eval(individual *ind, problem_instance *pi) {
    int n = pi->nObj;
    int count = 0;
    int i ;

    for (i = 0; i < n; i++) {
        if (ind->rep[i] != i) {
            count++;  
        }
    }

    return count;  
}


/*Funciónn que evalúa las inversiones */
int inversions_eval(individual *ind, problem_instance *pi){
    int inv = 0;
    int i, j;
    for(i = 0; i < pi->nObj-1; i++){
        for(j = i+1; j < pi->nObj; j++){
            if(ind->rep[i] > ind->rep[j]) inv++;
        }
    }
    return inv;
}

/* ----------------- END OF PERMUTATION PHASE -------------*/



/* Routine to evaluate objective function values and constraints for an individual 
void evaluate_ind (individual *ind)
{    
    void test_problem (double *xreal, double *xbin, int **gene, double *obj, double *constr)
    {
    obj[0] = pow(xreal[0],2.0);
    obj[1] = pow((xreal[0]-2.0),2.0);
    return;
    }
    

    test_problem (ind->xreal, ind->xbin, ind->gene, ind->obj, ind->constr);
    
    int j;
    if (ncon==0)
    {
        ind->constr_violation = 0.0;
    }
    else
    {
        ind->constr_violation = 0.0;
        for (j=0; j<ncon; j++)
        {
            if (ind->constr[j]<0.0)
            {
                ind->constr_violation += ind->constr[j];
            }
        }
    }
    return;
}
*/