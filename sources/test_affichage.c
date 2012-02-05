/*
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#include "test_affichage.h"
#include "affichage.h"
#include "parser.h"
#include "text.h"
#include <stdio.h>

void test_affichage(void)
{
	puts("Comparer X1=2 avec:");
	afficher_systeme(creer_systeme_depuis_texte("X1=2"));
	puts("Comparer X1=F2(X2),X2=3 avec:");
	afficher_systeme(creer_systeme_depuis_texte("X1=F2(X2),X2=3"));
	
	puts("Comparer X3 avec:");
	afficher_terme(parse_terme(text_creer_depuis_texte("X3")));
	puts("");
	puts("Comparer F3(X1,X2,3230987) avec:");
	afficher_terme(parse_terme(text_creer_depuis_texte("F3(X1,X2,3230987)")));
	puts("");
	
	puts("Comparer X1,X2,3230987 avec:");
	afficher_argument(parse_arguments(text_creer_depuis_texte("X1,X2,3230987")));
	puts("");
	
}
