#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<errno.h>
#include "structures.h"
#include "backupfile.h"

//Free memory allocation
void freeArray(int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert){
    for (int i = 0; i < *userCount; i++) {
        free(tabFest[i].password);
        //free(tabFest[i].id);
    }
    free(tabFest);
    //*/
    for (int j = 0; j < *roomCount; j++) {
        free(tabRoom[j].siege);
        //free(tabRoom[j].nb_range);
        //free(tabRoom[j].nb_siege_range);
        free(tabRoom[j].nom);
        //free(tabRoom[j].arange);
        //free(tabRoom[j].brange);
    }
    free(tabRoom);
    for (int k = 0; k < *concertCount; k++) {
        free(tabConcert[k].guest);
    }
    free(tabConcert);
}

/*
void Userfile(Utilisateur* tab, int* userCount){

FILE* f=NULL;
    f=fopen("UserTable", "w");
    if(f==NULL){
fprintf(stderr, "On ne peut pas écrire sur le fichier\n");
fprintf(stderr, "Code erreur : %d\n", errno);
fprintf(stderr, "Erreur : %s\n", strerror(errno));
 return;
}

fprintf(f, "%d\n", *userCount);

for (int i=0; i<*userCount; i++){
        fprintf(f, "%d" "%s",tab[i].id , tab[i].password);
}
fclose(f);       
}

Utilisateur* readfile(int* userCount){
    FILE* f=NULL;
    f=fopen("UserTable", "r");
if (f==NULL){
fprintf(stderr, "On ne peut pas écrire sur le fichier\n");
fprintf(stderr, "Code erreur : %d\n", errno);
fprintf(stderr, "Erreur : %s\n", strerror(errno));
     exit(1);
}
fscanf(f, "%d\n", userCount);
Utilisateur* tab=user_table(userCount);

for (int i=0; i<*userCount; i++){
tab[i].id=malloc(sizeof(int));
tab[i].password=malloc(50);


fscanf(f,"%d", tab[i].id);
fgets(tab[i].password, 50, f);
tab[i].password[strcspn(tab[i].password, "\n")] = '\0';
}
fclose(f);
return tab;
}

Utilisateur* Realloc_table(int* userCount){
FILE* f=NULL;
f=fopen("UserTable", "r" );
if(f==NULL){

fprintf(stderr, "On ne peut pas écrire sur le fichier\n");
fprintf(stderr, "Code erreur : %d\n", errno);
fprintf(stderr, "Erreur : %s\n", strerror(errno));
}

Utilisateur* tab=malloc(sizeof(Utilisateur)*(*userCount));
if(tab==NULL){
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
}

    fscanf(f, "%d\n", userCount);

    for(int i=0; i<*userCount; i++){

        tab[i].id=malloc(sizeof(int));
if(tab[i].id==NULL){
fprintf(stderr, "Erreur d'allocation mémoire pour l'id\n");
fprintf(stderr, "Code erreur : %d\n", errno);
fprintf(stderr, "Erreur : %s\n", strerror(errno));
exit(EXIT_FAILURE);
}
fscanf(f,"%d\n", tab[i].id);// get the id in the new tab from UserTable

tab[i].password=malloc(50);
if(tab[i].password==NULL){
fprintf(stderr, "Erreur d'allocation mémoire pour l'id\n");
fprintf(stderr, "Code erreur : %d\n", errno);
fprintf(stderr, "Erreur : %s\n", strerror(errno));
exit(EXIT_FAILURE);
}
fgets(tab[i].password, 50, f); // get the password in the new tab from UserTable
tab[i].password[strcspn(tab[i].password, "\n")] = '\0';  // Remove newline character
}

fclose(f);
return tab;
    
}
//*/