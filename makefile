all: execdef
interface.o: interface.c interface.h structures.h
	gcc -c interface.c -o interface.o
manager.o: manager.c manager.h structures.h couleur.h
	gcc -c manager.c -o manager.o
execdef: interface.o manager.o smartrobusnest.o
	gcc interface.o manager.o smartrobusnest.o -o execdef