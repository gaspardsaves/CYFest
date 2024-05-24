#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "manager.h"
#include "smartrobusnest.h"
#include <string.h>


//typedef struct {} Heure;
//typedef struct {} Date;


void PrintHourDateNow() {
    int h, min, s, day, month, year;
    time_t now;
    // Renvoie l'heure actuelle
    time(&now);
    // Conversion en heure locale
    //printf("Aujourd'hui est : %s", ctime(&now));
    struct tm *local = localtime(&now);
    h = local->tm_hour + 2;        
    min = local->tm_min;       
    s = local->tm_sec;       
    day = local->tm_mday;          
    month = local->tm_mon + 1;     
    year = local->tm_year + 1900; 
    //Ligne de test
    //printf("L'heure : %02d:%02d:%02d\n", h, min, s);
    //printf("La date : %02d/%02d/%d\n", day, month, year);
}

/*
int compareDate(Concert* tab){
    int max = sizeof(tab)/sizeof(Concert);
    for(int i=0; i<max; i++){
        tab[i].horaired.day==h;
    }
    else if(d.year>year){
        b = 1;
    }
    else{
        if(d.month<month){
            b = 0;
        }
        else if(d.month>month){
            b = 1;
        }
        else{
            if (d.day<day){
                b = 0;
            }
            else if(d.day>day){
                b = 1;
            }
            else{
                if(d.hour<h){
                    b = 0;
                }
                else if(d.hour>h){
                    b = 1;
                }
                else{
                    if(d.minut<min){
                        b = 0;
                    }
                    else if(d.minut>min){
                        b = 1;
                    }
                    else{
                        b = 0;
                    }
                }
            }
        }
    }
    printf("\n%d\n", b);
    return b;
}

Concert VerifConcert(Concert C){ //0 if concert finished or 1 if 
    int a = CheckHour(C.horaired);
    int b = CheckHour(C.horairef);
    if((a==1)&&(b==1)){
        printf("\nPas encore commencé\n");
        C.state = 0;
    }
    else if((a==0)&&(b==1)){
        printf("\nDéjà commencé\n");
        C.state = 1;
    }
    else if((a==0)&&(b==0)){
        printf("\nFinis\n");
        C.state = -1;
    }
    return C;
}


Concert* VerifTabConcert(Concert* Cab, int* Concertcount){
    int i = 0;
    int j = 0;
    while(i<(*Concertcount)){
        Cab[i] = VerifConcert(Cab[i]);
        if(Cab[i].state==-1){
            Cab[i].salle = ResetScene(Cab[i].salle);
            j++;
        }
        i++;
    }
    *Concertcount = (*Concertcount) - j;
    i = 0;
    int k=0;
    //Principe marche mais je n'arrive pas à realloc stp aide moi celui qui lit ce message
    Concert* Cab2 = malloc((*Concertcount)*sizeof(Concert));
    while(i<(*Concertcount)){
        if(Cab[i].state != -1){
            Cab2[k] = Cab[i];
            k++;
        }
        i++;
    }
    free(Cab);
    return Cab2;
}

int main (){
    getPrintHourDate();
    return 0;
}
//*/
