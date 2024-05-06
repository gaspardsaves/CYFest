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

int main (){
    int* p = NULL;
    verifmalloc(p);
    return 0;
}