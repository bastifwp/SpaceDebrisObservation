/* This file contains the variable and function declarations */

# ifndef _GLOBAL_H_
# define _GLOBAL_H_

# define INF 1.0e14
# define EPS 1.0e-14
# define E  2.71828182845905
# define PI 3.14159265358979
# define GNUPLOT_COMMAND "gnuplot -persist"

typedef struct
{
    /*USING*/
    int rank; 
    int *rep; /* Representación (permutación de nobj)*/
    double crowd_dist;
    double constr_violation; 
    double *obj /* Valores de las funciones objetivo */

    /* NOT USING */
    /*
    double *xreal;
    int **gene; 
    double *xbin;
    double *obj;
    double *constr;
    */
    
}
individual;

typedef struct
{
    individual *ind;
}
population;

/* Esto se utiliza en rank.c para aplicar los frentes y etc.....*/
typedef struct lists
{
    int index;
    struct lists *parent;
    struct lists *child;
}
list;


typedef struct
{
    int id;
    int l; /* Valor de observación */
    int O; /* Inicio ventana */
    int D; /* Fin ventana */
    int start_cost; /* Costo de empezar a observar */
    int Sn; /* tiempo de inicio de observación */
    int Cn; /* tiempo de fin de observación */

    struct objeto* next; /* Porque será parte de una lista enlazada en cada telescopio */
    
}objeto;




typedef struct
{
    int id;

    /* COLA */
    objeto *queue;
    int front; 
    int back;
    int T; /* Tiempo en el que el último objeto de la cola deja de observarse */
}telescopio;


typedef struct
{
    /* Listas de objetos y de telescopios */
    objeto *objetos;
    telescopio *telescopios;

    int **giro; /* Matriz con los costos de giro */

    /* Variables para definir dimensión del problema */
    int nObj; /* Numero de objetos */
    int nTel; /* Numero de telescopios */

}problem_instance;






extern int nvar;
extern int nobj;
extern int ncon;
extern int popsize;
extern double pcross;
extern double pmut;


/* Creo q esto son parametros de operadores 
extern double eta_c;
extern double eta_m;
*/

extern int ngen;

/*extern int nbinmut;*/

/* Cantidad de mutaciones/cruzamientos */
extern int nmut; /**/
extern int ncross;

/*extern int *nbits;  por que mi representación será una permutacion*/
 /*
extern double *min_realvar;
extern double *max_realvar;
extern double *min_binvar;
extern double *max_binvar;
extern int bitlength;
*/

extern int choice;
extern int obj1;
extern int obj2;

/*
extern int obj3;
extern int angle1;
extern int angle2;
*/


/* Added by me */
void restart_variables(problem_instance *pi);
int enqueue_start(telescopio *tel, objeto *obj, problem_instance *pi);
int enqueue_end(telescopio *tel, objeto *obj, problem_instance *pi);
int enqueue_middle(telescopio *tel, objeto *obj, problem_instance *pi);

void print_queue(telescopio *tel, problem_instance *pi);

/*objeto* top(telescopio *tel);
void dequeue(telescopio *tel);


/* Added by miss elizabeth */
void allocate_memory_pop (population *pop, int size, problem_instance *pi);
void allocate_memory_ind (individual *ind, problem_instance *pi);
void deallocate_memory_pop (population *pop, int size, problem_instance *pi);
void deallocate_memory_ind (individual *ind, problem_instance *pi);

int maximum (int a, int b);
int minimum (int a, int b);

void crossover (individual *parent1, individual *parent2, individual *child1, individual *child2, problem_instance *pi);
void crossover_OX(individual *parent1, individual *parent2, individual *child1, individual *child2, problem_instance *pi);
void realcross (individual *parent1, individual *parent2, individual *child1, individual *child2);
void bincross (individual *parent1, individual *parent2, individual *child1, individual *child2);

void assign_crowding_distance_list (population *pop, list *lst, int front_size);
void assign_crowding_distance_indices (population *pop, int c1, int c2);
void assign_crowding_distance (population *pop, int *dist, int **obj_array, int front_size);

void decode_perm (int *perm, problem_instance *pi);

void onthefly_display (population *pop, FILE *gp, int ii);

int check_dominance (individual *a, individual *b);

void evaluate_pop (population *pop, problem_instance *pi);
void evaluate_ind (individual *ind, problem_instance *pi);

void fill_nondominated_sort (population *mixed_pop, population *new_pop, problem_instance *pi);
void crowding_fill (population *mixed_pop, population *new_pop, int count, int front_size, list *cur, problem_instance *pi);

void initialize_pop (population *pop, problem_instance *pi);
void initialize_ind (individual *ind, problem_instance *pi);

void insert (list *node, int x);
list* del (list *node);

void merge(population *pop1, population *pop2, population *pop3, problem_instance *pi);
void copy_ind (individual *ind1, individual *ind2, problem_instance *pi);

void mutation_pop (population *pop, problem_instance *pi);
void random_swap(individual *ind, problem_instance *pi);
void mutation_ind (individual *ind, problem_instance *pi);
void bin_mutate_ind (individual *ind);
void real_mutate_ind (individual *ind);

void test_problem (double *xreal, double *xbin, int **gene, double *obj, double *constr);

void assign_rank_and_crowding_distance (population *new_pop);

void report_pop (population *pop, FILE *fpt, problem_instance *pi);
void report_feasible (population *pop, FILE *fpt, problem_instance *pi);
void report_ind (individual *ind, FILE *fpt, problem_instance *pi);

void quicksort_front_obj(population *pop, int objcount, int obj_array[], int obj_array_size);
void q_sort_front_obj(population *pop, int objcount, int obj_array[], int left, int right);
void quicksort_dist(population *pop, int *dist, int front_size);
void q_sort_dist(population *pop, int *dist, int left, int right);

void selection (population *old_pop, population *new_pop, problem_instance *pi);
individual* tournament (individual *ind1, individual *ind2);

# endif
