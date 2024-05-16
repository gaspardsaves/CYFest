#ifndef MANAGER_H
    #define MANAGER_H

    #include "structures.h"
    #include "couleur.h"
    
    Siege constructSiege(int cat, int price, int f);
    void affiche_siege(char* color, Siege s);
    Date getdate();
    Salle constructSalle();
    void affichesalle(Salle S);
    Concert creerconcert(Tabdesalle t);
    Salle* creetabSalle(int n);
    Salle* creationPlusieursSalles(int numberRoom);
    void numberRoom();
    void interfaceManager();

#endif