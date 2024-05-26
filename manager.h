#ifndef MANAGER_H
    #define MANAGER_H

    #include "structures.h"
    #include "color.h"
    #include "interface.h"
    
    Salle* createTabRoom(int* roomCount);
    Concert* createTabConcert(int* concertCount);
    Siege constructSiege(int cat, int price, int f);
    void displaySiege(char* color, Siege s);
    Date getDate();
    Salle ResetScene(Salle s);
    Salle freeTheSceneAfterConcert(Salle s);
    void constructRoom(int* userCount, Utilisateur* tabFest, int* roomCount, Salle** tabRoom, int* concertCount, Concert* tabConcert);
    void displayRoom(Salle S);
    void createConcert(int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert** tabConcert);
    void displayRoomConcert(int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert);
    void reportOnRoom(int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert);
    void salesRevenue(Salle s);
    void ratioSeat(Salle s);
    void multiConcertCreation(int numberConcert, int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert** tabConcert);
    void multiRoomCreation(int numberRoom, int* userCount, Utilisateur* tabFest, int* roomCount, Salle** tabRoom, int* concertCount, Concert* tabConcert);
    Salle category_aAndPit(Salle s, int n);
    Salle modifRoom(Salle s);
    Salle FreeTheSceneAfterConcert(Salle s);
    void dRoom(Salle S);
    void numberRoom(int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert);
    void interfaceManager (int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert);
#endif
