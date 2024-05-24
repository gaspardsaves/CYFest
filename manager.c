#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color.h"
#include "structures.h"
#include "interface.h"
#include "manager.h"
#include "smartrobusnest.h"

Salle* createTabRoom(int* roomCount){
    Salle* tabRoom = malloc((*roomCount)*sizeof(Salle));
    verifpointer(tabRoom);
    return tabRoom;
}

Concert* createTabConcert(int* concertCount){
    Concert* tabConcert = malloc((*concertCount)*sizeof(Concert));
    verifpointer(tabConcert);
    return tabConcert;
}

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

void displaySiege(char* clr, Siege s){
    color(clr);
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
    color("0");
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

void constructRoom(int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert){
    Salle newRoom;
    int i = 0;
    int j = 0;
    char tempoNom[50];
    printf("Quel est le nom de la salle ?\n");
    fgets(tempoNom, sizeof(tempoNom), stdin);
    tempoNom[strcspn(tempoNom, "\n")]='\0';
    newRoom.nom=malloc(strlen(tempoNom)+1);
    verifpointer(newRoom.nom);
    strcpy(newRoom.nom, tempoNom);
    newRoom.nb_range=better_scan("Choississez le nombre de rangées\n");
    while(newRoom.nb_range<1){
        newRoom.nb_range=better_scan("Mauvaise saisie, recommencez\n");
    }
    newRoom.nb_siege_range=better_scan("Choississez le nombre de sieges par rangées\n");
    while(newRoom.nb_siege_range<1){
        newRoom.nb_siege_range=better_scan("Mauvaise saisie, recommencez\n");
    }
    newRoom.arange=better_scan("Combien de rangées en catégorie A\n");
    while((newRoom.arange<0)&&(newRoom.arange>newRoom.nb_range)){
        newRoom.arange=better_scan("Mauvaise saisie, recommencez\n");
    }
    newRoom.prixa=better_scanFloat("Donnez le prix de la catégorie A\n");
    while(newRoom.prixa<0){
        newRoom.prixa=better_scanFloat("Mauvaise saisie, recommencez\n");
    }
    newRoom.brange=better_scan("Combien de rangées en catégorie B\n");
    while((newRoom.brange<0)||((newRoom.arange+newRoom.brange)>newRoom.nb_range)){
        newRoom.brange=better_scan("Mauvaise saisie, recommencez\n");
    }
    newRoom.prixb=better_scanFloat("Donnez le prix de la catégorie B\n");
    while(newRoom.prixb<0){
        newRoom.prixb=better_scanFloat("Mauvaise saisie, recommencez\n");
    }
    newRoom.prixc=better_scanFloat("Donnez le prix de la catégorie C\n");
    while(newRoom.prixc<0){
        newRoom.prixc=better_scanFloat("Mauvaise saisie, recommencez\n");
    }
    int a = newRoom.arange;
    int b = newRoom.brange;
    newRoom.siege = malloc(newRoom.nb_range*sizeof(Siege));
    verifpointer(newRoom.siege);
    while(i<newRoom.nb_range){
        newRoom.siege[i] = malloc(newRoom.nb_siege_range*sizeof(Siege));
        verifpointer(newRoom.siege[i]);
        while(j<newRoom.nb_siege_range){
            if(a>0){
                newRoom.siege[i][j] = constructSiege(1, newRoom.prixa, 0);
            }
            else if(b>0){
                newRoom.siege[i][j] = constructSiege(2, newRoom.prixb, 0);
            }
            else{
                newRoom.siege[i][j] = constructSiege(3, newRoom.prixc, 0);
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
    tabRoom=realloc(tabRoom, sizeof(Salle)*(*roomCount +1));
    verifpointer(tabRoom);
    tabRoom[(*roomCount)]=newRoom;
    (*roomCount)++;
    interfaceManager(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
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
                displaySiege("31", S.siege[i][j]);
            }
        j++;
        }
    printf("\n");
    j=0;
    i++;
    }
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

//*
void createConcert(int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert){
    Concert newConcert;
    char tempoGuest[50];
    printf("Quel est le nom de et le prénom de l'artiste ?\n");
    fgets(tempoGuest, sizeof(tempoGuest), stdin);
    tempoGuest[strcspn(tempoGuest, "\n")]='\0';
    newConcert.guest=malloc(strlen(tempoGuest)+1);
    verifpointer(newConcert.guest);
    strcpy(newConcert.guest, tempoGuest);
    printf("Saississez les éléments demandés sur la date et l'heure de début du concert\n");
    newConcert.horaired = getDate();
    printf("Saississez les éléments demandés sur la date et l'heure de fin du concert\n");
    newConcert.horaired = getDate();
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
        newConcert.salle = tabRoom[j];
        strcpy(newConcert.salle.nom, tabRoom[j].nom);
    }
    displayRoom(newConcert.salle);
    printf("Voulez-vous changer la salle %s ?\n", newConcert.salle.nom);
    printf("1 pour oui\n");
    printf("2 pour non\n");
    b = better_scan("");
    if(b==1){
        newConcert.salle = modifRoom(newConcert.salle);
        displayRoom(newConcert.salle);
    }
    tabConcert=realloc(tabConcert, sizeof(Concert)*(*concertCount +1));
    verifpointer(tabConcert);
    tabConcert[(*concertCount)]=newConcert;
    (*concertCount)++;
    interfaceManager(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
}
//*/


void multiConcertCreation(int numberConcert, int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert){
    for(int i=0; i<numberConcert; i++){
        createConcert(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
    }
}

void multiRoomCreation(int numberRoom, int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert){
    for(int i=0; i<numberRoom; i++){
        createConcert(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
    }
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
void numberConcert(int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert){
    int numberConcert;
    color("31");
    printf("Vous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\n");
    color("37");
    numberConcert = better_scan("Combien de concerts souhaitez-vous créer (10 maximum)?\n");
        switch(numberConcert){
        case 0:
            interfaceManager(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        case 1:
            createConcert(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
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
            multiConcertCreation(numberConcert, userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        default:
            color("33");
            printf("Erreur de saisie\n");
            color("37");
            interfaceManager(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
    }
}

void numberRoom(int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert){
    int numberRoom;
    color("31");
    printf("Vous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\n");
    color("37");
    numberRoom = better_scan("Combien de salles souhaitez-vous créer (10 maximum)?\n");
        switch(numberRoom){
        case 0:
            interfaceManager(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        case 1:
            constructRoom(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
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
            multiRoomCreation(numberRoom, userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        default:
            color("33");
            printf("Erreur de saisie\n");
            color("37");
            interfaceManager(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
    }
}

void interfaceManager (int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert){
    int choiceAction = better_scan("Bonjour Admin 👋\nQue souhaitez vous faire ?\n0 pour se déconnecter\n1 pour créer une/des salle(s)\n2 pour créer un/des concert(s)\n3 pour obtenir un rapport sur un concert\n");
    switch(choiceAction){
        case 0:
            choiceUser(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        case 1:
            numberRoom(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        case 2:
            numberConcert(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        case 4:
            //calculateRatio(tabRoom);
        default:
            color("33");
            printf("Erreur de saisie\n");
            color("37");
            interfaceManager(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
    }
}
