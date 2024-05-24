#ifndef HOUR_H
    #define HOUR_H

        #include <stdio.h>
        #include <stdlib.h>
        #include <time.h>
        #include "structures.h"
        #include "manager.h"

        void PrintHourDateNow();
        void PrintHourDate (Date d);
        int CheckHour(Date d);
        Concert VerifConcert(Concert C);
        Concert* VerifTabConcert(Concert* Cab, int* concertCount);

#endif