# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include "global.h"


void readPermFile(char* filePath, int* perm, int n_objetos){
    FILE* f = fopen(filePath, "r");
    printf("\nstart reading permutation");
    
    if(f == NULL){
        printf("\nFile dont exit");
        exit(1);
    }

    char *token;
    char line[3000];
    fgets(line, sizeof(line), f);

    /*Ahora recorremos cada cosa*/
    int index = 0;
    token = strtok(line, " ");
    
    while(token != NULL){

        if(index >= n_objetos){
            printf("Permutation have more numbers than observarble objetcts.\nExiting...\n");
            exit(1);
        }

        perm[index] = atoi(token);
        token = strtok(NULL, " ");
        index++;
    }

    if(index != n_objetos){
        printf("Not enough objects in permutation.\nExiting...\n");
        exit(1);
    }

    fclose(f);
}
