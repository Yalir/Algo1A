
CC = gcc
INCLUDES = 
LIBRARIES = 
LIBRARIES_DIR =
COMPILER_OPTIONS = -g -Wall
LINKER_OPTIONS = 

CFLAGS = $(INCLUDES) $(COMPILER_OPTIONS)
LDFLAGS = $(LIBRARIES_DIR) $(LIBRARIES) $(LINKER_OPTIONS)
all: algo

main.o : main.c affichage.h
	$(CC) $(CFLAGS) -c main.c

donnees.o : donnees.h Types.h
	$(CC) $(CFLAGS) -c donnees.c

affichage.o : affichage.c affichage.h donnees.h Types.h
	$(CC) $(CFLAGS) -c affichage.c

algo: main.o donnees.o affichage.o
	$(CC) -o algo $(LDFLAGS) main.o donnees.o affichage.o

clean : rm -f *.o