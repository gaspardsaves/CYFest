#ifndef MANAGER_H
    #define MANAGER_H

    #include "structures.h"
    #include "couleur.h"
    #include "interface.h"
    
    Siege constructSiege(int cat, int price, int f);
    void displaySiege(char* color, Siege s);
    Date getDate();
    Salle constructRoom();
    void displayRoom(Salle S);
    Concert createConcert(Tabdesalle t);
    Salle* createTabRoom(int n);
    Concert* createTabConcert(int n);
    Salle* multiroomCreation(int numberRoom);
    Salle category_aAndPit(Salle s, int n);
    Salle modifSalle(Salle s);
    void numberRoom(int* userCount, Utilisateur* tabFest);
    void interfaceManager (int* userCount, Utilisateur* tabFest);

#endif