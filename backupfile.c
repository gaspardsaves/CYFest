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
Salle SavePointeurSiege(Salle S){
    S.SaveSiege = malloc(S.nb_range*S.nb_siege_range*sizeof(Salle));
    verifpointer(S.SaveSiege);
    int n = S.nb_range*S.nb_range;
    int i = 0;
    int j = 0;
    int k = 0;
    while(i<n){
        S.SaveSiege[i] = S.siege[k][j]; 
        i++;
        k++;
        j++;
        if(k==S.nb_range){
            k=0;
        }
        if(j==S.nb_siege_range){
            j=0;
        }
    }
    return S;
}

void SauvegardeSalleFichier(Salle* s){
    FILE* f1 = fopen("SaveScene.bin", "wb");
    *s = SavePointeurSiege(*s);
    fwrite(s, sizeof(Salle), 1, f1);
    int i = 0;
    int n = s->nb_siege_range*s->nb_range;
    while(i<n){
        fwrite(&s->SaveSiege[i], sizeof(Siege), 1, f1);
        i++;
    }
    
    fclose(f1);
}

void LireSallefichier(Salle* s2){
    if(s2==NULL){
        printf("Erreur");
        exit(EXIT_FAILURE);
    }
    FILE* f1 = fopen("SaveScene.bin", "rb");
    fread(s2, sizeof(Salle),1,f1);
    int i = 0;
    int n = s2->nb_siege_range*s2->nb_range;
    while(i<n){
        fread(&s2->SaveSiege[i], sizeof(Siege), 1, f1);
        i++;
    }
    *s2 = ReadPointeurSiege(*s2);
    fclose(f1);
}
//*/

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