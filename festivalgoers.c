#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "structures.h"
#include "color.h"
#include "smartrobusnest.h"
#include "hour.h"
#include "interface.h"

//User array openned with the backupfiles
Utilisateur* constrTabFestivalGoers(int* userCount) {
    Utilisateur* tabFest = malloc(sizeof(Utilisateur) * (*userCount));
    verifpointer(tabFest);
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
    color("33");
    printf("Cet identifiant n'existe pas\n");
    color("37");
    return -1;
}

int checkPasswordFest(Utilisateur* tabFest, int* userCount, char* passwordco) {
    for (int i = 0; i < (*userCount); i++) {
        if (strcmp(tabFest[i].password, passwordco) == 0) {
            printf("Mot de passe correct\n");
            return 1;
        }
    }
    color("33");
    printf("Erreur de saisie\n");
    color("37");
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
    verifpointer(newUser.password);
    strcpy(newUser.password, tempoPassword);
    generateUniqueId(tabFest, genId, userCount);
    newUser.id = *genId;
    tabFest = realloc(tabFest, sizeof(Utilisateur) * (*userCount + 1));
    verifpointer(tabFest);
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

/*
void reserveSeat(int inputConcert, int ){
  //Eventuellement intégrer la vérification de l'heure

  


}

void reservation(int id, Concert* tabConcert, Salle* tabRoom){
  char inputConcert[50];
  printf("Quel est le concert que vous souhaitez voir ?\n");
  fgets(inputConcert, sizeof(inputConcert), stdin);
  inputConcert[strcspn(inputConcert, '\n')]='\0';
  int concertFound=-1;
  for (int i = 0; i < 10; i++) {
    if (strcmp(tabConcert[i].guest, inputConcert) == 0) {
      concertFound = i;
      reserveSeat(inputConcert, );



  free(inputConcert);
}

/*
void my_reservation(Festival tab_concert, Utilisateur u) {
  //Demander quel concert il veut voir + vérifier si son id est dans la salle
  //+ rechercher dans le tableau de la salle l'id de l'utilisateur et afficher 
  //le numéro de son/ses siège(s) ou place dans la fosse + affichage 

  char buffer[50];
  printf("Enter the name of the concert you want to see:");
  fgets(buffer, 50, stdin);
  buffer[strcspn(buffer, "\n")] = '\0';

  int concert_found = 0;

  for (int i = 0; i < 10; i++) {
   if (strcmp(tab_concert.concert[i].guest, buffer) == 0) {
    concert_found = 1;
     affichesalle(tab_concert.concert[i].salle);
     //faut que je vérigie si j'ai bine tab.concert qui est dedans
       //euh d'abord rangé puis siège, on fait une boucle+, voir sur la feuille les étapes de morrt. C'est la bombe atomique là l'espagnole voir la fête totale
     int user_reservation = 0;
 printf("The program is checking reservation(s) for user %d in concert %s:\n", u.id, tab_concert.concert[i].guest);
  for (int row = 0; row < tab_concert.concert[i].salle.nb_range; row++) {
  for (int seat = 0; seat < tab_concert.concert[i].salle.nb_siege_range; seat++) {
  for (int j = 0; j < 2; j++) { 
    if (tab_concert.concert[i].salle.siege[row][seat].id[j].id == u.id) {
    printf("Row %d, Seat %d\n", row, seat);
    printf("Category: %d, Price: %d\n", tab_concert.concert[i].salle.siege[row][seat].categorie, tab_concert.concert[i].salle.siege[row][seat].prix);
 user_reservation = 1;
}
}
}
}
  if (!user_reservation) {
  printf("No reservations found for user %d in concert %s.\n", u.id, tab_concert.concert[i].guest);
}
 break;
}
}

  if (!concert_found) {
   printf("No concert found with the name %s\n", buffer);
}
}

void reserve_seats(Festival tab_concert) {
  // Demander quel concert il veut réserver + appel du tableau de la salle et l'afficher, demander à l'utilisateur la/ les sièges qu'il veut réserver + faire le débit avec le compte fictif bancaire et printf facture envoyé
  int concert_number = 0;
  int row_number = 0;
  int seat_number = 0;
  do {
  concert_number = better_scan("Enter the concert number you want to reserve: ");
  } while (concert_number < 0 || concert_number >= 10);

  affichesalle(tab_concert.concert[concert_number].salle);

  do {
   row_number = better_scan("Enter the row number you want: ");
  } while (row_number < 0 || row_number >tab_concert.concert[concert_number].salle.nb_range);

    
  do {
  seat_number = better_scan("Enter the seat number you want: ");
  } while (seat_number < 0 || seat_number > tab_concert.concert[concert_number].salle.nb_siege_range);


  if (tab_concert.concert[concert_number].salle.siege[row_number][seat_number].etat_siege == 1) {
  printf("Seat already reserved.\n");
    // On refait le fonction ? Plus simple je pense
  reserve_seats(tab_concert);
  } 
  else {
  tab_concert.concert[concert_number].salle.siege[row_number][seat_number].etat_siege = 1;
  printf("Seat %d in row %d for concert %d reserved successfully.\n", seat_number, row_number, concert_number);
  printf("Payment processed. Invoice sent to you.\n");// On peut enelever mais c'est sympa

}
}

*/

//Interface
void interfaceFestivalGoers(int id, int* userCount, Utilisateur* tabFest) {
    int choiceAction = better_scan("Bonjour 👋\nQue souhaitez vous faire ?\n0 pour se déconnecter\n1 pour voir vos réservations\n2 pour réserver un concert\n");
    switch (choiceAction){
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
        color("33");
        printf("Erreur de saisie\n");
        color("37");
        interfaceFestivalGoers(id, userCount, tabFest);
        break;
    }
}