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
TEST_EXEC=test_algo

CFLAGS =$(INCLUDES) $(COMPILER_OPTIONS)
LDFLAGS =$(LIBRARIES_DIR) $(LIBRARIES) $(LINKER_OPTIONS)

all: $(EXEC) $(TEST_EXEC)

# ============================================================================ #
# Règles par fichier
# ============================================================================ #
main.o : main.c affichage.h construction.h resolution.h
	$(CC) main.c $(CFLAGS)

donnees.o : donnees.h types.h donnees.c
	$(CC) donnees.c $(CFLAGS)

affichage.o : affichage.c affichage.h donnees.h types.h
	$(CC) affichage.c $(CFLAGS)

construction.o : construction.h construction.c
	$(CC) construction.c $(CFLAGS)
	
resolution.o : resolution.h resolution.c
	$(CC) resolution.c $(CFLAGS)

text.o : text.h text.c
	$(CC) text.c $(CFLAGS)

parser.o : parser.h parser.c text.h donnees.h types.h
	$(CC) parser.c $(CFLAGS)

representant.o : representant.h representant.c types.h donnees.h
	$(CC) representant.c $(CFLAGS)

test.o: test.c
	$(CC) test.c $(CFLAGS)

# ============================================================================ #
# Liaison de l'exécutable
# ============================================================================ #
$(EXEC): main.o donnees.o affichage.o construction.o resolution.o representant.o text.o parser.o
	$(LD) -o $(EXEC) main.o donnees.o affichage.o construction.o resolution.o representant.o text.o parser.o $(LDFLAGS)

$(TEST_EXEC): test.o donnees.o affichage.o construction.o resolution.o representant.o text.o parser.o
	$(LD) -o $(TEST_EXEC) test.o donnees.o affichage.o construction.o resolution.o representant.o text.o parser.o $(LDFLAGS)

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
# Test
# ============================================================================ #
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# ============================================================================ #
# Debuggage
# ============================================================================ #
debug: $(EXEC)
	gdb ./$(EXEC)

debug_test: $(TEST_EXEC)
	gdb ./$(TEST_EXEC)

