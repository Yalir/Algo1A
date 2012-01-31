/*
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#include <stdio.h>
#include "affichage.h"
#include "construction.h"
#include "resolution.h"
#include "donnees.h"
#include "config.h"

/** @brief Breve description de la fonction.
 *
 * Description de la fonction (but, resultats).
 * @param par1  description du parametre.
 * @param par2  description du parametre.
 * @return	description du resultat retourne.
 */


int main (int argc, const char * argv[])
{
	Solutions s;
	Systeme t;
	
	t = construire_systeme();
	afficher_systeme(t);
	s = traiter_systeme(t);
	afficher_solutions(s);
	
#if WINDOWS
	system("PAUSE");
#endif
    return 0;
}

