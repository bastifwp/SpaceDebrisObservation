/* Rank assignment routine */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "global.h"
# include "rand.h"

/* Function to assign rank and crowding distance to a population of size pop_size*/
void assign_rank_and_crowding_distance (population *new_pop)
{
    int flag;
    int i;
    int end;
    int front_size;
    int rank=1;
    list *orig;
    list *cur;

    list *temp1, *temp2; /*Variables auxiliares para recorrer listas*/
    
    front_size = 0;

    /* Lista con los indices de los individuos no asignados */
    orig = (list *)malloc(sizeof(list)); 
    orig->index = -1;
    orig->parent = NULL;
    orig->child = NULL;

    /* Lista enlazada con el frente actual */
    cur = (list *)malloc(sizeof(list));
    cur->index = -1;
    cur->parent = NULL;
    cur->child = NULL;


    /*Ahora temp1 tiene el puntero a orig*/
    temp1 = orig;

    /* Asignamos todos los individuos a la lista orig */
    for (i=0; i<popsize; i++)
    {
        insert (temp1,i);
        temp1 = temp1->child;
    }


    /*Hay q notar q  orig y cur tienen nodo dummy de cabecera */

    /*Loop de ordenamiento por frentes */
    do
    {   
        /*Si solo queda un individuo en la lista entonces lo asignamos al siguiente rank */
        /* Esto se hace poruqe no hay con quien más compararlo*/
        if (orig->child->child == NULL)
        {
            new_pop->ind[orig->child->index].rank = rank;
            new_pop->ind[orig->child->index].crowd_dist = INF;
            break;
        }

        /*Procesamos el individuo */
        temp1 = orig->child;
        insert (cur, temp1->index); /* Asumimos que lo podemos poner en la lista de pareto actual */
        front_size = 1;

        
        temp2 = cur->child; /*Para recorrrer el frente acutal */
        
        /*Se pasa al siguiente nodo*/
        temp1 = del (temp1);  /*Elimina el primero*/
        temp1 = temp1->child; /*Se avanza, porque el primero es dummy */
        
        /* Recorremos los individuos restantes temp1 de orig */
        do
        {
            temp2 = cur->child;

            /* Comparamos temp1 con cada individuo del frente actual*/
            do
            {
                end = 0;
                flag = check_dominance (&(new_pop->ind[temp1->index]), &(new_pop->ind[temp2->index]));
                
                /*temp1 domina a algun elemento que ya estaba en el frente */
                if (flag == 1)
                {
                    /* Temp2 se saca de la cola actual y se vuele a la cola de espera */
                    insert (orig, temp2->index); /*Se incerta de tal forma que el ciclo exterior no lo va a pescar pq está antes*/
                    temp2 = del (temp2);
                    front_size--;
                    temp2 = temp2->child;
                }

                /* Si son no dominadas */
                if (flag == 0)
                {
                    /* temp1 y temp2 no se dominan, temp1 todavia puede seguir */
                    temp2 = temp2->child;
                }

                /*Si un elemento que estaba en el frente domina a temp1 entonces temp1 no puede pertenecer al frente */
                if (flag == -1)
                {
                    end = 1; /*Salimos del ciclo */
                }
            }
            while (end!=1 && temp2!=NULL);
            /* Solo la agregamos si era no dominada o si dominaba a otra */
            if (flag == 0 || flag == 1)
            {
                insert (cur, temp1->index);
                front_size++;
                temp1 = del (temp1);
            }
            temp1 = temp1->child; /* Pasamos al siguiente pendiente */
        }
        while (temp1 != NULL);

        /*Hasta aquí en cur ya tenemos un frente completo*/

        /*Asignamos el rank a todos los individuos */
        temp2 = cur->child;
        do
        {
            new_pop->ind[temp2->index].rank = rank;
            temp2 = temp2->child;
        }
        while (temp2 != NULL);

        /*Asignamos el crowding distance*/
        assign_crowding_distance_list (new_pop, cur->child, front_size);
        
        /*Limpiamos la lista del frente actual para crear el siguiente*/
        temp2 = cur->child;
        do
        {
            temp2 = del (temp2);
            temp2 = temp2->child;
        }
        while (cur->child !=NULL);
        rank+=1;
        
    }


    while (orig->child!=NULL);
    free (orig);
    free (cur);
    return;
}
