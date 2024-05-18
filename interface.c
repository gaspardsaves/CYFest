#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "smartrobusnest.h"
#include "manager.h"
#include "festivalgoers.h"

//*
void connectionFestivalGoers (int* userCount){
    char passwordco[31];
    printf("\033[31mVous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\033[00m\n");
    int idco = better_scan("Heureux de vous revoir\nSaisir votre identifiant");
    if (idco==0){
        choiceCoFestivalGoers(userCount);
    }
    int retour1 = checkIdFest(tabFest, userCount, idco);
    if (retour1==-1){
        connectionFestivalGoers(userCount);
    }
    printf("Saisir votre mot de passe\n");
    scanf("%s",passwordco);
    if (passwordco==0){
        choiceCoFestivalGoers(userCount);
    }
    int retour2 = checkPasswordFest (tabFest, userCount, passwordco); 
    if (retour2==1) {
        interfaceFestivalGoers(idco);
    }
    else {
        printf("Erreur de connexion, merci de réassayer\n");
        choiceCoFestivalGoers(userCount);
    }
}
//*/

void choiceCoFestivalGoers (int* userCount) {
    unsigned co2=-3;
    printf("\033[31mVous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\033[00m\n");
    co2=better_scanUn("Vous avez choisi festivalier.\nQuelle est votre situation ?\n1 pour créer un compte\n2 pour se connecter\n");
    switch(co2){
        case 0:
            choiceUser(userCount);
            break;
        case 1:
            printf("ok pour creation compte festivalier\n");
            //accountCreationFestivalGoers(int* userCount);
            break;
        case 2:
            printf("okprêtpourconnexionfetivalier\n");
            //connectionFestivalGoers(int* userCount);
            break;
        default:
            printf("Erreur de saisie\n");
            choiceCoFestivalGoers(userCount);
        break;
    }
}

void connectionManager(int* userCount){
    int codemanag;
    printf("\033[31mVous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\033[00m\n");
    codemanag=better_scan("Vous avez choisi manager\nSaisir le code\n");
        switch(codemanag){
            case 0:
                choiceUser(userCount);
                break;
            case 2000:
                printf("Code bon\n");
                interfaceManager(userCount);
                break;
            default:
                printf("\033[33mErreur de saisie\033[00m\n");
                connectionManager(userCount);
            break;
        }
}

void choiceUser (int* userCount){
    unsigned co1=-3;
    printf("\033[31mVous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\033[00m\n");
    co1=better_scanUn("Choisir votre interface de connexion :\n1 pour Festivalier\n2 pour Manager\n");
    switch(co1){
        case 0:
            exit(0);
            break;
        case 1:
            choiceCoFestivalGoers(userCount);
            break;
        case 2:
            connectionManager(userCount);
            break;
        default:
            printf("Erreur de saisie\n");
            choiceUser(userCount);
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
    choiceUser(userCount);
    return 0;
}