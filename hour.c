#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "manager.h"

//typedef struct {} Heure;
//typedef struct {} Date;


void getPrintHourDate () {
    int h, min, s, day, month, year;
    time_t now;
    // Renvoie l'heure actuelle
    time(&now);
    // Conversion en heure locale
    //printf("Aujourd'hui est : %s", ctime(&now));
    struct tm *local = localtime(&now);
    h = local->tm_hour;        
    min = local->tm_min;       
    s = local->tm_sec;       
    day = local->tm_mday;          
    month = local->tm_mon + 1;     
    year = local->tm_year + 1900;  
    printf("L'heure : %02d:%02d:%02d\n", h, min, s);
    printf("La date : %02d/%02d/%d\n", day, month, year);
}

int compareDate(Concert* tab){
    int max = sizeof(tab)/sizeof(Concert);
    for(int i=0; i<max; i++){
        tab[i].horaired.day==h
    }
    getPrintHourDate ();
}


void checkDate (concert) {
    int retourDate = compareDate();
    if (retourDate==1){
        //freeSalle()
    }

}

int main (){
    getPrintHourDate();
    return 0;
}