
CC = gcc -c
LD = gcc
INCLUDES =
LIBRARIES =
LIBRARIES_DIR =
COMPILER_OPTIONS = -g -Wall
LINKER_OPTIONS =

CFLAGS =$(INCLUDES) $(COMPILER_OPTIONS)
LDFLAGS =$(LIBRARIES_DIR) $(LIBRARIES) $(LINKER_OPTIONS)

all: algo

main.o : main.c affichage.h construction.h resolution.h
	$(CC) main.c $(CFLAGS)

donnees.o : donnees.h Types.h
	$(CC) donnees.c $(CFLAGS)

affichage.o : affichage.c affichage.h donnees.h Types.h
	$(CC) affichage.c $(CFLAGS)

construction.o : construction.h
	$(CC) construction.c $(CFLAGS)
	
resolution.o : resolution.h
	$(CC) resolution.c $(CFLAGS)

algo: main.o donnees.o affichage.o construction.o resolution.o
	$(LD) -o algo main.o donnees.o affichage.o construction.o resolution.o $(LDFLAGS)

clean:
	rm -fv *.o

