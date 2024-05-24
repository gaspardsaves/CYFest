#ifndef INTERFACE_H
    #define INTERFACE_H

    #include "structures.h"
    #include "manager.h"
    #include "smartrobusnest.h"
    #include "festivalgoers.h"

    void connectionFestivalGoers (int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert);
    void choiceCoFestivalGoers (int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert);
    void connectionManager(int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert);
    void choiceUser(int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert);
    int main();

#endif