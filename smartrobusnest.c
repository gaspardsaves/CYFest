#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void verifpointer(void* p){
    if (p==NULL){
        printf("%d\n", errno);
        fprintf(stderr, "Pointeur nul\n");
        exit(1);
    }
}

void checkOpenFile(FILE* f){
    if (f==NULL){
        printf("%d\n", errno);
        fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
        exit(2);
    }
}

void checkWritingFile(int writeReturn){
    if (writeReturn==EOF){
        printf("%d\n", errno);
        fprintf(stderr, "Erreur lors de l'écriture d'une ligne\n");
        exit(2);
    }
}

void checkCloseFile(int closeReturn){
    if (closeReturn==EOF){
        printf("%d\n", errno);
        fprintf(stderr, "Erreur lors de la fermeture d'un flux\n");
        exit(3);
    }
}

int better_scan(char * message){
    int ret_var = 0;
    int value = 1;
  while (ret_var != 1 || value < 0)
    {   
        printf("%s", message);
        ret_var = scanf("%d", &value);
        while(getchar()!='\n'){} // Ligne facultative de sécurisation
    }
    return value;
}

float better_scanFloat(char * message){
    int ret_var = 0;
    float value = 1;
  while (ret_var != 1 || value < 0)
    {   
        printf("%s", message);
        ret_var = scanf("%f", &value);
        while(getchar()!='\n'){} // Ligne facultative de sécurisation
    }
    return value;
}

unsigned better_scanUn(char * message){
    int ret_var = 0;
    unsigned value = 1;
  while (ret_var != 1 || value < 0)
    {   
        printf("%s", message);
        ret_var = scanf("%d", &value);
        while(getchar()!='\n'){} // Ligne facultative de sécurisation
    }
    return value;
}