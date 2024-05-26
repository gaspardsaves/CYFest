#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structures.h"
#include "color.h"
#include "smartrobusnest.h"
#include "backupfile.h"
#include "hour.h"
#include "manager.h"
#include "festivalgoers.h"

void connectionFestivalGoers(int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert) {
    char passwordco[30];
    
    // User enters his id
    int idco = better_scan("Heureux de vous revoir\nSaisir votre identifiant\n");
    if (idco==0) {
        choiceCoFestivalGoers(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
    }

    // Check if id exists
    int retour1 = checkIdFest(tabFest, userCount, idco);
    if (retour1 == -1) {
        choiceUser (userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
    }
    printf("Saisir votre mot de passe\n");
    fgets(passwordco, sizeof(passwordco), stdin); // Get passsword
    passwordco[strcspn(passwordco, "\n")] = '\0'; // Remove the newline character from the input

    // Check if the entered password is correct
    int retour2 = checkPasswordFest(tabFest, userCount, passwordco, idco);
    if (retour2 == 1) {
        // If the password is correct, print the success message down below
        printf("Connexion réussie\n");
        interfaceFestivalGoers(idco, userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
    }
    else {
        // Invalid password, print the error message down below
        color("33");
        printf("Erreur de connexion, merci de réessayer\n");
        color("37");
        choiceUser (userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
    }
}

void choiceCoFestivalGoers (int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert) {
    unsigned co2=-3;
    color("31");
    printf("Vous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\n");
    color("37");
    // User chooses what he wants to do
    co2=better_scanUn("Vous avez choisi festivalier.\nQuelle est votre situation ?\n1 pour créer un compte\n2 pour se connecter\n");
    switch(co2){
        case 0:
            // User chooses 0 for to go back
            choiceUser(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        case 1:
            // User chooses 1 to create an account
            accountCreationFestivalGoers(userCount, &tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        case 2:
            // User chooses 2 to log in
            connectionFestivalGoers(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        default:
            // Invalid inputs
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
    
    // User enters manager code
    codemanag=better_scan("Vous avez choisi manager\nSaisir le code\n");
    
        switch(codemanag){
            case 0:
                // User chooses 0 to go back
                choiceUser(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
                break;
            case 2000:
               // User chooses 2000 to enter into interface manager
                printf("Code bon\n");
                interfaceManager(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
                break;
            default:
                // Invalid inputs
                color("33");
                printf("Erreur de saisie\n");
                color("37");
                connectionManager(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        }
}

void choiceUser (int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert){
    unsigned co1=-3;
    tabConcert=verifTabConcert(tabConcert, concertCount);
    color("31");
    printf("Vous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\n");
    color("37");
    // User chooses what he wants to do
    co1=better_scanUn("Choisir votre interface de connexion :\n1 pour Festivalier\n2 pour Manager\n");
    switch(co1){
        case 0:
            // Users chooses 0 to exit
            for(int i=0; i<(*roomCount); i++){
                tabRoom[i]=SavePointeurSiege(tabRoom[i]);
                SaveScene(&(tabRoom[i]));
            }
            SaveCounter(userCount, roomCount, concertCount);
            arrayFree(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            exit(0);
            break;
        case 1:
            // User chooses 1 to action in choiceCoFestivalGoers function
            choiceCoFestivalGoers(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        case 2:
            // User chooses 2 to log in as manager
            connectionManager(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        default:
            // Invalid inputs
            color("33");
            printf("Erreur de saisie\n");
            color("37");
            choiceUser(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
    }
}

int main (){
    srand(time(NULL));
    // Initialize user count and user array
    // Initialize room count and room array
    // Initialize concert count and concert array
    int nbrUser = 0;
    int* userCount = &nbrUser;
    int nbrRoom = 0;
    int* roomCount = &nbrRoom;
    int nbrConcert = 0;
    int* concertCount = &nbrConcert;
    ReadCounter(userCount, roomCount, concertCount);
    Utilisateur* tabFest = constrTabFestivalGoers(userCount);
    Salle* tabRoom=createTabRoom(roomCount);
    for(int i=0; i<(*roomCount); i++){
        ReadScene(&(tabRoom[i]));
        tabRoom[i]=ReadPointeurSiege(tabRoom[i]);
    }
    Concert* tabConcert=createTabConcert(concertCount);
    // Verify the hour
    for(int i=0; i<(*roomCount); i++){
        dRoom((tabRoom[i]));
    }
    // Start user interface
    choiceUser(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
    return 0;
}
