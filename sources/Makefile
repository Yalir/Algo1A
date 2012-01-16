
CC = gcc -c
LD = gcc
INCLUDES =
LIBRARIES =
LIBRARIES_DIR =
COMPILER_OPTIONS = -g -Wall
LINKER_OPTIONS =
EXEC=algo

CFLAGS =$(INCLUDES) $(COMPILER_OPTIONS)
LDFLAGS =$(LIBRARIES_DIR) $(LIBRARIES) $(LINKER_OPTIONS)

all: $(EXEC)

main.o : main.c affichage.h construction.h resolution.h
	$(CC) main.c $(CFLAGS)

donnees.o : donnees.h Types.h donnees.c
	$(CC) donnees.c $(CFLAGS)

affichage.o : affichage.c affichage.h donnees.h Types.h
	$(CC) affichage.c $(CFLAGS)

construction.o : construction.h construction.c
	$(CC) construction.c $(CFLAGS)
	
resolution.o : resolution.h resolution.c
	$(CC) resolution.c $(CFLAGS)

representant.o : representant.h representant.c Types.h donnees.h
	$(CC) representant.c $(CFLAGS)
	
$(EXEC): main.o donnees.o affichage.o construction.o resolution.o representant.o
	$(LD) -o $(EXEC) main.o donnees.o affichage.o construction.o resolution.o representant.o $(LDFLAGS)

clean:
	rm -fv *.o

run: $(EXEC)
	./$(EXEC)

debug: $(EXEC)
	gdb ./$(EXEC)

