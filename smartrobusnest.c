#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void verifmalloc(void* p){
    if (p==NULL){
        printf("%d\n", errno);
        exit(EXIT_FAILURE);
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