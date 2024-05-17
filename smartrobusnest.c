#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void verifmalloc(void* p){
    if (p==NULL){
        //printf("%d", perror(errno));
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