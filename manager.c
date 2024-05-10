#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "couleur.h"
#include "structures.h"
#include "interface.h"


Siege constructSiege(int cat, int price, int f){
    Siege s;
    s.etat_siege = 0;
    s.categorie = cat;
    s.prix = price;
    s.fosse = f;

    return s;
}

void affiche_siege(char* color, Siege s){
    couleur(color);
    if (s.etat_siege){
        printf("X ");
    }
    else if(!(s.etat_siege)){
        printf("O ");
    }
    couleur("0");
}

Date getdate(){
    Date d;
    printf("Donnez la date exacte du concert \n");
    printf("L'année\n");
    scanf("%d", &d.year);
    printf("Le mois\n");
    scanf("%d", &d.month);
    printf("Le jour\n");
    scanf("%d", &d.day);
    printf("L'heure\n");
    scanf("%d", &d.hour);
    printf("La minute\n");
    scanf("%d", &d.minut);
    return d;
}

Salle constructSalle(){
    Salle S;
    int i = 0;
    int j = 0;
    printf("Choississez le nombre de rangé\n");
    scanf("%d", &S.nb_range);
    
    printf("Choississez le nombre de siege par rangé\n");
    scanf("%d", &S.nb_siege_range);
    printf("Combien de catégorie A par range\n");
    scanf("%d", &S.arange);
    printf("Donnez le prix de la catégorie A\n");
    scanf("%d", &S.prixa);
    printf("Combien de catégorie B par range\n");
    scanf("%d", &S.brange);
    printf("Donnez le prix de la catégorie B\n");
    scanf("%d", &S.prixb);
    printf("Donnez le prix de la catégorie C\n");
    scanf("%d", &S.prixc);
    int a = S.arange;
    int b = S.brange;
    S.siege = malloc(S.nb_range*sizeof(Siege*));
    while(i<S.nb_range){
        S.siege[i] = malloc(S.nb_siege_range*sizeof(Siege));
        while(j<S.nb_siege_range){
            if(a>0){
                S.siege[i][j] = constructSiege(1, S.prixa, 0);
            }
            else if(b>0){
                S.siege[i][j] = constructSiege(2, S.prixb, 0);
            }
            else{
                S.siege[i][j] = constructSiege(3, S.prixc, 0);
            }
            
            j++;
        }
        if(a>0){
            a--;
        }
        else if(b>0){
            b--;
        }
        j=0;
        i++;
    }
    return S;
}

void affichesalle(Salle S){
    int i = 0;
    int j = 0;
    while(i<S.nb_range){
        while(j<S.nb_siege_range){
            switch (S.siege[i][j].categorie){
                case 1 :
                    affiche_siege("32", S.siege[i][j]);
                    break;
                case 2 :
                    affiche_siege("33", S.siege[i][j]);
                    break;
                case 3:
                    affiche_siege("37", S.siege[i][j]);
                    break;
                default:
                    break;
            }
            
        j++;
        }
    printf("\n");
    j=0;
    i++;
    }
}

Concert creerconcert(Tabdesalle t){
    Concert c;
    printf("Quelle est le nom de et le prénom de l'artiste ?\n");
    scanf("%s", c.guest);
    printf("Donnez la date du début\n");
    c.horaired = getdate();
    printf("Donnez la date de fin\n");
    c.horaired = getdate();
    int i = 0;
    int b = 0;
    int n = sizeof(t);
    while((i<n)&&(b!=1)){
        printf("Es que vous voulez cette salle %s\n", *t.tab[i].nom);
        printf("1 pour oui \n");
        printf("2 pour non \n");
        scanf("%d", &b);
        i++;
    }
    if(b){
        c.salle = t.tab[i];
    }
    return c;
}

Salle* creetabSalle(int n){
    Salle* tab = malloc(n*sizeof(Salle));
    return tab;
}

Salle* creationPlusieursSalles(int numberRoom){
    Salle* S = creetabSalle(numberRoom);
    int i = 0;
    while(i<numberRoom){
        S[i] = constructSalle();
        i++;
    }
    return S;
}

//Salle* AjoutDeSalle(Salle* tab){
    //int n = sizeof(tab);
    //tab = realloc(tab, sizeof(Salle)*(n+1));
    //tab[n] = ConstructSalle();
    //return tab;
//}

void numberRoom(){
    int numberRoom;
    printf("\033[31mVous pouvez revenir en arrière à chaque étape ou interrompre en saisissant 0\033[00m\n");
    printf("Combien de salles souhaitez-vous créer (10 maximum)?\n");
    scanf("%d", &numberRoom);
        switch(numberRoom){
        case 0:
            interfaceManager();
            break;
        case 1:
            constructSalle();
            break;
        case 2 3 4 5 6 7 8 9 10:
            creationPlusieursSalles(numberRoom);
            break;
        default:
            printf("Erreur de saisie\n");
            interfaceManager();
            break;
    }


}

void interfaceManager (){
    int choiceAction;
    printf("Bonjour Admin 👋\nQue souhaitez vous faire ?\n0 pour se déconnecter\n1 pour créer une/des salle\n");
    printf("2 pour créer un concert\n");
    scanf("%d", &choiceAction);
    switch(choiceAction){
        case 0:
            choixUtilisateur();
            break;
        case 1:
            numberRoom();
            break;
        case 2:
            creerconcert();
            break;
        default:
            printf("Erreur de saisie\n");
            interfaceManager();
            break;
    }
}


int main (){
    Salle s = constructSalle();
    affichesalle(s);
    Salle* tab;
    return 0;
}
