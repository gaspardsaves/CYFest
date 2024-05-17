#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "smartrobusnest.h"
#include "manager.h"
//#include "festivalgoers.h"

/*unsigned better_scanUn(char * message){
    int ret_var = 0;
    unsigned value = 1;
  while (ret_var != 1 || value < 0)
    {   
        printf("%s", message);
        ret_var = scanf("%d", &value);
        while(getchar()!='\n'){} // Ligne facultative de sécurisation
    }
    return value;
}

int better_scan(char * message){
    int ret_var = 0;
    int value = 1;
  while (ret_var != 1 || value < 0)
    {   
        printf("%s", message);
        ret_var = scanf("%d", &value);
        while(getchar()!='\n'){} // Ligne facultative de sécurisation
    }
    return value;
}*/

/*int checkIdFest (char idco[30], char* tabid[]){
    int retour = strcmp(idco, tabid);
    if (retour==0) {
        printf("Identifiant correct\n");
        return 1;
    }
    else {
        printf("Cet identifiant n'existe pas\n");
        return -1;
    }
}

int checkPasswordFest (int idco, char passwordco[30], ){
    int retour = strcmp(passwordco,);
    if(retour==NULL){
        printf("Mot de passe correct\n");
        return 1;
    }
    else {
        printf("Erreur de saisie\n");
        return -1;
    }
}*/

/*void connectionFestivalgoers (){
    char passwordco[30];
    char idco[30];
    printf("\033[31mVous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\033[00m\n");
    printf("Heureux de vous revoir\nSaisir votre identifiant");
    scanf("%s", idco);
    if (idco==0){
        choiceCoFestivalGoers();
    }
    //int retour1 = checkIdFest(idco, tabid);
    //if (retour1==-1){
        //connexionFestivalier();
    //}
    printf("Saisir votre mot de passe\n");
    scanf("%s",passwordco);
    if (passwordco==0){
        choiceCoFestivalGoers();
    }
    //Voir pour bidouillage du double tableau idem pour identifiant
    //int retour2 = checkPasswordFest (idco, passwordco, tabpassword); 
    //if (retour2==1) {
        //interfaceFestivalier(idco);
    //}
    else {
        printf("Erreur de connexion, merci de réassayer\n");
        choiceCoFestivalGoers();
    }
}*/

void choiceCoFestivalGoers () {
    unsigned co2=-3;
    printf("\033[31mVous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\033[00m\n");
    co2=better_scanUn("Vous avez choisi festivalier.\nQuelle est votre situation ?\n1 pour créer un compte\n2 pour se connecter\n");
    switch(co2){
        case 0:
            choiceUser();
            break;
        case 1:
            printf("ok pour creation compte festivalier\n");
            //constrCompteFestivalier();
            break;
        case 2:
            printf("okprêtpourconnexionfetivalier\n");
            //connectionFestivalGoers();
            break;
        default:
            printf("Erreur de saisie\n");
            choiceCoFestivalGoers();
        break;
    }
}

void connectionManager(){
    int codemanag;
    printf("\033[31mVous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\033[00m\n");
    codemanag=better_scan("Vous avez choisi manager\nSaisir le code\n");
        switch(codemanag){
        case 0:
            choiceUser();
            break;
        case 2000:
            printf("Code bon\n");
            interfaceManager();
            break;
        default:
            printf("\033[33mErreur de saisie\033[00m\n");
            connectionManager();
            break;
    }

}

void choiceUser (){
    unsigned co1=-3;
    printf("\033[31mVous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\033[00m\n");
    co1=better_scanUn("Choisir votre interface de connexion :\n1 pour Festivalier\n2 pour Manager\n");
    switch(co1){
        case 0:
            exit(0);
            break;
        case 1:
            choiceCoFestivalGoers();
            break;
        case 2:
            connectionManager();
            break;
        default:
            printf("Erreur de saisie\n");
            choiceUser();
            break;
    }
}

int main (){
    choiceUser();
    return 0;
}