#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "structures.h"
#include "smartrobusnest.h"
#include "interface.h"

//User array openned with the backupfiles
Utilisateur* constrTabFestivalGoers(int* userCount) {
    Utilisateur* tabFest = malloc(sizeof(Utilisateur) * (*userCount));
    verifmalloc(tabFest);
    return tabFest;
}

//Connection required
//*/
int checkIdFest(Utilisateur* tabFest, int* userCount, int idco) {
    for (int i = 0; i < (*userCount); i++) {
        if (tabFest[i].id == idco) {
            printf("Identifiant correct\n");
            return 1;
        }
    }
    printf("Cet identifiant n'existe pas\n");
    return -1;
}

int checkPasswordFest(Utilisateur* tabFest, int* userCount, char* passwordco) {
    for (int i = 0; i < (*userCount); i++) {
        if (strcmp(tabFest[i].password, passwordco) == 0) {
            printf("Mot de passe correct\n");
            return 1;
        }
    }
    printf("Erreur de saisie\n");
    return -1;
}
//*/

void generateUniqueId(Utilisateur* tabFest, int* genId, int* userCount) {
    bool unique;
    do {
        unique = true;
        *genId = rand()%90001+1000; // Generate ID between 1000 and 100000
        for (int i = 0; i < (*userCount); i++) { // Check if it is already used
            if (tabFest[i].id == *genId) {
                unique = false;
                break;
            }
        }
    } while (!unique); // generate id until it is unique
}

void accountCreationFestivalGoers(int* userCount, Utilisateur* tabFest){
    char tempoPassword[30];
    int id=-1;
    int* genId=&id;
    Utilisateur newUser;
    printf("Saisir votre mot de passe (30 caractères maximum)\n");
    fgets(tempoPassword, sizeof(tempoPassword), stdin);
    tempoPassword[strcspn(tempoPassword, "\n")] = '\0';
    newUser.password= malloc(strlen(tempoPassword) + 1);
    verifmalloc(newUser.password);
    strcpy(newUser.password, tempoPassword);
    generateUniqueId(tabFest, genId, userCount);
    newUser.id = *genId;
    tabFest[(*userCount)]=newUser;
    (*userCount)++;
    printf("Votre identifiant est %d\n", newUser.id);
    printf("Votre mot de passe est %s\n", newUser.password);
    printf("Votre compte est créé, notez bien vos identifiants, ils vous permettent de vous connectez et d'accéder à vos réservations\n");
    choiceUser (userCount, tabFest);
}

//Display if the manager wants to see the differents ID and passwords
void displayUsers(Utilisateur* tabFest, int* userCount) {
    printf("Liste des festivaliers:\n");
    for (int i=0; i<(*userCount); i++) {
        printf("Festivaliers %d:\n", i + 1);
        printf("  ID: %d\n", tabFest[i].id);
        printf("  Mot de passe: %s\n\n", tabFest[i].password);
    }
}

//Interface
void interfaceFestivalGoers(int id, int* userCount, Utilisateur* tabFest){
    int choiceAction = better_scan("Bonjour 👋\nQue souhaitez vous faire ?\n0 pour se déconnecter\n1 pour voir vos réservations\n2 pour réserver un concert\n");
    switch (choiceAction) {
    case 0:
        choiceUser(userCount, tabFest);
        break;
    case 1:
        //myReservations();
        break;
    case 3:
        //reservation();
        break;
    default:
        printf("Erreur de saisie\n");
        interfaceFestivalGoers(id, userCount, tabFest);
        break;
    }
}

    /*
    for (int i = 0; i < userCount; i++) {
        free(users[i].id);
        free(users[i].password);
    }
    free(users);
    //*/



