/*
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

#include "test_types.h"
#include "types.h"
#include <assert.h>

void test_types(void)
{
	assert(est_fonction(Variable) == 0);
	assert(est_fonction(Constante) == 0);
	assert(est_fonction(Fonction) == 1);
	assert(est_fonction(Fonction+3) == 1);
	assert(est_fonction(Fonction-1) == 0);
	assert(est_fonction(Fonction+4) == 0);
}
