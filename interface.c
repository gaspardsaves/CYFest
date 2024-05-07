#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Interface                          -----------------------------------
typedef struct {
    int admin; //1
    int id;
    char* password;
} Manager;

typedef struct {
    int admin; //0
    int id; 
    char* password;
    int** resa; // double tableau qui contient les concerts et les sièges associés à ces derniers;
    int porte_feuille;
} Utilisateur; 

// Concert                           --------------------------------

typedef struct {
    int etat_salle; 
    int categorie;
    int prix;
    int nombre_personne;
    int fosse; // fosse ou pas f?1:0
    Utilisateur id[20];
} Siege;

typedef struct {
    int** siege[10]; // double tableau qui va contenir  
    int nb_range;
    int nb_siege_range;
    int nb_cat_par_ranger;
//déterminer le la catégorie C
// malloc les sièges
} Salle; 

typedef struct {
    char guest;
    int horaire_d;
    int horaire_f;
    Salle salle;
} Concert;

typedef struct {
    int concert[10];
// Tableau qui contient tout les concerts
} Festival;

void checkPasswordFest

void connexionFestivalier (){
    char password[30];
    int retour1, retour2;
    //printf("\033[31mVous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\033[00m\n");
    //Voir pour revenir en arrière
    printf("Heureux de vous revoir\nSaisir votre identifiant");

    printf("")
    scanf("%s",&password);
    //Voir pour bidouillage du double tableau idem pour identifiant
    retour2=strcmp(password,tabpassword[i]);
    

}

void choixCoFestivalier () {
    unsigned co2=-3;
    printf("\033[31mVous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\033[00m\n");
    printf("Vous avez choisi festivalier.\nQuelle est votre situation ?\n1 pour créer un compte\n2 pour se connecter\n");
    scanf("%d", &co2);
    switch(co2){
        case 0:
            choixUtilisateur();
            break;
        case 1:
            printf("ok pour creation compte festivalier\n");
            //constrCompteFestivalier();
            break;
        case 2:
            printf("okprêtpourconnexionfetivalier\n");
            //connexionFestivalier();
            break;
        default:
            printf("Erreur de saisie\n");
            choixCoFestivalier();
        break;
    }
}

void connexionManager(){
    int codemanag;
    printf("\033[31mVous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\033[00m\n");
    printf("Vous avez choisi manager\nSaisir le code\n");
    scanf("%d", &codemanag);
        switch(codemanag){
        case 0:
            choixUtilisateur();
            break;
        case 1:
            printf("Code bon\n");
            //interfaceManager();
            break;
        default:
            printf("\033[33mErreur de saisie\033[00m\n");
            connexionManager();
            break;
    }

}

void choixUtilisateur (){
    unsigned co1=-3;
    printf("\033[31mVous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\033[00m\n");
    printf("Choisir votre interface de connexion :\n1 pour Festivalier\n2 pour Manager\n");
    scanf("%d", &co1);
    switch(co1){
        case 0:
            exit(EXIT_FAILURE);
            break;
        case 1:
            choixCoFestivalier();
            break;
        case 2:
            connexionManager();
            break;
        default:
            printf("Erreur de saisie\n");
            choixUtilisateur();
            break;
    }
}

int main (){
    choixUtilisateur();
    return 0;
}