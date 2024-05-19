#ifndef INTERFACE_H
    #define INTERFACE_H

    #include "structures.h"
    #include "manager.h"
    #include "smartrobusnest.h"
    #include "festivalgoers.h"

    void connectionFestivalGoers (int* userCount, Utilisateur* tabFest);
    void choiceCoFestivalGoers (int* userCount, Utilisateur* tabFest);
    void connectionManager(int* userCount, Utilisateur* tabFest);
    void choiceUser(int* userCount, Utilisateur* tabFest);
    int main();

#endif