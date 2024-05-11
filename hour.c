#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//typedef struct {} Heure;
//typedef struct {} Date;
//A voir pour stockage comparaison jour et mois en anglais mais on s'en branle

void getPrintHourDate () {
    int h, min, s, day, mois, an;
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
    mois = local->tm_mon + 1;     
    an = local->tm_year + 1900;  
    printf("L'heure : %02d:%02d:%02d\n", h, min, s);
    printf("La date : %02d/%02d/%d\n", day, mois, an);
}

void compareDate(){}


void checkDate (concert) {
    getPrintHourDate();
    int retourDate = compareDate();
    if (retourDate==1){
        //freeSalle()
    }

}

int main (){
    getPrintHourDate();
    return 0;
}