/*
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#include <stdio.h>
#include "test_text.h"
#include "text.h"
#include <assert.h>

void test_text(void)
{
	assert(text_creer_depuis_texte(NULL) == NULL);
	assert(text_creer_depuis_texte("a") != NULL);
	assert(text_obtenir_taille(text_creer_depuis_texte("abc")) == 3);
	
	
}
