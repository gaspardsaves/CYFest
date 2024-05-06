#include <stdio.h>
#include <stdlib.h>

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

int main (){
    int co1, co2, codemanag;
    printf("Choisir votre interface de connexion :\n1 pour manager\n2 pour festivalier\n");
    scanf("%d", &co1);
    //A faire éventuellement dans smartrobusnest mais potentiellement à voir la gestion d'erreur
    if(co1==1) {
        printf("Vous avez choisi manager\nSaisir le code\n");
        scanf("%d", &codemanag);
        //A voir pour les appels de fonctions croisés entre les fichiers
    }
    else if (co1==2) {
        printf("Vous avez choisi festivalier.\nQuelle est votre situation ?\n1 : créer un compte\n2 : Connexion\n");
        scanf("%d", &co2);
        //A voir pour les appels de fonctions
    }
    else {
        printf("Erreur de saisie\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}