#ifndef FESTIVALGOERS_H
    #define FESTIVALGOERS_H
    #include <stdbool.h>
    #include "structures.h"
    #include "smartrobusnest.h"

    Utilisateur* constrTabFestivalGoers(int userCount);
    void generateUniqueId(Utilisateur* tabFest, int* genId, int userCount);
    void accountCreationFestivalGoers(int* tabFest, int* userCount);
    int checkIdFest (Utilisateur* tabFest, int userCount, int idco);
    int checkPasswordFest (Utilisateur* tabFest, int userCount, char passwordco);
    void displayUsers(Utilisateur* tabFest, int userCount);
    void interfaceFestivalGoers(int id);
    
#endif