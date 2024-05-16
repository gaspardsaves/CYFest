#ifndef INTERFACE_H
    #define INTERFACE_H

    #include "structures.h"
    #include "manager.h"
    #include "smartrobusnest.h"

    int checkIdFest (char idco[30], char** tabid[]);
    int checkPasswordFest (int idco, char passwordco[30], char** tabpassword[30]);
    void connexionFestivalier ();
    void choixCoFestivalier ();
    void connexionManager();
    void choixUtilisateur ();
    int main ();

#endif