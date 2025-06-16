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



/* Added by me */
void restart_variables(problem_instance *pi);
int enqueue_start(telescopio *tel, objeto *obj, problem_instance *pi);
int enqueue_end(telescopio *tel, objeto *obj, problem_instance *pi);
int enqueue_middle(telescopio *tel, objeto *obj, problem_instance *pi);
void print_queue(telescopio *tel, problem_instance *pi);
void decode_perm (int *perm, problem_instance *pi);
void evaluate_ind (int* perm, problem_instance *pi);

/* Added variables to read */
void findDef(FILE *f, char *def);
int countWords(char *line);
void readPermFile(char* filePath, int* perm, int n_objetos);

/* Added auxiliar functions */
int maximum (int a, int b);
int minimum (int a, int b);

# endif
