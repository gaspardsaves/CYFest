#ifndef HOUR_H
    #define HOUR_H

        #include <stdio.h>
        #include <stdlib.h>
        #include <time.h>
        #include "structures.h"
        #include "manager.h"

        void printHourDateNow();
        void printHourDate (Date d);
        int checkHour(Date d);
        Concert verifConcert(Concert C);
        Concert* verifTabConcert(Concert* tabConcert, int* concertCount);

#endif