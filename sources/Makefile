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
GUI_APP=AlgoUI

CFLAGS =$(INCLUDES) $(COMPILER_OPTIONS)
LDFLAGS =$(LIBRARIES_DIR) $(LIBRARIES) $(LINKER_OPTIONS)

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
all: $(EXEC) $(TEST_EXEC) $(GUI_APP)
else
all: $(EXEC) $(TEST_EXEC)
endif


# ============================================================================ #
# Règles par fichier (algo)
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

types.o : types.h types.c
	$(CC) types.c $(CFLAGS)

# ============================================================================ #
# Règles par fichier (test)
# ============================================================================ #
test.o: test.c test_text.h test_donnees.h test_types.h
	$(CC) test.c $(CFLAGS)

test_text.o: test_text.c test_text.h text.h
	$(CC) test_text.c $(CFLAGS)

test_donnees.o: test_donnees.c test_donnees.h donnees.h
	$(CC) test_donnees.c $(CFLAGS)

test_types.o: test_types.c test_types.h types.h
	$(CC) test_types.c $(CFLAGS)

test_construction.o: test_construction.c test_construction.h construction.h
	$(CC) test_construction.c $(CFLAGS)

test_parser.o: test_parser.c test_parser.h parser.h
	$(CC) test_parser.c $(CFLAGS)

test_affichage.o: test_affichage.c test_affichage.h affichage.h
	$(CC) test_affichage.c $(CFLAGS)

test_representant.o: test_representant.c test_representant.h representant.h
	$(CC) test_representant.c $(CFLAGS)

test_resolution.o: test_resolution.c test_resolution.h resolution.h
	$(CC) test_resolution.c $(CFLAGS)

# test_.o: test_.c test_.h .h
#	$(CC) test_.c $(CFLAGS)

# ============================================================================ #
# Liaison de l'exécutable algo
# ============================================================================ #
$(EXEC): main.o types.o donnees.o affichage.o construction.o resolution.o representant.o text.o parser.o
	$(LD) -o $(EXEC) main.o types.o donnees.o affichage.o construction.o resolution.o representant.o text.o parser.o $(LDFLAGS)
	@echo "Built main executable.\n"

# ============================================================================ #
# Liaison de l'exécutable de test
# ============================================================================ #
$(TEST_EXEC): test.o types.o donnees.o affichage.o construction.o resolution.o representant.o text.o parser.o test_text.o test_donnees.o test_types.o test_construction.o test_parser.o test_affichage.o test_representant.o test_resolution.o
	$(LD) -o $(TEST_EXEC) test.o types.o donnees.o affichage.o construction.o resolution.o representant.o text.o parser.o test_text.o test_donnees.o test_types.o test_construction.o test_parser.o test_affichage.o test_representant.o test_resolution.o $(LDFLAGS)
	@echo "Built test executable.\n"

$(GUI_APP):
	cd .. && xcodebuild -project Algo1A.xcodeproj -target AlgoUI

# ============================================================================ #
# Nettoyage
# ============================================================================ #

ifeq ($(UNAME), Darwin)
clean:
	rm -fv *.o
	cd .. && xcodebuild -project Algo1A.xcodeproj -target AlgoUI clean
else
clean:
	rm -fv *.o
endif


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

