#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color.h"
#include "structures.h"
#include "interface.h"
#include "manager.h"
#include "smartrobusnest.h"

Siege constructSiege(int cat, int price, int f){
    Siege s;
    s.etat_siege = 0;
    s.categorie = cat;
    s.prix = price;
    s.fosse = f;

    return s;
}

Salle ResetScene(Salle s){
    int i = 0;
    int j = 0;
    while(i<s.nb_range){
        while(j<s.nb_siege_range){
            s.siege[i][j].nombre_personne = 0;
            s.siege[i][j].etat_siege = 0;
            j++;
        }
        j = 0;
        i++;
    }
    return s;
}

void displaySiege(char* color, Siege s){
    couleur(color);
    if((s.categorie==1)&&(s.fosse==1)){
        if(!s.etat_siege){
            printf("oo\t");
        }
        else if (s.nombre_personne==1){
            printf("xo\t");
        }
        else if((s.nombre_personne==2)||(s.etat_siege)){
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

Salle FreeTheSceneAfterConcert(Salle s){
    int i = 0;
    int j = 0;
    while(i<s.nb_range){
        while(j<s.nb_siege_range){
            if(s.siege[i][j].etat_siege==1){
                s.siege[i][j].etat_siege = 0;
            }
            j++;
        }
        j=0;
        i++;
    }
    return s;
}

Date getDate(){
    Date d;
    d.year=better_scan("L'année\n");
    while(d.year<2024){
        d.year=better_scan("Mauvaise saisie, recommencez\n");
    }
    d.month=better_scan("Le mois\n");
    while((d.month<1)||(d.month>12)){
        d.month=better_scan("Mauvaise saisie, recommencez\n");
    }
    d.day=better_scan("Le jour\n");
    while((d.day<1)||(d.day>30)){
        d.day=better_scan("Mauvaise saisie, recommencez\n");
    }
    d.hour=better_scan("L'heure\n");
    while((d.hour<0)||(d.hour>23)){
        d.hour=better_scan("Mauvaise saisie, recommencez\n");
    }
    d.minut=better_scan("La minute\n");
    while((d.minut<0)||(d.minut>59)){
        d.minut=better_scan("Mauvaise saisie, recommencez\n");
    }
    return d;
}

Salle constructRoom(){
    Salle s;
    int i = 0;
    int j = 0;
    // Il faut que tu mette un gets pour le nom de la salle stp
    s.nb_range=better_scan("Choississez le nombre de rangées\n");
    while(s.nb_range<1){
        s.nb_range=better_scan("Mauvaise saisie, recommencez\n");
    }
    s.nb_siege_range=better_scan("Choississez le nombre de sieges par rangées\n");
    while(s.nb_siege_range<1){
        s.nb_siege_range=better_scan("Mauvaise saisie, recommencez\n");
    }
    s.arange=better_scan("Combien de rangées en catégorie A\n");
    while((s.arange<0)&&(s.arange>s.nb_range)){
        s.arange=better_scan("Mauvaise saisie, recommencez\n");
    }
    s.prixa=better_scanFloat("Donnez le prix de la catégorie A\n");
    while(s.prixa<0){
        s.prixa=better_scanFloat("Mauvaise saisie, recommencez\n");
    }
    s.brange=better_scan("Combien de rangées en catégorie B\n");
    while((s.brange<0)||((s.arange+s.brange)>s.nb_range)){
        s.brange=better_scan("Mauvaise saisie, recommencez\n");
    }
    s.prixb=better_scanFloat("Donnez le prix de la catégorie B\n");
    while(s.prixb<0){
        s.prixb=better_scanFloat("Mauvaise saisie, recommencez\n");
    }
    s.prixc=better_scanFloat("Donnez le prix de la catégorie C\n");
    while(s.prixc<0){
        s.prixc=better_scanFloat("Mauvaise saisie, recommencez\n");
    }
    int a = s.arange;
    int b = s.brange;
    s.siege = malloc(s.nb_range*sizeof(Siege));
    verifpointer(s.siege);
    while(i<s.nb_range){
        s.siege[i] = malloc(s.nb_siege_range*sizeof(Siege));
        verifpointer(s.siege[i]);
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

void displayRoom(Salle S){
    int i = 0;
    int j = 0;
    while(i<S.nb_range){
        while(j<S.nb_siege_range){
            if (!S.siege[i][j].etat_siege){
                switch (S.siege[i][j].categorie){
                    case 1 :
                        displaySiege("32", S.siege[i][j]);
                        break;
                    case 2 :
                        displaySiege("33", S.siege[i][j]);
                        break;
                    case 3:
                        displaySiege("37", S.siege[i][j]);
                        break;
                    default:
                        break;
                }
            }
            else{
                affiche_siege("31", S.siege[i][j]);
            }
        j++;
        }
    printf("\n");
    j=0;
    i++;
    }
}

Concert createConcert(Concert* tabConcert, Salle* tabRoom){
    Concert c;
    printf("Quel est le nom de et le prénom de l'artiste ?\n");
    scanf("%s", c.guest);
    printf("Saississez les éléments demandés sur la date et l'heure de début du concert\n");
    c.horaired = getDate();
    printf("Saississez les éléments demandés sur la date et l'heure de fin du concert\n");
    c.horaired = getDate();
    int i = 0;
    int b = 0;
    int j = 0;
    int n = sizeof(tabRoom);
    while((i<n)&&(b!=1)){
        printf("Voulez-vous affecter le concert à cette salle %s\n", tabRoom[i].nom);
        j=i;
        b = better_scan("1 pour oui \n2 pour non \n");
        i++;
    }
    if(b==1){
        tabRoom[j].state = 1;
        c.salle = tabRoom[j];
        strcpy(c.salle.nom, tabRoom[j].nom);
    }
    displayRoom(c.salle);
    printf("Voulez-vous changer la salle %s ?\n", c.salle.nom);
    printf("1 pour oui\n");
    printf("2 pour non\n");
    b = better_scan("");
    if(b==1){
        c.salle = modifRoom(c.salle);
        displayRoom(c.salle);
    }
    return c;
}

Salle* createTabRoom(int n){
    Salle* tabRoom = malloc(n*sizeof(Salle));
    verifpointer(tabRoom);
    return tabRoom;
}

Concert* createTabConcert(int n){
    Concert* tabConcert = malloc(n*sizeof(Concert));
    verifpointer(tabConcert);
    return tabConcert;
}

Salle* multiroomCreation(int numberRoom){
    Salle* S = createTabRoom(numberRoom);
    int i = 0;
    while(i<numberRoom){
        S[i] = constructRoom();
        i++;
    }
    return S;
}

Concert* MultiConcertCreation(int numberConcert, Salle* s){
    Concert* C = createTabConcert(numberConcert);
    int i = 0;
    while(i<numberConcert){
        C[i] = createConcert(s);
        i++;
    }
    return C; 
}

//Salle* AjoutDeSalle(Salle* tab){
    //int n = sizeof(tab);
    //tab = realloc(tab, sizeof(Salle)*(n+1));
    //tab[n] = ConstructSalle();
    //return tab;
//}

Salle category_aAndPit(Salle s, int n){
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

Salle modifRoom(Salle s){
    int b = 0;
    b=better_scan("\nVoulez vous changer le prix de la categorie A ?\n");
    if(b==1){
        s.prixa = better_scanFloat("Quel est le nouveau prix de la catégorie A ?\n");
    }
    b=0;
    b=better_scan("\nVoulez-vous changer le prix de la categorie B ?\n");
    if(b==1){
        s.prixb = better_scanFloat("Quel est le nouveau prix de la catégorie B ?\n");
    }
    b=0;
    b=better_scan("\nVoulez-vous changer le prix de la categorie C ?\n");
    if(b==1){
        s.prixc = better_scanFloat("Quel est le nouveau prix de la catégorie C ?\n");
    }
    b=0;
    b=better_scan("Voulez-vous une fosse ?\n1 pour oui\n2 pour non\n");
    category_aAndPit(s, b);
    b=0;
    return s;
}

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

void numberRoom(int* userCount, Utilisateur* tabFest){
    int numberRoom;
    couleur("31");
    printf("Vous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\n");
    couleur("37");
    numberRoom = better_scan("Combien de salles souhaitez-vous créer (10 maximum)?\n");
        switch(numberRoom){
        case 0:
            interfaceManager(userCount, tabFest);
            break;
        case 1:
            constructRoom();
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
            multiroomCreation(numberRoom);
            break;
        default:
            color("33");
            printf("Erreur de saisie\n");
            color("37");
            interfaceManager(userCount, tabFest);
            break;
    }
}

void interfaceManager (int* userCount, Utilisateur* tabFest){
    int choiceAction = better_scan("Bonjour Admin 👋\nQue souhaitez vous faire ?\n0 pour se déconnecter\n1 pour créer une/des salle\n2 pour créer un concert\n3 pour créer un festival\n4 pour obtenir un rapport sur un concert\n");
    switch(choiceAction){
        case 0:
            choiceUser(userCount, tabFest);
            break;
        case 1:
            numberRoom(userCount, tabFest);
            break;
        case 2:

            //createConcert(tabRoom);
            break;
        case 4:
            //calculateRatio(tabRoom);
        default:
            color("33");
            printf("Erreur de saisie\n");
            color("37");
            interfaceManager(userCount, tabFest);
            break;
    }
}
