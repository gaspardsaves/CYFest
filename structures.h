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

    typedef struct {
        int admin; //1
        int id;
        char* password;
    }Manager;

    // Concert                           --------------------------------
    typedef struct {
        int etat_siege; 
        int categorie; // 1 : classe A et fosse; 2 : classe B; 3 : classe C
        int prix;
        int nombre_personne;
        int fosse; // fosse ou pas f?1:0
        Utilisateur id[2];
    } Siege;

    typedef struct {
        Siege** siege; // double tableau qui va contenir  
        int nb_range;
        int nb_siege_range;
        char* nom[100];
        int arange;
        int brange;
        float prixa;
        float prixb;
        float prixc;
        int state;
    // malloc les sièges
    } Salle; 


    typedef struct {
        char guest[100];
        Date horaired;
        Date horairef;
        Salle salle;
        int state;
    } Concert;

    typedef struct{
        Salle* tab;
    } Tabdesalle;
    
    typedef struct {
        Concert concert[10];
    // Tableau qui contient tout les concerts
    } Festival;

#endif
