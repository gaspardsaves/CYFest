#ifndef FESTIVALGOERS_H
    #define FESTIVALGOERS_H
    #include <stdbool.h>
    #include "structures.h"
    #include "smartrobusnest.h"

    Utilisateur* constrTabFestivalGoers(int* userCount);
    int checkIdFest (Utilisateur* tabFest, int* userCount, int idco);
    int checkPasswordFest (Utilisateur* tabFest, int* userCount, char *passwordco, int idco);
    void generateUniqueId(Utilisateur* tabFest, int* genId, int* userCount);
    void accountCreationFestivalGoers(int* userCount, Utilisateur** tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert);
    void displayUsers(Utilisateur* tabFest, int* userCount);
    void reservation(int id, int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert);
    void reserveSeat(int concertFound, int id, int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert);
    void interfaceFestivalGoers(int idco, int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert);
    
#endif