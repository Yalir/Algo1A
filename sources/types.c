/*
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#include "types.h"
#include <stdio.h>

int est_fonction(TypeTerme t)
{
	if (t >= Fonction && t <= Fonction + 3)
		return 1;
	else
	{
		if (t > Fonction + 3 && t <= Fonction + 10)
			fprintf(stderr, "*** avertissement: est_fonction() - fonction d'indice %d invalide.\n", t - Fonction);
		
		return 0;
	}
}
