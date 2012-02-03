
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
#include "test_donnees.h"

int main (int argc, const char * argv[])
{
	//Systeme s = creer_systeme_depuis_texte("X2 = 2, F1(X1, X2) = F1(F2(1, X2), X3)");
	//afficher_systeme(s);
	
	test_text();
	test_donnees();
	
	// test_types();
	
#if WINDOWS
	system("PAUSE");
#endif
    return 0;
}


