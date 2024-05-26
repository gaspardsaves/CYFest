#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "structures.h"
#include "color.h"
#include "smartrobusnest.h"
#include "manager.h"
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
// Go through the list of users to check if id is already used
    for (int i = 0; i < (*userCount); i++) {
        
        // Check if the password is not NULL and if the user is matches the id of connection
        if (tabFest[i].password != NULL && tabFest[i].id == idco) {
            printf("Identifiant correct\n");
            return 1;
        }
    }
     // If the id is not found, display the error message down below
    color("33");
    printf("Cet identifiant n'existe pas\n");
    color("37");
    return -1;
}


int checkPasswordFest(Utilisateur* tabFest, int* userCount, char* passwordco, int idco) {
    // Go through the list of users to check if the id of connection and password are matching
    for (int i = 0; i < (*userCount); i++) {
        
        // Check if the password is not NULL, the user id matches, and the password matches with user's password
        if (tabFest[i].password != NULL && tabFest[i].id == idco && strcmp(tabFest[i].password, passwordco) == 0) {
            printf("Mot de passe correct\n");
            return 1;
        }
    }
  // If the id and password are not matching, display the error message down below
    color("33");
    printf("Erreur de saisie\n");
    color("37");
    return -1;
}
//*/

// Generate an id, if it is used then generate another id and verify if it is used
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
    } while (!unique); // Generate id until it is unique
}


// Festival-goer enter a password and the program give an id to him
void accountCreationFestivalGoers(int* userCount, Utilisateur** tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert){
    char tempoPassword[30];
    int id=-1;
    int* genId=&id;
    Utilisateur newUser;
    
    printf("Saisir votre mot de passe (30 caractères maximum)\n");
    fgets(tempoPassword, sizeof(tempoPassword), stdin); // Read the password entered from the user, making sure it does not exceed the buffer size
    tempoPassword[strcspn(tempoPassword, "\n")] = '\0'; // Remove the newline character from the end of the input
    newUser.password= malloc(strlen(tempoPassword) + 1); // Allocate memory for the password in the newUser structure
    verifpointer(newUser.password); // Verify if pointer is correct
    strcpy(newUser.password, tempoPassword); // Copy the temporary password in the allocated memory for newUser's password
    
    generateUniqueId(*tabFest, genId, userCount); // Generate an id with the function
    newUser.id = *genId;
    *tabFest = realloc(*tabFest, sizeof(Utilisateur) * (*userCount+1));
    verifpointer(*tabFest);
    
    (*tabFest)[(*userCount)]=newUser; // It adds the user's details to a table of all users 
    (*userCount)++; // Go to the next square in the table 
    printf("Votre identifiant est %d\n", newUser.id);
    printf("Votre mot de passe est %s\n", newUser.password);
    printf("Votre compte est créé, notez bien vos identifiants, ils vous permettent de vous connectez et d'accéder à vos réservations\n");
    choiceUser (userCount, *tabFest, roomCount, tabRoom, concertCount, tabConcert);
}

// Display if the manager wants to see the differents id and passwords
void displayUsers(Utilisateur* tabFest, int* userCount) {
    printf("Liste des festivaliers:\n");
    for (int i=0; i<(*userCount); i++) {
        printf("Festivaliers %d:\n", i + 1);
        printf("  ID: %d\n", tabFest[i].id);
        printf("  Mot de passe: %s\n\n", tabFest[i].password);
    }
}

//*
void reserveSeat(int concertFound, int id, int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert){
  //Eventuellement intégrer la vérification de l'heure
  int rowNumber = 0;
  int seatNumber = 0;
  // Display the seating arrangement of the concert
  displayRoom(tabConcert[concertFound].salle);
  // The user enter the row number of the seat he wish to reserve
  do {
    rowNumber = better_scan("Entrez la rangée du siège que vous souhaitez réserver\n");
    rowNumber--;
  } while (rowNumber < 0 || rowNumber > tabConcert[concertFound].salle.nb_range);
  // The user to enter the seat number he wish to reserve
  do {
    seatNumber = better_scan("Entrez le numéro du siège que vous souhaitez réserver\n");
    seatNumber--;
  } while (seatNumber < 0 || seatNumber > tabConcert[concertFound].salle.nb_siege_range);
  // Checking if the seat is already reserved
  if (tabConcert[concertFound].salle.siege[rowNumber][seatNumber].etat_siege == 1) {
    color("33");
    printf("Ce siège est déjà réservé\n");
    color("37");
    reserveSeat(concertFound, id, userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);// Call the function to reserve another seat
  }
  else {
    tabConcert[concertFound].salle.siege[rowNumber][seatNumber].etat_siege=1;
    tabConcert[concertFound].salle.siege[rowNumber][seatNumber].id[1]=1;
    //Add resa à tab resa en récupérant l'adresse du siège
    printf("Siège %d de la colonne %d du concert %s reservé avec succès\n", seatNumber, rowNumber, tabConcert[concertFound].guest);
    //printf("Paiement effectué, billets envoyés.\n");
  }
  interfaceFestivalGoers(id, userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
}

void reservation(int id, int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert){
  char inputConcert[50];
  printf("Voici la liste des concerts :\n");
  for(int j=0; j<(*concertCount); j++){
      printf("%s\n", tabConcert[j].guest);
  }
  printf("Saisir le nom du concert que vous souhaitez voir\n");
  // The user to enter the name of the concert he wish to see
  fgets(inputConcert, sizeof(inputConcert), stdin);
  inputConcert[strcspn(inputConcert, "\n")]='\0'; // Remove the newline character from the input
  int concertFound=-1;
  // Looking for the concert in the list of concerts
  for (int i = 0; i < (*concertCount); i++) {
    if (strcmp(tabConcert[i].guest, inputConcert) == 0) { // Compare input with concert names
      concertFound = i;
      reserveSeat(concertFound, id, userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
    }
  }
  color("33");
  printf("Erreur de saisie, salle introuvable\n");
  color("37");
  interfaceFestivalGoers(id, userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
}

/*
void myReservation () {
  char buffer[50];
  
}
//*/

/*
void my_reservation(Festival tab_concert, Utilisateur u) {
  //Demander quel concert il veut voir + vérifier si son id est dans la salle
  //+ rechercher dans le tableau de la salle l'id de l'utilisateur et afficher 
  //le numéro de son/ses siège(s) ou place dans la fosse + affichage 

  char buffer[50];
  printf("Enter the name of the concert you want to see:");
  fgets(buffer, 50, stdin);
  buffer[strcspn(buffer, "\n")] = '\0';  // Remove the newline character from the input

  int concert_found = 0;

  for (int i = 0; i < 10; i++) { // Go through the list of concerts to find the concert
   if (strcmp(tab_concert.concert[i].guest, buffer) == 0) { // Compare the input with concert names
    concert_found = 1;
     affichesalle(tab_concert.concert[i].salle); 


int user_reservation = 0;
printf("The program is checking reservation(s) for user %d in concert %s:\n", u.id, tab_concert.concert[i].guest);
 
 // Check each seat in the concert's seating arrangement for the user's reservation
  for (int row = 0; row < tab_concert.concert[i].salle.nb_range; row++) {
  for (int seat = 0; seat < tab_concert.concert[i].salle.nb_siege_range; seat++) {
  for (int j = 0; j < 2; j++) { // Display the seating arrangement of the concert
    if (tab_concert.concert[i].salle.siege[row][seat].id[j].id == u.id) { // If the user id matches, display the seat detail
    printf("Row %d, Seat %d\n", row, seat);
    printf("Category: %d, Price: %d\n", tab_concert.concert[i].salle.siege[row][seat].categorie, tab_concert.concert[i].salle.siege[row][seat].prix);
 user_reservation = 1;
}
}
}
}
// If no reservation is found for the user, print the message down below
  if (!user_reservation) {
  printf("No reservations found for user %d in concert %s.\n", u.id, tab_concert.concert[i].guest);
}
 break; // End the loop as the concert has been found
}
}
  // If the concert is not found, print the message down below
  if (!concert_found) {
   printf("No concert found with the name %s\n", buffer);
}
}
*/

//Interface
void interfaceFestivalGoers(int idco, int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert) {
    color("35");
    printf("\nBonjour 👋\n");
    color("37");
    int choiceAction = better_scan("Que souhaitez vous faire ?\n0 pour se déconnecter\n1 pour voir vos réservations\n2 pour réserver un concert\n");
    // Handle the user's choice 
    switch (choiceAction){
      case 0:
        // If the user chooses 0, call the choiceUser function to handle user choices
        choiceUser(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
        break;
      case 1:
        // If the user chooses 1, handle viewing reservations
        //myReservations();
        break;
      case 2:
        // If the user chooses 2, handle booking a concert
        reservation(idco, userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
        break;
      default:
        // If the user enters an invalid choice, display the error message down below
        color("33");
        printf("Erreur de saisie\n");
        color("37");
        // Call the function to allow the user to make another choice
        interfaceFestivalGoers(idco, userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
        break;
    }
}
