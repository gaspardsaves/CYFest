all: execdef
interface.o: interface.c interface.h smartrobusnest.h structures.h color.h manager.h festivalgoers.h backupfile.h hour.h
	gcc -c interface.c -o interface.o
manager.o: manager.c manager.h smartrobusnest.h structures.h color.h
	gcc -c manager.c -o manager.o
festivalgoers.o: festivalgoers.c festivalgoers.h smartrobusnest.h structures.h color.h
	gcc -c festivalgoers.c -o festivalgoers.o
smartrobusnest.o: smartrobusnest.c smartrobusnest.h
	gcc -c smartrobusnest.c -o smartrobusnest.o
backupfile.o: backupfile.c backupfile.h
	gcc -c backupfile.c -o backupfile.o
hour.o: hour.c hour.h structures.h
	gcc -c hour.c -o hour.o
execdef: interface.o manager.o festivalgoers.o smartrobusnest.o backupfile.o hour.o
	gcc interface.o manager.o festivalgoers.o smartrobusnest.o backupfile.o hour.o -o execdef

clean:
	rm interface.o manager.o festivalgoers.o smartrobusnest.o backupfile.o hour.o
	rm execdef