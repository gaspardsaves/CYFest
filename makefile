all: execdef
interface.o: interface.c interface.h structures.h
	gcc -c interface.c -o interface.o
manager.o: manager.c manager.h structures.h couleur.h
	gcc -c manager.c -o manager.o
festivalgoers.o: festivalgoers.c festivalgoers.h structures.h
	gcc -c festivalgoers.c -o festivalgoers.o
smartrobusnest.o: smartrobusnest.c smartrobusnest.h
	gcc -c smartrobusnest.c -o smartrobusnest.o
execdef: interface.o manager.o festivalgoers.o smartrobusnest.o
	gcc interface.o manager.o festivalgoers.o smartrobusnest.o -o execdef

clean:
	rm interface.o manager.o festivalgoers.o smartrobusnest.o
	rm execdef