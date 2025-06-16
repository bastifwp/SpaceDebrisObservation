# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include "global.h"


/*Función que avanza el puntero del archivo hasta el string def */
void findDef(FILE *f, char *def) {

    char word[3000];
    /* assumes no word exceeds length of 1023 */
    while (fscanf(f, " %1023s", word)) {
        if(strcmp(word,def) == 0) break;
    }
}

void removeSemicolon(char *line){
    strtok(line, ";");
}

/* Básticamente cuenta cuantos espacios hay */
int countWords(char *line){
    int words;
    char linet[3000], *token;
    strcpy(linet, line);

    words = 0;
    token = strtok(linet, " "); /* Obtenemos la primera palabra */

    while( token != NULL ) {
        words ++;
        token = strtok(NULL, " "); /* Avanzamos a la siguiente palabra */
    }
   return words;
}

/* FUNCIONES PARA LEER CONJUNTOS: */
void readObjetos(FILE *f, problem_instance *pi){
    char *token, id=0;
    char line[3000];
    fgets(line, sizeof(line), f);
    removeSemicolon(line);

    pi->nObj = countWords(line);
    pi->objetos = malloc(pi->nObj*sizeof(objeto));

    /*Ahora asignamos los ids a cada objeto*/
    token=strtok(line, " ");
    while( token != NULL ) {
        pi->objetos[id].id=id;
        pi->objetos[id].next = malloc(sizeof(objeto));
        token=strtok(NULL, " ");
        id++;
    }
}


void readTelescopios(FILE *f, problem_instance *pi){
    char *token, id=0;
    char line[3000];
    fgets(line, sizeof(line), f);
    removeSemicolon(line);

    pi->nTel = countWords(line);
    pi->telescopios = malloc(pi->nTel*sizeof(telescopio));

    /* Asignamos los ids a cada telescopio */
    token=strtok(line, " ");
    while( token != NULL ) {
        pi->telescopios[id].id=id;
        pi->telescopios[id].queue = malloc(sizeof(objeto));
        token=strtok(NULL, " ");
        id++;
    }
}

/* FUNCIONES PARA LEER PARAMETROS */
void readObjetosParams(FILE *f, problem_instance *pi){

    char line[3000];
    char *token;

    /* Nos saltamos la primera linea */
    fgets(line, sizeof(line), f);
   
    
    int i = 0;
    while (1){
    
        /*Nos saltamos la primera word, si es ; entonces break*/
        fgets(line, sizeof(line), f);
        token = strtok(line, " ");
        if (strchr(token, ';') != NULL) break;
    
        /* Recorremos todos los parametros de la linea */
        token =strtok(NULL, " "); /* Para leer el primer parametro */
        
        int param = 0;
        while(token != NULL){
            if(param == 0){
                pi->objetos[i].l = atoi(token);
            }
            else if(param == 1){
                pi->objetos[i].O = atoi(token);
            }
            else if(param == 2){
                pi->objetos[i].D = atoi(token);
            }
            else if(param == 3){
                pi->objetos[i].start_cost = atoi(token);
            }

            param++;

            token=strtok(NULL, " ");
        }

        i++;
    }

    fgets(line, sizeof(line), f);

}

/* Función para leer el parámetro de giro */
void readGiro(FILE *f, problem_instance *pi){
    char line[3000];
    char *token;

    /* Pedimos memoria para el parámetro giro */
    pi->giro = (int **)malloc(pi->nObj * sizeof(int*));
    int i;
    for(i=0; i < pi->nObj; i++){
        pi->giro[i] = (int *)malloc(pi->nObj * sizeof(int));
    }

    /* Nos saltamos la primera linea */
    fgets(line, sizeof(line), f);    

    int j=0;
    i=0;
    while(1){

        /*Nos saltamos la primera word, si es ; entonces break*/
        fgets(line, sizeof(line), f);

        token = strtok(line, " ");
        if (strchr(token, ';') != NULL) break;

        /* Ahora asignamos el costo de giro */
        token = strtok(NULL, " "); /* Avanzamos para enrtar al ciclo*/
        j=0;
        while(token != NULL){
            pi->giro[i][j] = atoi(token);
            token=strtok(NULL, " ");
            j++;
        }
        
        i++;
    }
}


int readInputFile(char* filePath, problem_instance *pi) {
    int debug=0;
    FILE* fh=fopen(filePath, "r");

    /*check if file exists*/
    if( fh==NULL ){
        printf("File does not exists %s", filePath);
        return 0;
    }

    /* Lectura de conjuntos */
    findDef(fh, "N:=");
    readObjetos(fh, pi);
    printf("\nfinished objetos!");

    findDef(fh, "M:=");
    readTelescopios(fh, pi);
    printf("\nfinished telescopios!");

    /* Lectura de parámetros */    
    /*(no reconoce "l O D start_cost:=")*/ 
    findDef(fh, "start_cost:=");
    readObjetosParams(fh, pi);
    printf("\nfinished params!");

    char find[3000];
    sprintf(find, "o%d:=", pi->nObj); /*tenemos que buscar o8, donde 8 es el ultimo objeto */
    findDef(fh, find);
    readGiro(fh, pi);
    printf("\nfinished giro");

    /* Finished reading */
    fclose(fh);

    printf("\nFinished instance description, press any key to continue \n");   
    getchar();

    return 0;
}


