#ifndef BACKUPFILE_H
    #define BACKUPFILE_H
    #include <stddef.h>
    #include "structures.h"

void arrayFree(int* userCount, Utilisateur* tabFest, int* roomCount, Salle* tabRoom, int* concertCount, Concert* tabConcert);
void SaveCounter(int* userCount, int* roomCount, int* concertCount);
void ReadCounter(int* userCount, int* roomCount, int* concertCount);
void SaveSaveSit(Salle* s);
void ReadSaveSit(Salle* s);
void SaveScene(Salle* s);
void ReadScene(Salle* s);
Salle SavePointeurSiege(Salle S);
Salle ReadPointeurSiege(Salle S);

#endif