/* NSGA-II routine (implementation of the 'main' function) */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <time.h>

# include "global.h"
# include "rand.h"


int nvar;
/*
int nbin;
*/
int nobj; /* Cantidad de funciones obj*/

/*
int ncon;
*/

int popsize;
double pcross;
double pmut;

/*
double eta_c;
double eta_m;
*/

int ngen;

/*int nbinmut;*/

/* Cantidad de veces que usan los operadores */
int nmut;
int ncross; 


int choice;
int obj1;
int obj2;

/*
int obj3;
int angle1;
int angle2;
*/


int main (int argc, char **argv)
{
    int i;
    FILE *fpt1;
    FILE *fpt2;
    FILE *fpt3;
    FILE *fpt4;
    FILE *fpt5;

    problem_instance *pi = malloc (sizeof(problem_instance)) ;
    population *parent_pop;
    population *child_pop;
    population *mixed_pop;
    if (argc< 7)
    {
        /*printf("\n Usage ./nsga2r instance_route random_seed popsize ngen nobj pcross_bin pmut_bin\n./nsga2r 0.123 b-Instancia14_cap2_relacion7UnoUnoUnoTodosDistintos.dat 100 100 2 0.6 0.01\n");*/
        /* printf("\n For debug queues: ./nsga2r 0.123 test_data.dat 100 100 2 \n"); */
        printf("\n Usage ./nsga2r seed instance popsize ngen pcross pmut \n Example:");
        printf("\n ./nsga2r 0.123 test_data.dat 100 100 0.5 0.5 \n");
        exit(1);
    }

    seed = (double)atof(argv[1]);
    if (seed<=0.0 || seed>=1.0){
        printf("\n Entered seed value is wrong, seed value must be in (0,1) \n");
        exit(1);
    }

    fpt1 = fopen("initial_pop.out","w");
    fpt2 = fopen("final_pop.out","w");
    fpt3 = fopen("best_pop.out","w");
    fpt4 = fopen("all_pop.out","w");
    fpt5 = fopen("params.out","w");
    fprintf(fpt1,"# This file contains the data of initial population\n");
    fprintf(fpt2,"# This file contains the data of final population\n");
    fprintf(fpt3,"# This file contains the data of final feasible population (if found)\n");
    fprintf(fpt4,"# This file contains the data of all generations\n");
    fprintf(fpt5,"# This file contains information about inputs as read by the program\n");

    popsize = atoi(argv[3]);
    if (popsize<4 || (popsize%4)!= 0){
        printf("\n population size read is : %d", popsize);
        printf("\n Wrong population size entered, hence exiting \n");
        exit (1);
    }
    ngen = atoi(argv[4]);
    if (ngen<1){
        printf("\n number of generations read is : %d",ngen);
        printf("\n Wrong nuber of generations entered, hence exiting \n");
        exit (1);
    }

    nobj=2;  /*Siempre trabajaremos con dos funciones objetivo en este códgio */

    pcross = atof (argv[5]);
    if (pcross<0.0 || pcross>1.0){
        printf("\n Probability of crossover entered is : %e",pcross);
        printf("\n Entered value of probability of crossover of binary variables is out of bounds, hence exiting \n");
        exit (1);
    }
    pmut = atof (argv[6]);
    if (pmut<0.0 || pmut>1.0){
        printf("\n Probability of mutation entered is : %e",pmut);
        printf("\n Entered value of probability  of mutation of binary variables is out of bounds, hence exiting \n");
        exit (1);
    }
    

    /*printf("\n Input data successfully entered, now performing initialization \n");*/
    fprintf(fpt5,"\n Population size = %d",popsize);
    fprintf(fpt5,"\n Number of generations = %d",ngen);
    fprintf(fpt5,"\n Number of objective functions = %d",nobj);
    fprintf(fpt5, "\n Probability of crossover = %e", pcross);
    fprintf(fpt5, "\n Probability of mutation = %e", pmut);    
    fprintf(fpt5,"\n Seed for random number generator = %e",seed);


    /*Mediremos el tiempo de ejecución */
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    char * instance_route = argv[2];
    readInputFile(instance_route, pi);

    nmut = 0; 
    ncross = 0;
    nvar = pi->nObj;
   
   /* printf("We will alloc memory for population \n"); */

    parent_pop = (population *)malloc(sizeof(population));
    child_pop = (population *)malloc(sizeof(population));
    mixed_pop = (population *)malloc(sizeof(population));
    allocate_memory_pop (parent_pop, popsize, pi);
    allocate_memory_pop (child_pop, popsize, pi);
    allocate_memory_pop (mixed_pop, 2*popsize, pi);


    randomize();
    restart_variables(pi); /* Tenemos que reiniciar las variables para luego comenzar a evaluar cada individuo por separado */
    initialize_pop(parent_pop, pi);
    evaluate_pop (parent_pop, pi); /* Here each permutation individual is decoded as well */
    assign_rank_and_crowding_distance(parent_pop); 
    report_pop (parent_pop, fpt1, pi);
    fprintf(fpt4,"# gen = 1\n");
    report_pop(parent_pop,fpt4, pi);
    fflush(stdout);
    fflush(fpt1);
    fflush(fpt2);
    fflush(fpt3);
    fflush(fpt4);
    fflush(fpt5);
    sleep(1);
    for (i=2; i<=ngen; i++)
    {

        selection (parent_pop, child_pop, pi); 
        mutation_pop (child_pop, pi);
        evaluate_pop(child_pop, pi); /* Here each individual is decoded */
        merge (parent_pop, child_pop, mixed_pop, pi); /*Metemos ambas poblaciones en mixed_pop*/
        fill_nondominated_sort(mixed_pop, parent_pop, pi); /*Elegimos los que sigan*/ 


        /* Comment following four lines if information for all
        generations is not desired, it will speed up the execution */
        /*
        fprintf(fpt4,"# gen = %d\n",i);
        report_pop(parent_pop,fpt4, pi);
        fflush(fpt4);
        printf("\n gen = %d\n",i);
        */
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\n Generations finished cpu time: \n%f", cpu_time_used);
    report_pop(parent_pop,fpt2, pi);
    report_feasible(parent_pop,fpt3, pi);
    

    fflush(stdout);
    fflush(fpt1);
    fflush(fpt2);
    fflush(fpt3);
    fflush(fpt4);
    fflush(fpt5);
    fclose(fpt1);
    fclose(fpt2);
    fclose(fpt3);
    fclose(fpt4);
    fclose(fpt5);

    deallocate_memory_pop (parent_pop, popsize, pi);
    deallocate_memory_pop (child_pop, popsize, pi);
    deallocate_memory_pop (mixed_pop, 2*popsize, pi);
    free (parent_pop);
    free (child_pop);
    free (mixed_pop);

    return (0);
}
