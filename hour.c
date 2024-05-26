#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "manager.h"
#include "smartrobusnest.h"
#include <string.h>

//typedef struct {} Heure;
//typedef struct {} Date;

//*
void printHourDateNow() {
    int h, min, s, day, month, year;
    time_t now;
    // Return current time
    time(&now);
    // Conversion to local time
    //printf("Nous sommes le : %s", ctime(&now));
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

void printHourDate (Date d) {  
    printf("\nL'heure : %02d:%02d\n", d.hour, d.minut);
    printf("La date : %02d/%02d/%d\n", d.day, d.month, d.year);
}

int checkHour(Date d){
    int h, min, s, day, month, year;
    int b = 0;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    h = local->tm_hour;        
    min = local->tm_min;       
    s = local->tm_sec;       
    day = local->tm_mday;          
    month = local->tm_mon + 1;     
    year = local->tm_year + 1900; 
    printHourDateNow();
    printf("%d\n", year);
    printHourDate(d);
    if(d.year<year){
        b = 0;
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
    //printf("\n%d\n", b);
    return b;
}

// Assign a state to the concert 0 if it hasn't started yet, and 1 if the concert has started and -1 if it has finished
void verifConcert(Concert c){ 
    int a = checkHour(c.horaired);
    int b = checkHour(c.horairef);
    if((a==1)&&(b==1)){
        printf("Concert pas encore commencé\n");
        c.state = 0;
    }
    else if((a==0)&&(b==1)){
        printf("Concert déjà commencé\n");
        c.state = 1;
    }
    else if((a==0)&&(b==0)){
        printf("Concert fini\n");
        c.state = -1;
    }
}

Concert* verifTabConcert(Concert* tabConcert, int* concertCount){
    int i = 0;
    int j = 0;
    while(i<(*concertCount)){
        verifConcert(tabConcert[i]);
        if(tabConcert[i].state==-1){
            tabConcert[i].salle = freeTheSceneAfterConcert(tabConcert[i].salle);
            j++;
        }
        i++;
    }
    *concertCount = (*concertCount) - j;
    i = 0;
    int k=0;
    Concert* newTabConcert = malloc((*concertCount)*sizeof(Concert));
    while(i<(*concertCount)){
        if(tabConcert[i].state != -1){
            newTabConcert[k] = tabConcert[i];
            k++;
        }
        i++;
    }
    free(tabConcert);
    return newTabConcert;
}
