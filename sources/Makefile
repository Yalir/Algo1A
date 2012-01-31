# ============================================================================ #
#
# ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
# Case 925 - 163, avenue de Luminy
# 13288 Marseille CEDEX 9
#
# Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
# reproduit, utilise ou modifie sans l'avis express de ses auteurs.
#
# ============================================================================ #

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

# ============================================================================ #
# Règles par fichier
# ============================================================================ #
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

text.o : text.h text.c
	$(CC) text.c $(CFLAGS)

parser.o : parser.h parser.c text.h donnees.h Types.h
	$(CC) parser.c $(CFLAGS)

representant.o : representant.h representant.c Types.h donnees.h
	$(CC) representant.c $(CFLAGS)

# ============================================================================ #
# Liaison de l'exécutable
# ============================================================================ #
$(EXEC): main.o donnees.o affichage.o construction.o resolution.o representant.o text.o parser.o
	$(LD) -o $(EXEC) main.o donnees.o affichage.o construction.o resolution.o representant.o text.o parser.o $(LDFLAGS)

# ============================================================================ #
# Nettoyage
# ============================================================================ #
clean:
	rm -fv *.o

# ============================================================================ #
# Exécution
# ============================================================================ #
run: $(EXEC)
	./$(EXEC)

# ============================================================================ #
# Debuggage
# ============================================================================ #
debug: $(EXEC)
	gdb ./$(EXEC)

