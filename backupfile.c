#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "structures.h"
#include "backupfile.h"
#include "color.h"
#include "structures.h"
#include "manager.h"
#include "smartrobusnest.h"


//Free memory allocation before killing the application
void arrayFree(int* UtilisateurCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert){
    for (int i = 0; i < *UtilisateurCount; i++) {
        free(tabFest[i].password);
    }
    free(tabFest);
    for (int j = 0; j < *roomCount; j++) {
        free(tabRoom[j].siege);
        free(tabRoom[j].nom);
    }
    free(tabRoom);
    for (int k = 0; k < *concertCount; k++) {
        free(tabConcert[k].guest);
    }
    free(tabConcert);
}

//NOUVEAU CODE SAUVEGARDE BINAIRE
/*
void SaveSaveSit(Salle* s) {
    FILE* f = fopen("SaveSit.bin", "wb");
    if (f == NULL) {
        perror("Erreur dans l'écriture du fichier SaveSit");
        exit(1);
    }

    int tot_seat = s->nb_range * s->nb_siege_range;
    fwrite(s->Save_sit, sizeof(Siege), tot_seat, f);
    fclose(f);
}

void ReadSaveSit(Salle* s) {
    FILE* f = fopen("SaveSit.bin", "rb");
    if (f == NULL) {
        perror("Erreur dans la lecture du fichier SaveSit");
        exit(1);
    }

    int tot_seat = s->nb_range * s->nb_siege_range;
    s->Save_sit = malloc(tot_seat * sizeof(Siege));
    if (s->Save_sit == NULL) {
        perror("Erreur à l'allocation de la mémoire pour Save_sit");
        exit(1);
    }

    fread(s->Save_sit, sizeof(Siege), tot_seat, f);
    fclose(f);
}

void SaveScene(Salle* s) {
    FILE* f1 = fopen("Scene.bin", "wb");
    if (f1 == NULL) {
        perror("Erreur dans l'écriture du fichier");
        exit(1);
    }
    printf("Bonne sauvegarde de la scene %s\n", s->nom);

   
    fwrite(&s->nb_range, sizeof(int), 1, f1);
    fwrite(&s->nb_siege_range, sizeof(int), 1, f1);
    fwrite(s->nom, sizeof(char), 100, f1); 
    fwrite(&s->arange, sizeof(int), 1, f1);
    fwrite(&s->brange, sizeof(int), 1, f1);
    fwrite(&s->prixa, sizeof(float), 1, f1);
    fwrite(&s->prixb, sizeof(float), 1, f1);
    fwrite(&s->prixc, sizeof(float), 1, f1);
    fwrite(&s->state, sizeof(int), 1, f1);

  
    for (int i = 0; i < s->nb_range; i++) {
        fwrite(s->siege[i], sizeof(Siege), s->nb_siege_range, f1);
    }
    fclose(f1);

    // Sauvegarder Save_sit
    SaveSaveSit(s);
}

void ReadScene(Salle* s) {
    FILE* f1 = fopen("Scene.bin", "rb");
    if (f1 == NULL) {
        perror("Erreur dans la lecture du fichier");
        exit(1);
    }

 
    fread(&s->nb_range, sizeof(int), 1, f1);
    fread(&s->nb_siege_range, sizeof(int), 1, f1);
    fread(s->nom, sizeof(char), 100, f1); 
    fread(&s->arange, sizeof(int), 1, f1);
    fread(&s->brange, sizeof(int), 1, f1);
    fread(&s->prixa, sizeof(float), 1, f1);
    fread(&s->prixb, sizeof(float), 1, f1);
    fread(&s->prixc, sizeof(float), 1, f1);
    fread(&s->state, sizeof(int), 1, f1);

    
    s->siege = malloc(s->nb_range * sizeof(Siege*));
    for (int i = 0; i < s->nb_range; i++) {
        s->siege[i] = malloc(s->nb_siege_range * sizeof(Siege));
        fread(s->siege[i], sizeof(Siege), s->nb_siege_range, f1);
    }
    fclose(f1);

    
    ReadSaveSit(s);
    printf("ReadScene BIEN effectue\n");
}

Salle SavePointeurSiege(Salle S) {
    int tot_seat = S.nb_range * S.nb_siege_range;
    S.Save_sit = malloc(tot_seat * sizeof(Siege));
    if (S.Save_sit == NULL) {
        perror("Erreur à l'allocation de la mémoire pour Save_sit");
        exit(EXIT_FAILURE);
    }

    int k = 0;
    for (int i = 0; i < S.nb_range; i++) {
        for (int j = 0; j < S.nb_siege_range; j++) {
            S.Save_sit[k++] = S.siege[i][j];
        }
    }

    return S;
}

Salle ReadPointeurSiege(Salle S) {
    S.siege = malloc(S.nb_range * sizeof(Siege*));
    if (S.siege == NULL) {
        perror("Erreur allocation mémoire du nombre de rangées");
        exit(1);
    }

    for (int i = 0; i < S.nb_range; i++) {
        S.siege[i] = malloc(S.nb_siege_range * sizeof(Siege));
        if (S.siege[i] == NULL) {
            perror("Erreur allocation dynamique du nombre de sièges par rangée");
            exit(1);
        }
    }

    int k = 0;
    for (int i = 0; i < S.nb_range; i++) {
        for (int j = 0; j < S.nb_siege_range; j++) {
            S.siege[i][j] = S.Save_sit[k++];
        }
    }

    printf("ReadPointeurSiege Bien effectué \n");
    printf(" \n");
    printf(" \n");
    
    return S;
}

int main(){


    Salle s = constructSalle();
    printf("\n");
    strcpy(s.nom, "Jezus");
    s.siege[0][0].etat_siege = 1; 
    affichesalle(s);
    s = SavePointeurSiege(s);
    SaveScene(&s);

    printf("\n");

    Salle s2;
    ReadScene(&s2);
    ReadPointeurSiege(s2);
    s2 = ReadPointeurSiege(s2);
    affichesalle(s2);


  return 0;
}
//*/

//SAUVEGARDE UTILISATEUR
/*
void Utilisateurfile(Utilisateur* tab, int* UtilisateurCount){

FILE* f=NULL;
    f=fopen("UtilisateurTable", "w");
    if(f==NULL){
fprintf(stderr, "On ne peut pas écrire sur le fichier\n");
fprintf(stderr, "Code erreur : %d\n", errno);
fprintf(stderr, "Erreur : %s\n", strerror(errno));
 return;
}

fprintf(f, "%d\n", *UtilisateurCount);

for (int i=0; i<*UtilisateurCount; i++){
        fprintf(f, "%d" "%s",*tab[i].id , tab[i].password);
}
fclose(f);       
}

Utilisateur* readfile(int* UtilisateurCount){
    FILE* f=NULL;
    f=fopen("UtilisateurTable", "r");
if (f==NULL){
fprintf(stderr, "On ne peut pas écrire sur le fichier\n");
fprintf(stderr, "Code erreur : %d\n", errno);
fprintf(stderr, "Erreur : %s\n", strerror(errno));
     exit(1);
}
fscanf(f, "%d\n", UtilisateurCount);
Utilisateur* tab=Utilisateur_table(UtilisateurCount);

for (int i=0; i<*UtilisateurCount; i++){
tab[i].id=malloc(sizeof(int));
tab[i].password=malloc(50);


fscanf(f,"%d", tab[i].id);
fgets(tab[i].password, 50, f);
tab[i].password[strcspn(tab[i].password, "\n")] = '\0';
}
fclose(f);
return tab;
}

Utilisateur* Realloc_table(int* UtilisateurCount){
FILE* f=NULL;
f=fopen("UtilisateurTable", "r" );
if(f==NULL){

fprintf(stderr, "On ne peut pas écrire sur le fichier\n");
fprintf(stderr, "Code erreur : %d\n", errno);
fprintf(stderr, "Erreur : %s\n", strerror(errno));
}

Utilisateur* tab=malloc(sizeof(Utilisateur)*(*UtilisateurCount));
if(tab==NULL){
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
}

    fscanf(f, "%d\n", UtilisateurCount);

    for(int i=0; i<*UtilisateurCount; i++){

        tab[i].id=malloc(sizeof(int));
if(tab[i].id==NULL){
fprintf(stderr, "Erreur d'allocation mémoire pour l'id\n");
fprintf(stderr, "Code erreur : %d\n", errno);
fprintf(stderr, "Erreur : %s\n", strerror(errno));
exit(EXIT_FAILURE);
}
fscanf(f,"%d\n", tab[i].id);// get the id in the new tab from UtilisateurTable

tab[i].password=malloc(50);
if(tab[i].password==NULL){
fprintf(stderr, "Erreur d'allocation mémoire pour l'id\n");
fprintf(stderr, "Code erreur : %d\n", errno);
fprintf(stderr, "Erreur : %s\n", strerror(errno));
exit(EXIT_FAILURE);
}
fgets(tab[i].password, 50, f); // get the password in the new tab from UtilisateurTable
tab[i].password[strcspn(tab[i].password, "\n")] = '\0';  // Remove newline character
}

fclose(f);
return tab; 
}
//*/

//ANCIEN CODE DE SAUVEGARDE DISFONCTIONNEL
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
void Utilisateurfile(Utilisateur* tab, int* UtilisateurCount){

FILE* f=NULL;
    f=fopen("UtilisateurTable", "w");
    if(f==NULL){
fprintf(stderr, "On ne peut pas écrire sur le fichier\n");
fprintf(stderr, "Code erreur : %d\n", errno);
fprintf(stderr, "Erreur : %s\n", strerror(errno));
 return;
}

fprintf(f, "%d\n", *UtilisateurCount);

for (int i=0; i<*UtilisateurCount; i++){
        fprintf(f, "%d" "%s",tab[i].id , tab[i].password);
}
fclose(f);       
}

Utilisateur* readfile(int* UtilisateurCount){
    FILE* f=NULL;
    f=fopen("UtilisateurTable", "r");
if (f==NULL){
fprintf(stderr, "On ne peut pas écrire sur le fichier\n");
fprintf(stderr, "Code erreur : %d\n", errno);
fprintf(stderr, "Erreur : %s\n", strerror(errno));
     exit(1);
}
fscanf(f, "%d\n", UtilisateurCount);
Utilisateur* tab=Utilisateur_table(UtilisateurCount);

for (int i=0; i<*UtilisateurCount; i++){
tab[i].id=malloc(sizeof(int));
tab[i].password=malloc(50);


fscanf(f,"%d", tab[i].id);
fgets(tab[i].password, 50, f);
tab[i].password[strcspn(tab[i].password, "\n")] = '\0';
}
fclose(f);
return tab;
}

Utilisateur* Realloc_table(int* UtilisateurCount){
FILE* f=NULL;
f=fopen("UtilisateurTable", "r" );
if(f==NULL){

fprintf(stderr, "On ne peut pas écrire sur le fichier\n");
fprintf(stderr, "Code erreur : %d\n", errno);
fprintf(stderr, "Erreur : %s\n", strerror(errno));
}

Utilisateur* tab=malloc(sizeof(Utilisateur)*(*UtilisateurCount));
if(tab==NULL){
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
}

    fscanf(f, "%d\n", UtilisateurCount);

    for(int i=0; i<*UtilisateurCount; i++){

        tab[i].id=malloc(sizeof(int));
if(tab[i].id==NULL){
fprintf(stderr, "Erreur d'allocation mémoire pour l'id\n");
fprintf(stderr, "Code erreur : %d\n", errno);
fprintf(stderr, "Erreur : %s\n", strerror(errno));
exit(EXIT_FAILURE);
}
fscanf(f,"%d\n", tab[i].id);// get the id in the new tab from UtilisateurTable

tab[i].password=malloc(50);
if(tab[i].password==NULL){
fprintf(stderr, "Erreur d'allocation mémoire pour l'id\n");
fprintf(stderr, "Code erreur : %d\n", errno);
fprintf(stderr, "Erreur : %s\n", strerror(errno));
exit(EXIT_FAILURE);
}
fgets(tab[i].password, 50, f); // get the password in the new tab from UtilisateurTable
tab[i].password[strcspn(tab[i].password, "\n")] = '\0';  // Remove newline character
}

fclose(f);
return tab;
    
}
//*/
