#ifndef STRUCTURES
    #define STRUCTURES
    #include <stddef.h>

    typedef struct{
        int year;
        int month;
        int day;
        int hour;
        int minut;
    }Date;
    
    //utilisateur
    typedef struct {
        int admin; //1
        int id;
        char* password;
        int** resa; // double tableau qui contient les concerts et les sièges associés à ces derniers;
        int porte_feuille;
    }Utilisateur;

    // Concert                           --------------------------------
    typedef struct {
        int etat_siege; 
        int categorie; // 1 : classe A et fosse; 2 : classe B; 3 : classe C
        int prix;
        int nombre_personne;
        int fosse; // fosse ou pas f?1:0
        int id[2];
    } Siege;

    typedef struct {
        Siege** siege; // double tableau qui va contenir les sièges 
        int nb_range;
        int nb_siege_range;
        char* nom;
        int arange;
        int brange;
        float prixa;
        float prixb;
        float prixc;
        int state;
        Siege* saveSit;
    } Salle; 


    typedef struct {
        char* guest;
        Date horaired;
        Date horairef;
        Salle salle;
        int state;
    } Concert;

#endif
