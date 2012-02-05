/*
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#include "test_resolution.h"
#include "resolution.h"
#include "donnees.h"
#include "parser.h"
#include "text.h"
#include <assert.h>
#include <stdlib.h>

void test_resolution(void)
{
	ResolutionErr err;
	assert(traiter_systeme(NULL, NULL) == NULL);
	assert(traiter_systeme(creer_systeme_depuis_texte("X1=34"), NULL) != NULL);
	assert(traiter_systeme(NULL, &err) == NULL);
	assert(traiter_systeme(creer_systeme_depuis_texte("X1=34"), &err) != NULL);
	assert(traiter_systeme(creer_systeme_depuis_texte("X1=34,X1=2"), &err) == NULL);
	
	Equation *dansSys, *dansSolu;
	assert(traiter_equation(NULL, NULL, NULL, NULL) == -2);
	assert(traiter_equation(creer_solutions(), NULL, NULL, NULL) == -2);
	assert(traiter_equation(NULL, parse_equation(text_creer_depuis_texte("X1=2")), NULL, NULL) == -2);
	assert(traiter_equation(creer_solutions(), parse_equation(text_creer_depuis_texte("X1=2")), NULL, NULL) == -2);
	assert(traiter_equation(creer_solutions(), parse_equation(text_creer_depuis_texte("X1=2")), &dansSys, &dansSolu) == 0);
	assert(traiter_equation(creer_solutions(), parse_equation(text_creer_depuis_texte("X1=2,X1=3")), &dansSys, &dansSolu) == -2);
	
	assert(contient_terme(NULL, NULL) == 0);
	assert(contient_terme(creer_terme(), creer_terme()) == 0);
	assert(decapsuler_fonctions(NULL, NULL) == NULL);
	assert(compter_arguments(NULL) == -1);
	assert(id_fonction(NULL) == -1);
}

