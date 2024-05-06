//Interface                          -----------------------------------
typedef struct {
    int admin; //1
    int id;
    char* password;
} Manager;

typedef struct {
    int admin; //0
    int id; 
    char* password;
    int** resa; // double tableau qui contient les concerts et les sièges associés à ces derniers;
    int porte_feuille;
} Utilisateur; 

// Concert                           --------------------------------

typedef struct {
    int etat_salle; 
    int categorie;
    int prix;
    int nombre_personne;
    int fosse; // fosse ou pas f?1:0
    Utilisateur id[20];
} Siege;

typedef struct {
    int** siege[10]; // double tableau qui va contenir  
    int nb_range;
    int nb_siege_range;
    int nb_cat_par_ranger;
//déterminer le la catégorie C
// malloc les sièges
} Salle; 

typedef struct {
    char guest;
    int horaire_d;
    int horaire_f;
    Salle salle;
} Concert;

typedef struct {
    int concert[10];
// Tableau qui contient tout les concerts
} Festival;