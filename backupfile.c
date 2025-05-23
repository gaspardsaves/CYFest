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


//Free memory allocation of array before killing the application
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
// Save counters in a binary file to be able to recreate the arrays
void SaveCounter(int* userCount, int* roomCount, int* concertCount){
    FILE* f1 = fopen("Counter.bin", "wb+");
    checkOpenFile(f1);
    //int write1 = fwrite(userCount, sizeof(int), 1, f1);
    //checkWritingFile(write1);
    int write2 = fwrite(roomCount, sizeof(int), 1, f1);
    checkWritingFile(write2);
    //int write3 = fwrite(concertCount, sizeof(int), 1, f1);
    //checkWritingFile(write3);
    int close = fclose(f1);
    checkCloseFile(close);
}

// Recovering counters
void ReadCounter(int* userCount, int* roomCount, int* concertCount){
    FILE* f1 = fopen("Counter.bin", "rb+");
    checkOpenFile(f1);
    //fread(userCount, sizeof(int), 1, f1);
    fread(roomCount, sizeof(int), 1, f1);
    //fread(concertCount, sizeof(int), 1, f1);
    int close = fclose(f1);
    checkCloseFile(close);
}


void SaveSaveSit(Salle* s) {
    FILE* f = fopen("SaveSit.bin", "wb");
    // Verify the file pointer is not NULL
    if (f == NULL) {
        perror("Erreur dans l'écriture du fichier SaveSit");
        exit(1);
    }
    // Save each seat from the room (state of seat because it represents the seat materially)
    int tot_seat = s->nb_range * s->nb_siege_range;
    fwrite(s->saveSit, sizeof(Siege), tot_seat, f);
    fclose(f);
}

void ReadSaveSit(Salle* s) {
    FILE* f = fopen("SaveSit.bin", "rb");
    // Verify the file pointer is not NULL
    if (f == NULL) {
        perror("Erreur dans la lecture du fichier SaveSit");
        exit(1);
    }
    printf("Bon read save sit avant siege\n");
    int tot_seat = s->nb_range * s->nb_siege_range;
    printf("Bon read save sit après int\n");
    s->saveSit = malloc(tot_seat * sizeof(Siege));
    printf("Bon read save sit après malloc\n");
    // Verify allocation memory is not NULL
    if (s->saveSit == NULL) {
        perror("Erreur à l'allocation de la mémoire pour saveSit");
        exit(1);
    }
    fread(s->saveSit, sizeof(Siege), tot_seat, f);
    fclose(f);
}


void SaveScene(Salle* s) {
    FILE* f1 = fopen("Scene.bin", "wb");
    // Verify the file pointer is not NULL
    if (f1 == NULL) {
        perror("Erreur dans l'écriture du fichier");
        exit(1);
    }
    // Save details from the room
    fwrite(&s->nb_range, sizeof(int), 1, f1);
    fwrite(&s->nb_siege_range, sizeof(int), 1, f1);
    // Read directly from the static array
    fwrite(s->nom, sizeof(char), 100, f1); 
    // Save details from the room
    fwrite(&s->arange, sizeof(int), 1, f1);
    fwrite(&s->brange, sizeof(int), 1, f1);
    fwrite(&s->prixa, sizeof(float), 1, f1);
    fwrite(&s->prixb, sizeof(float), 1, f1);
    fwrite(&s->prixc, sizeof(float), 1, f1);
    fwrite(&s->state, sizeof(int), 1, f1);
    // Save seats
    for (int i = 0; i < s->nb_range; i++) {
        fwrite(s->siege[i], sizeof(Siege), s->nb_siege_range, f1);
    }
    fclose(f1);
    // Save seats details
    SaveSaveSit(s);
    printf("Bonne sauvegarde de la scene %s\n", s->nom);
}


void ReadScene(Salle* s) {
    FILE* f1 = fopen("Scene.bin", "rb");
    // Verify the file pointer is not NULL
    if (f1 == NULL) {
        perror("Erreur dans la lecture du fichier");
        exit(1);
    }
    // Read details from the room
    fread(&s->nb_range, sizeof(int), 1, f1);
    fread(&s->nb_siege_range, sizeof(int), 1, f1);
    // Read directly from the static array
    fread(&s->nom, sizeof(char), 100, f1);
    fread(&s->arange, sizeof(int), 1, f1);
    fread(&s->brange, sizeof(int), 1, f1);
    fread(&s->prixa, sizeof(float), 1, f1);
    fread(&s->prixb, sizeof(float), 1, f1);
    fread(&s->prixc, sizeof(float), 1, f1);
    fread(&s->state, sizeof(int), 1, f1);
    // Allocate memory for seats
    s->siege = malloc(s->nb_range * sizeof(Siege*));

    for (int i = 0; i < s->nb_range; i++) {
        s->siege[i] = malloc(s->nb_siege_range * sizeof(Siege));

        // Verify allocation memory is not NULL
        if (s->siege[i] == NULL) {
            perror("Erreur allocation dynamique du nombre de sièges par rangée");
            exit(1);
        }
    // Read seats details  
    fread(s->siege[i], sizeof(Siege), s->nb_siege_range, f1);
    }
    fclose(f1);

    // Read saveSit
    printf("Bon read scene avant seat\n");
    ReadSaveSit(s);
    printf("ReadScene BIEN effectué\n");
}

Salle SavePointeurSiege(Salle S) {
    int tot_seat = S.nb_range * S.nb_siege_range;
    // Allocate memory for room
    S.saveSit = malloc(tot_seat * sizeof(Siege));
    // Verify allocation memory is not NULL
    if (S.saveSit == NULL) {
        perror("Erreur à l'allocation de la mémoire pour saveSit");
        exit(EXIT_FAILURE);
    }
    int k = 0;
    // Save details of each seat (state seat=>seat materially)
    for (int i = 0; i < S.nb_range; i++) {
        for (int j = 0; j < S.nb_siege_range; j++) {
            S.saveSit[k++] = S.siege[i][j];
        }
    }
    printf("Bon save pointeurs siege\n");
    return S;
}

Salle ReadPointeurSiege(Salle S) {
    S.siege = malloc(S.nb_range * sizeof(Siege*));
    // Verify allocation memory is not NULL
    if (S.siege == NULL) {
        perror("Erreur allocation mémoire du nombre de rangées");
        exit(1);
    }
    for (int i = 0; i < S.nb_range; i++) {
        S.siege[i] = malloc(S.nb_siege_range * sizeof(Siege));
        // Verify allocation memory is not NULL
        if (S.siege[i] == NULL) {
            perror("Erreur allocation dynamique du nombre de sièges par rangée");
            exit(1);
        }
    }
    // Read details of each seat (state seat=>seat materially)
    int k = 0;
    for (int i = 0; i < S.nb_range; i++) {
        for (int j = 0; j < S.nb_siege_range; j++) {
            S.siege[i][j] = S.saveSit[k++];
        }
    }
    printf("ReadPointeurSiege Bien effectué \n");
    printf(" \n");
    printf(" \n");
    return S;
}



/*

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

void SaveCounter(int* CounterRoom, int* CounterConcert, int* CounterUser){
    FILE* f1 = fopen("Counter.bin", "wb+");
    fwrite(CounterRoom, sizeof(int), 1, f1);
    fwrite(CounterConcert, sizeof(int), 1, f1);
    fwrite(CounterUser, sizeof(int), 1, f1);
    fclose(f1);
}

void ReadCounter(int* CounterRoom, int* CounterConcert, int* CounterUser){
    FILE* f1 = fopen("Counter.bin", "rb+");
    fread(CounterRoom, sizeof(int), 1, f1);
    fread(CounterConcert, sizeof(int), 1, f1);
    fread(CounterUser, sizeof(int), 1, f1);
    fclose(f1);
}

//*/
