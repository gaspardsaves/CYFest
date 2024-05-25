#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structures.h"
#include "color.h"
#include "smartrobusnest.h"
#include "manager.h"
#include "festivalgoers.h"

//*
void connectionFestivalGoers(int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert) {
    char passwordco[30];
    int idco = better_scan("Heureux de vous revoir\nSaisir votre identifiant\n");
    if (idco==0) {
        choiceCoFestivalGoers(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
    }
    int retour1 = checkIdFest(tabFest, userCount, idco);
    if (retour1 == -1) {
        return;
    }
    printf("Saisir votre mot de passe\n");
    fgets(passwordco, sizeof(passwordco), stdin);
    passwordco[strcspn(passwordco, "\n")] = '\0';
    int retour2 = checkPasswordFest(tabFest, userCount, passwordco, idco);
    if (retour2 == 1) {
        printf("Connexion réussie\n");
        interfaceFestivalGoers(idco, userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
    }
    else {
        color("33");
        printf("Erreur de connexion, merci de réessayer\n");
        color("37");
        choiceUser (userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
    }
}
//*/

void choiceCoFestivalGoers (int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert) {
    unsigned co2=-3;
    color("31");
    printf("Vous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\n");
    color("37");
    co2=better_scanUn("Vous avez choisi festivalier.\nQuelle est votre situation ?\n1 pour créer un compte\n2 pour se connecter\n");
    switch(co2){
        case 0:
            choiceUser(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        case 1:
            accountCreationFestivalGoers(userCount, &tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        case 2:
            connectionFestivalGoers(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        default:
            color("33");
            printf("Erreur de saisie\n");
            color("37");
            choiceCoFestivalGoers(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
        break;
    }
}

void connectionManager(int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert){
    int codemanag;
    color("31");
    printf("Vous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\n");
    color("37");
    codemanag=better_scan("Vous avez choisi manager\nSaisir le code\n");
        switch(codemanag){
            case 0:
                choiceUser(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
                break;
            case 2000:
                printf("Code bon\n");
                interfaceManager(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
                break;
            default:
                color("33");
                printf("Erreur de saisie\n");
                color("37");
                connectionManager(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        }
}

void choiceUser (int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert){
    unsigned co1=-3;
    color("31");
    printf("Vous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\n");
    color("37");
    co1=better_scanUn("Choisir votre interface de connexion :\n1 pour Festivalier\n2 pour Manager\n");
    switch(co1){
        case 0:
            //freeArray(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            exit(0);
            break;
        case 1:
            choiceCoFestivalGoers(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        case 2:
            connectionManager(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        default:
            color("33");
            printf("Erreur de saisie\n");
            color("37");
            choiceUser(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
    }
}

int main (){
    srand(time(NULL));
    //int nbrUser = openBackupfile();
    //IL FAUT REOUVRIR L'ENSEMBLE DES FICHIERS ICI
    //EN APPELANT DES FONCTIONS DE BACKUPFILE ET TOUT 
    //STOCKER DANS DES POINTEURS QU'ON VA TRIMBALER
    //DANS LA SUITE DU PROGRAMME

    //ne pas toucher les lignes qui suivent, elles me permettent de tester la partie festivalier
    int nbrUser = 0;
    int* userCount = &nbrUser;
    Utilisateur* tabFest = constrTabFestivalGoers(userCount);
    //*
    int nbrRoom = 0;
    int* roomCount = &nbrRoom;
    Salle* tabRoom=createTabRoom(roomCount);
    int nbrConcert = 0;
    int* concertCount = &nbrConcert;
    Concert* tabConcert=createTabConcert(concertCount);
    //*/
    choiceUser(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
    return 0;
}