#include <stdio.h>
#include <stdlib.h>
#include <manager.h>
#include <string.h> 




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

}


  

void my_reservation(Festival tab_concert, Utilisateur u) {
  /*Demander quel conceret il veut voir + vérifier si son id est dans la salle + rechercher dans le tableau de la salle l'id de l'utilisateur et afficher le numéro de son/ses siège(s) ou place dans la fosse + affichage 
   */
  char buffer[50];
  printf("Enter the name of the concert you want to see: ");
  fgets(buffer, 50, stdin);
  buffer[strcspn(buffer, "\n")] = '\0';

  int concert_found = 0;

  for (int i = 0; i < 10; i++) {
   if (strcmp(tab_concert.concert[i].guest, buffer) == 0) {
    concert_found = 1;
     affichesalle(tab_concert.concert[i].salle);
     /* faut que je vérigie si j'ai bine tab.concert qui est dedans
       euh d'abord rangé puis siège, on fait une boucle+, voir sur la feuille les étapes de morrt. C'est la bombe atomique là l'espagnole voir la fête totale
         */
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




void action_type(Festival tab_concert){
int question;

  do{
  question=better_scan("0-my reservation or 1-reserve seats");
  }
  while(question!=1&&question!=0);


switch (question){

  case 0: my_reservation(tab_concert,);
    break;

  case 1: reserve_seats(tab_concert);
    break;

  default:
    break;
} 
}





  int main(){
    // Bon faut fait venir le tab_concert d'un autre programme crée et qui contient le taleau concert
Festival tab_concert; 

action_type(tab_concert);

// est-ce qu'on débite le montant de la place avec un compte bancaire fictif avec une fonction card_ticket

  // free buffer
    return 0;
  }
