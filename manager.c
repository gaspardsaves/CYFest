#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "couleur.h"
#include "structures.h"
#include "interface.h"
#include "manager.h"


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
    if((s.categorie==1)&&(s.fosse==1)){
        if(s.nombre_personne==0){
            printf("oo\t");
        }
        else if (s.nombre_personne==1){
            printf("xo\t");
        }
        else if(s.nombre_personne==2){
            printf("xx\t");
        }
    }
    else if (s.etat_siege){
        printf("X\t");
    }
    else if(!(s.etat_siege)){
        printf("O\t");
    }
    couleur("0");
}

Date getdate(){
    Date d;
    printf("Donnez la date exacte du concert \n");
    printf("L'année\n");
    scanf("%d", &d.year);
    while(d.year<2024){
        printf("Mauvaise saisi, recommencer\n");
        scanf("%d", &d.year);
    }
    printf("Le mois\n");
    scanf("%d", &d.month);
    while((d.month<1)||(d.month>12)){
        printf("Mauvaise saisi, recommencer\n");
        scanf("%d", &d.month);
    }
    printf("Le jour\n");
    scanf("%d", &d.day);
    printf("L'heure\n");
    scanf("%d", &d.hour);
    while((d.hour<0)||(d.hour>23)){
        printf("Mauvaise saisi, recommencer\n");
        scanf("%d", &d.hour);
    }
    printf("La minute\n");
    scanf("%d", &d.minut);
    while((d.minut<0)||(d.minut>59)){
        printf("Mauvaise saisi, recommencer\n");
        scanf("%d", &d.minut);
    }
    return d;
}

Salle constructSalle(){
    Salle s;
    int i = 0;
    int j = 0;
    printf("Choississez le nombre de rangé\n");
    scanf("%d", &s.nb_range);
    while(s.nb_range<1){
        printf("Mauvaise saisi, recommencer\n");
        scanf("%d", &s.nb_range);
    }
    printf("Choississez le nombre de siege par rangé\n");
    scanf("%d", &s.nb_siege_range);
    while(s.nb_siege_range<1){
        printf("Mauvaise saisi, recommencer\n");
        scanf("%d", &s.nb_siege_range);
    }
    printf("Combien de catégorie A par range\n");
    scanf("%d", &s.arange);
    while((s.arange<0)&&(s.arange>s.nb_range)){
        printf("Mauvaise saisi, recommencer\n");
        scanf("%d", &s.arange);
    }
    printf("Donnez le prix de la catégorie A\n");
    scanf("%f", &s.prixa);
    while(s.prixa<0){
        printf("Mauvaise saisi, recommencer\n");
        scanf("%f", &s.prixa);
    }
    printf("Combien de catégorie B par range\n");
    scanf("%d", &s.brange);
    while((s.brange<0)||((s.arange+s.brange)>s.nb_range)){
        printf("Mauvaise saisi, recommencer\n");
        scanf("%d", &s.brange);
    }
    printf("Donnez le prix de la catégorie B\n");
    scanf("%f", &s.prixb);
    while(s.prixb<0){
        printf("Mauvaise saisi, recommencer\n");
        scanf("%f", &s.prixb);
    }
    printf("Donnez le prix de la catégorie C\n");
    scanf("%f", &s.prixc);
    while(s.prixc<0){
        printf("Mauvaise saisi, recommencer\n");
        scanf("%f", &s.prixc);
    }
    int a = s.arange;
    int b = s.brange;
    s.siege = malloc(s.nb_range*sizeof(Siege));
    while(i<s.nb_range){
        s.siege[i] = malloc(s.nb_siege_range*sizeof(Siege));
        while(j<s.nb_siege_range){
            if(a>0){
                s.siege[i][j] = constructSiege(1, s.prixa, 0);
            }
            else if(b>0){
                s.siege[i][j] = constructSiege(2, s.prixb, 0);
            }
            else{
                s.siege[i][j] = constructSiege(3, s.prixc, 0);
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
    return s;
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

Concert* creetabConcert(int n){
    Concert* tab = malloc(n*sizeof(Concert));
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

Salle ClasseAetFosse(Salle s, int n){
    int i = 0;
    int j = 0;
    while(i<s.arange){
        while(j<s.nb_siege_range){
            s.siege[i][j].fosse= n;
            j++;
        }
        j=0;
        i++;
    }
    return s;
}

Salle modifsalle(Salle s){
    int b = 0;
    printf("\nVoulez vous changer le prix de la categorie A ?\n");
    scanf("%d", &b);
    if(b==1){
        printf("Quelle est le nouveau prix de la catégorie A ?\n");
        scanf("%f", &s.prixa);
    }
    b=0;
    printf("\nVoulez vous changer le prix de la categorie B ?\n");
    scanf("%d", &b);
    if(b==1){
        printf("Quelle est le nouveau prix de la catégorie B ?\n");
        scanf("%f", &s.prixb);
    }
    b=0;
    printf("\nVoulez vous changer le prix de la categorie C ?\n");
    scanf("%d", &b);
    if(b==1){
        printf("Quelle est le nouveau prix de la catégorie C ?\n");
        scanf("%f", &s.prixc);
    }
    b=0;
    printf("Voulez-vous une fosse \n");
    printf("1 pour oui \n");
    printf("2 pour non \n");
    scanf("%d", &b);
    ClasseAetFosse(s, b);
    b=0;
    return s;
}

void SauvegardeSalleFichier(Salle* s){
    FILE* f1 = fopen("SaveScene.bin", "wb");
    fwrite(s, sizeof(Salle), 1, f1);
     fclose(f1);
}

Salle LireSallefichier(Salle* s2){
    FILE* f1 = fopen("SaveScene.bin", "rb");
    fread(s2, sizeof(Salle),1,f1);
    fclose(f1);
    return *s2;
}

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
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
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
    printf("2 pour créer un concert\n3 pour créer un festival\n4 pour obtenir un rapport sur un concert\n");
    scanf("%d", &choiceAction);
    switch(choiceAction){
        case 0:
            choiceUser();
            break;
        case 1:
            numberRoom();
            break;
        case 2:
            //creerconcert(tabdesalle);
            break;
        default:
            printf("Erreur de saisie\n");
            interfaceManager();
            break;
    }
}
