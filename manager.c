#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color.h"
#include "structures.h"
#include "interface.h"
#include "manager.h"
#include "smartrobusnest.h"

// Function to create an array of rooms
Salle* createTabRoom(int* roomCount){
    // Allocate memory for the array of rooms
    Salle* tabRoom = malloc((*roomCount+1)*sizeof(Salle));
    // Verify that the memory allocation was successful
    verifpointer(tabRoom);
    return tabRoom;
}

Concert* createTabConcert(int* concertCount){
    // Allocate memory for the array of concerts
    Concert* tabConcert = malloc((*concertCount+1)*sizeof(Concert));
    // Verify that the memory allocation was successful
    verifpointer(tabConcert);
    return tabConcert;
}

Siege constructSiege(int cat, int price, int f){
    Siege s;
    // Initialize seat state to 0 (available)
    s.etat_siege = 0;
    // Set the seat category
    s.categorie = cat;
    // Set the seat price
    s.prix = price;
    // Set whether the seat is in the pit
    s.fosse = f;

    return s;
}

Salle ResetScene(Salle s){
    int i = 0;
    int j = 0;
    // Loop through all rows
    while(i<s.nb_range){
        // Loop through all seats in a row
        while(j<s.nb_siege_range){
            // Reset seat state and number of people
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
    color(clr); // Set the color
    if((s.categorie==1)&&(s.fosse==1)){
        if(!s.etat_siege){
            printf("oo\t"); // Display empty seat in pit
        }
        else if (s.nombre_personne==1){
            printf("xo\t"); // Display seat with one person in pit
        }
        else if((s.nombre_personne==2)||(s.etat_siege)){
            printf("xx\t"); // Display occupied seat in pit
        }
    }
    else if (s.etat_siege){
        printf("X\t"); // Display occupied seat
    }
    else if(!(s.etat_siege)){
        printf("O\t"); // Display empty seat
    }
    color("0"); // Reset color
}

Salle FreeTheSceneAfterConcert(Salle s){
    int i = 0;
    int j = 0;
    // Loop through all rows
    while(i<s.nb_range){
        // Loop through all seats in a row
        while(j<s.nb_siege_range){
            if(s.siege[i][j].etat_siege==1){
                // Reset seat state to available
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
    // Get the year from the user and validate it
    d.year=better_scan("L'année\n");
    while(d.year<2024){
        d.year=better_scan("Mauvaise saisie, recommencez\n");
    }
    // Get the month from the user and validate it
    d.month=better_scan("Le mois\n");
    while((d.month<1)||(d.month>12)){
        d.month=better_scan("Mauvaise saisie, recommencez\n");
    }
    // Get the day from the user and validate it
    d.day=better_scan("Le jour\n");
    while((d.day<1)||(d.day>30)){
        d.day=better_scan("Mauvaise saisie, recommencez\n");
    }
    // Get the hour from the user and validate it
    d.hour=better_scan("L'heure\n");
    while((d.hour<0)||(d.hour>23)){
        d.hour=better_scan("Mauvaise saisie, recommencez\n");
    }
    // Get the minut from the user and validate it
    d.minut=better_scan("La minute\n");
    while((d.minut<0)||(d.minut>59)){
        d.minut=better_scan("Mauvaise saisie, recommencez\n");
    }
    return d;
}

void constructRoom(int* userCount, Utilisateur* tabFest, int* roomCount, Salle** tabRoom, int* concertCount, Concert* tabConcert){
    Salle newRoom;
    int i = 0;
    int j = 0;
    char tempoNom[50];
    // Get the name of the room
    printf("Quel est le nom de la salle ?\n");
    fgets(tempoNom, sizeof(tempoNom), stdin);
    tempoNom[strcspn(tempoNom, "\n")]='\0';
    // Allocate memory for the room name and copy it
    newRoom.nom=malloc(strlen(tempoNom)+1);
    verifpointer(newRoom.nom);
    strcpy(newRoom.nom, tempoNom);
    // Get the number of rows in the room
    newRoom.nb_range=better_scan("Choississez le nombre de rangées\n");
    while(newRoom.nb_range<1){
        newRoom.nb_range=better_scan("Mauvaise saisie, recommencez\n");
    }
    // Get the number of seats per row
    newRoom.nb_siege_range=better_scan("Choississez le nombre de sieges par rangées\n");
    while(newRoom.nb_siege_range<1){
        newRoom.nb_siege_range=better_scan("Mauvaise saisie, recommencez\n");
    }
    // Get the number of rows in category A
    newRoom.arange=better_scan("Combien de rangées en catégorie A\n");
    while((newRoom.arange<0)&&(newRoom.arange>newRoom.nb_range)){
        newRoom.arange=better_scan("Mauvaise saisie, recommencez\n");
    }
    // Get the price for category A
    newRoom.prixa=better_scanFloat("Donnez le prix de la catégorie A\n");
    while(newRoom.prixa<0){
        newRoom.prixa=better_scanFloat("Mauvaise saisie, recommencez\n");
    }
    // Get the number of rows in category B
    newRoom.brange=better_scan("Combien de rangées en catégorie B\n");
    while((newRoom.brange<0)||((newRoom.arange+newRoom.brange)>newRoom.nb_range)){
        newRoom.brange=better_scan("Mauvaise saisie, recommencez\n");
    }
    // Get the price for category B
    newRoom.prixb=better_scanFloat("Donnez le prix de la catégorie B\n");
    while(newRoom.prixb<0){
        newRoom.prixb=better_scanFloat("Mauvaise saisie, recommencez\n");
    }
    // Get the price for category C
    newRoom.prixc=better_scanFloat("Donnez le prix de la catégorie C\n");
    while(newRoom.prixc<0){
        newRoom.prixc=better_scanFloat("Mauvaise saisie, recommencez\n");
    }
    int a = newRoom.arange;
    int b = newRoom.brange;
    // Allocate memory for the seats
    newRoom.siege = malloc(newRoom.nb_range*sizeof(Siege));
    verifpointer(newRoom.siege);
    // Initialize each seat in the room
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
    (*tabRoom)=realloc((*tabRoom), sizeof(Salle)*(*roomCount +1));
    verifpointer(*tabRoom);
    // Add the new room to the array of rooms
    (*tabRoom)[(*roomCount)]=newRoom;
    (*roomCount)++;
}

// Function to display a room
void displayRoom(Salle S){
    int i = 0;
    int j = 0;
     // Loop through each row in the room
    while(i<S.nb_range){
        // Loop through each seat in the row
        while(j<S.nb_siege_range){
            // If the seat is not occupied
            if (!S.siege[i][j].etat_siege){
                // Display the seat based on its category
                switch (S.siege[i][j].categorie){
                    case 1 :
                        displaySiege("32", S.siege[i][j]); // Category 1 seat with color green
                        break;
                    case 2 :
                        displaySiege("33", S.siege[i][j]); // Category 2 seat with color orange
                        break;
                    case 3:
                        displaySiege("37", S.siege[i][j]); // Category 3 seat with color white
                        break;
                    default:
                        break;
                }
            }
            else{
                // Display the occupied seat with color red
                displaySiege("31", S.siege[i][j]);
            }
        j++;
        }
    // Print a newline after each row
    printf("\n");
    j=0;
    i++;
    }
}

// Function to modify room details
Salle modifRoom(Salle s){
    int b = 0;
    // Prompt to change the price of category A
    b=better_scan("\nVoulez-vous changer le prix de la categorie A ?\n1 pour oui\n2 pour non\n");
    if(b==1){
        s.prixa = better_scanFloat("Quel est le nouveau prix de la catégorie A ?\n");
    }
    b=0;
    // Prompt to change the price of category B
    b=better_scan("\nVoulez-vous changer le prix de la categorie B ?\n1 pour oui\n2 pour non\n");
    if(b==1){
        s.prixb = better_scanFloat("Quel est le nouveau prix de la catégorie B ?\n");
    }
    b=0;
    // Prompt to change the price of category C
    b=better_scan("\nVoulez-vous changer le prix de la categorie C ?\n1 pour oui\n2 pour non\n");
    if(b==1){
        s.prixc = better_scanFloat("Quel est le nouveau prix de la catégorie C ?\n");
    }
    b=0;
    // Prompt to decide if there should be a pit
    b=better_scan("Voulez-vous une fosse ?\n1 pour oui\n2 pour non\n");
    category_aAndPit(s, b); // Call function to handle category A and pit
    b=0;
    return s; // Return the modified room
}

//*
// Function to create a concert
void createConcert(int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert** tabConcert){
    Concert newConcert;
    char tempoGuest[50];
    // Prompt for the artist's name and surname
    printf("Quel est le nom de et le prénom de l'artiste ?\n");
    fgets(tempoGuest, sizeof(tempoGuest), stdin);
    tempoGuest[strcspn(tempoGuest, "\n")]='\0';
    // Allocate memory for the guest name and copy the name
    newConcert.guest=malloc(strlen(tempoGuest)+1);
    verifpointer(newConcert.guest);
    strcpy(newConcert.guest, tempoGuest);
    // Prompt for the start date and time of the concert
    printf("Saississez les éléments demandés sur la date et l'heure de début du concert\n");
    newConcert.horaired = getDate();
    // Prompt for the end date and time of the concert
    printf("Saississez les éléments demandés sur la date et l'heure de fin du concert\n");
    newConcert.horairef = getDate();
    int i = 0;
    int b = 0;
    int j = 0;
    // Iterate through the rooms to select one for the concert
    while((i<*roomCount)&&(b!=1)){
        printf("Voulez-vous affecter le concert à cette salle : %s\n", tabRoom[i].nom);
        j=i;
        b = better_scan("1 pour oui \n2 pour non \n");
        i++;
    }
    // If a room is selected, assign it to the concert
    if(b==1){
        tabRoom[j].state = 1;
        newConcert.salle = tabRoom[j];
        //strcpy(newConcert.salle.nom, tabRoom[j].nom);
    }
    else {
        // If no room is selected, prompt to restart the concert creation
        printf("Aucune salle sélectionnée pour le concert.\n");
        color("33");
        printf("Veuillez recommencez la création du concert\n");
        color("37");
        return;
    }
    // Display the selected room
    displayRoom(newConcert.salle);
    // Prompt to modify the selected room
    printf("Voulez-vous modifier la salle %s ?\n", newConcert.salle.nom);
    printf("1 pour oui\n");
    printf("2 pour non\n");
    b = better_scan("");
    // If yes, modify the room and display it again
    if(b==1){
        newConcert.salle = modifRoom(newConcert.salle);
        displayRoom(newConcert.salle);
    }
    // Allocate more memory for the concert array and add the new concert
    (*tabConcert)=realloc((*tabConcert), sizeof(Concert)*(*concertCount +1));
    verifpointer(*tabConcert);
    (*tabConcert)[(*concertCount)]=newConcert;
    (*concertCount)++;
}
//*/

// Function to create multiple concerts
void multiConcertCreation(int numberConcert, int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert** tabConcert){
    for(int i=0; i<numberConcert; i++){
        // Call the createConcert function to create a new concert
        createConcert(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
    }
    // Call the interface manager to handle the next steps
    interfaceManager(userCount, tabFest, roomCount, tabRoom, concertCount, *tabConcert);
}

// Function to create multiple rooms
void multiRoomCreation(int numberRoom, int* userCount, Utilisateur* tabFest, int* roomCount, Salle** tabRoom, int* concertCount, Concert* tabConcert){
    for(int i=0; i<numberRoom; i++){
        // Call the constructRoom function to create a new room
        constructRoom(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
    }
    // Call the interface manager to handle the next steps
    interfaceManager(userCount, tabFest, roomCount, *tabRoom, concertCount, tabConcert);
}

//Salle* AjoutDeSalle(Salle* tab){
    //int n = sizeof(tab);
    //tab = realloc(tab, sizeof(Salle)*(n+1));
    //tab[n] = ConstructSalle();
    //return tab;
//}

// Function to set the pit status for category A seats in a room
Salle category_aAndPit(Salle s, int n){
    int i = 0;
    int j = 0;
    // Function to set the pit status for category A seats in a room
    while(i<s.arange){
        // Loop through each seat in the row
        while(j<s.nb_siege_range){
            s.siege[i][j].fosse= n;// Set the pit status for the seat
            j++;
        }
        j=0;
        i++;
    }
    return s;// Return the updated room
}


// Function to calculate and display the seat occupancy ratio in a room
void RatioSeat(Salle s){
    int i = 0;
    int j = 0;
    int Reservation = 0;
    // Loop through each row in the room
    while(i<s.nb_range){
        // Loop through each seat in the row
        while(j<s.nb_siege_range){
            if(s.siege[i][j].etat_siege==1){
                Reservation= Reservation + 1; // Count the number of reserved seats
            }
            j++;
        }
        j=0;
        i++;
    }
    double n = s.nb_range*s.nb_siege_range; // Total number of seats
    printf("\n%f pourcent(s) des sièges sont occupés dans cette salle\n", (Reservation/n)*100);
}

// Function to calculate and display the potential sales revenue for a concert in a room
void SalesRevenue(Salle s){
    int i = 0;
    int j = 0;
    float salesRevenue = 0;
    // Loop through each row in the room
    while(i<s.nb_range){
        // Loop through each seat in the row
        while(j<s.nb_siege_range){
            if(s.siege[i][j].etat_siege==1){
                salesRevenue = salesRevenue + s.siege[i][j].prix; // Sum up the prices of reserved seats
            }
            j++;
        }
        j=0;
        i++;
    }
    printf("Le chiffre d'affaire potentiel sur ce concert est %f\n", salesRevenue); // Display the potential sales revenue
}


void numberConcert(int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert){
    int numberConcert;
    color("31");// Set color to red
    printf("Vous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\n");
    color("37");// Set color to white
    numberConcert = better_scan("Combien de concerts souhaitez-vous créer (10 maximum)?\n");
    // Switch case to handle the user input
        switch(numberConcert){
        case 0:
            // Return to the interface manager
            interfaceManager(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            // Create the specified number of concerts
            multiConcertCreation(numberConcert, userCount, tabFest, roomCount, tabRoom, concertCount, &tabConcert);
            break;
        default:
            // Handle invalid input
            color("33");// Set color to yellow
            printf("Erreur de saisie\n");
            color("37");// Set color to white
            // Return to the interface manager
            interfaceManager(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        }
}

void numberRoom(int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert){
    int numberRoom;
    color("31"); // Set color to red
    printf("Vous pouvez revenir en arrière à chaque étape ou interrompre le programme en saisissant 0\n");
    color("37"); // Set color to white
    numberRoom = better_scan("Combien de salles souhaitez-vous créer (10 maximum)?\n");
    // Switch case to handle the user input
    switch(numberRoom){
        case 0:
             // Return to the interface manager
            interfaceManager(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            // Create the specified number of rooms
            multiRoomCreation(numberRoom, userCount, tabFest, roomCount, &tabRoom, concertCount, tabConcert);
            break;
        default:
            // Handle invalid input
            color("33");// Set color to yellow
            printf("Erreur de saisie\n");
            color("37");// Set color to white
            interfaceManager(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
    }
}

// Function to manage the interface
void interfaceManager (int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert){
    int choiceAction = better_scan("Bonjour Admin 👋\nQue souhaitez vous faire ?\n0 pour se déconnecter\n1 pour créer une/des salle(s)\n2 pour créer un/des concert(s)\n3 pour obtenir un rapport sur un concert\n");
     // Switch case to handle the user choice
    switch(choiceAction){
        case 0:
            // Log out
            choiceUser(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        case 1:
            // Create rooms
            numberRoom(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        case 2:
            // Create concerts
            numberConcert(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
        case 3:
            // Get a report on a concert (functionality not implemented)
            //reportOnRoom(tabRoom);
        default:
            // Handle invalid input
            color("33"); // Set color to yellow
            printf("Erreur de saisie\n");
            color("37"); // Set color to white
            interfaceManager(userCount, tabFest, roomCount, tabRoom, concertCount, tabConcert);
            break;
    }
}
