/*
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#include "test_parser.h"
#include "parser.h"
#include <assert.h>
#include <stdlib.h>

void test_parser(void)
{
	assert(creer_systeme_depuis_texte(NULL) == NULL);
	assert(creer_systeme_depuis_texte("") == NULL);
	assert(creer_systeme_depuis_texte("X1=xx") == NULL);
	assert(creer_systeme_depuis_texte("X1=2") != NULL);
	
	assert(parse_equation(NULL) == NULL);
	assert(parse_equation(text_creer_depuis_texte("")) == NULL);
	assert(parse_equation(text_creer_depuis_texte("X1=X2")) != NULL);
	assert(parse_equation(text_creer_depuis_texte("X1 =X2")) == NULL);
	assert(parse_equation(text_creer_depuis_texte("X1=")) == NULL);
	assert(parse_equation(text_creer_depuis_texte("X1=z")) == NULL);
	
	assert(parse_arguments(NULL) == NULL);
	assert(parse_arguments(text_creer_depuis_texte("")) == NULL);
	assert(parse_arguments(text_creer_depuis_texte(" ")) == NULL);
	assert(parse_arguments(text_creer_depuis_texte("1, 2")) == NULL);
	assert(parse_arguments(text_creer_depuis_texte("1,2")) != NULL);
	assert(parse_arguments(text_creer_depuis_texte("1,2x")) == NULL);
	assert(parse_arguments(text_creer_depuis_texte("X1,X2,X3,2,88,F2(99,11,22)")) != NULL);
	assert(parse_arguments(text_creer_depuis_texte("X1,Xx2,X3,2,88,F2(99,11,22)")) == NULL);
	
	assert(parse_terme(NULL) == NULL);
	assert(parse_terme(text_creer_depuis_texte("")) == NULL);
	assert(parse_terme(text_creer_depuis_texte("X1")) != NULL);
	assert(parse_terme(text_creer_depuis_texte("1")) != NULL);
	assert(parse_terme(text_creer_depuis_texte("F1(X2)")) != NULL);
	assert(parse_terme(text_creer_depuis_texte("F1(X2,X1,X3)")) != NULL);
	assert(parse_terme(text_creer_depuis_texte("X1 ")) == NULL);
	assert(parse_terme(text_creer_depuis_texte("=X1")) == NULL);
	assert(parse_terme(text_creer_depuis_texte("X1=")) == NULL);
	assert(parse_terme(text_creer_depuis_texte("z=X1")) == NULL);
	assert(parse_terme(text_creer_depuis_texte("X1=z")) == NULL);
	
	assert(parse_fonction(NULL) == NULL);
	assert(parse_fonction(text_creer_depuis_texte("")) == NULL);
	assert(parse_fonction(text_creer_depuis_texte("X1")) == NULL);
	assert(parse_fonction(text_creer_depuis_texte("1")) == NULL);
	assert(parse_fonction(text_creer_depuis_texte("F1()")) == NULL);
	assert(parse_fonction(text_creer_depuis_texte("F1(X1)")) != NULL);
	assert(parse_fonction(text_creer_depuis_texte("F1(X1,X2,X3)")) != NULL);
	assert(parse_fonction(text_creer_depuis_texte("F1(X1,X2,X3 )")) == NULL);
}

