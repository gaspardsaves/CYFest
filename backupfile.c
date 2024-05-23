#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "backupfile.h"

//Free memory allocation
void freeTab(int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert){
    for (int i = 0; i < *userCount; i++) {
        free(tabFest[i].password);
        free(tabFest[i].id);
    }
    free(tabFest);
    //*/
    for (int j = 0; j < *roomCount; j++) {
        free(tabRoom[j].siege);
        free(tabRoom[j].nb_range);
        free(tabRoom[j].nb_siege_range);
        free(tabRoom[j].nom);
        free(tabRoom[j].arange);
        free(tabRoom[j].brange);
    }
    free(tabRoom);
    for (int k = 0; k < *concertCount; k++) {
        free(tabConcert[k].guest);
    }
    free(tabConcert);
}