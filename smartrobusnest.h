#ifndef VERIF_MALLOC
    #define VERIF_MALLOC
    #include <stddef.h>
    void verifmalloc(void* p);
    int better_scan(char * message);
    float better_scanFloat(char * message);
    unsigned better_scanUn(char * message);
#endif