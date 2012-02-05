
/*
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#include <stdio.h>
#include "test_types.h"
#include "test_text.h"
#include "test_donnees.h"
#include "test_parser.h"
#include "test_affichage.h"
#include "test_construction.h"
#include "test_representant.h"
#include "test_resolution.h"

int main (int argc, const char * argv[])
{
	test_types();
	test_text();
	test_donnees();
	test_parser();
	test_affichage();
	test_construction();
	test_representant();
	test_resolution();
	
#if WINDOWS
	system("PAUSE");
#endif
    return 0;
}


