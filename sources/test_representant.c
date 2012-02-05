/*
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "test_representant.h"
#include "representant.h"
#include "donnees.h"
#include "types.h"


void test_representant(void)
{
									/*Fonction : obtenir_representant_terme(const Terme u,const Solutions s) */
									
assert(obtenir_representant_terme(NULL,NULL)==NULL);
									/*Fonction :obtenir_representant_equation(const Equation *e,const Solutions s */
assert(obtenir_representant_equation(NULL,NULL)==NULL);


	
}

