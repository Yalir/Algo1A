/*
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#include <stdio.h>
#include "test_donnees.h"
#include "donnees.h"
#include "types.h"
#include <assert.h>
#include <string.h>

void test_donnees(void)
{	
									/*Fonction : creer_systeme() */
	assert(creer_systeme()!=NULL);

									/*Fonction : creer_equation() */
	assert(creer_equation()!=NULL);
	
									/*Fonction : creer_terme() */	
	assert(creer_terme()!=NULL);
	
									/*Fonction : creer_argument() */	
	assert(creer_argument()!=NULL);
	
									/*Fonction : initialiser_solutions() */	
	assert(initialiser_solutions(NULL,3)==-1);
	assert(initialiser_solutions(creer_solutions(),3)==1);

									/*Fonction : copie_equation() */	
	assert(copie_equation(NULL)==NULL);
	assert(copie_equation(creer_equation())!=NULL);
	
									/*Fonction : copie_terme() */	
	assert(copie_terme(NULL)==NULL);
	assert(copie_terme(creer_terme())!=NULL);
	
									/*Fonction : copie_argument() */	
	assert(copie_argument(NULL)==NULL);
	assert(copie_argument(creer_argument())!=NULL);
	
									/*Fonction : destroy_systeme() */	
	assert(destroy_systeme(NULL)==-1);
	assert(destroy_systeme(creer_systeme())==1);	
	
									/*Fonction : destroy_equation() */	
	assert(destroy_equation(NULL)==-1);
	assert(destroy_equation(creer_equation())==1);	
	
									/*Fonction : destroy_terme() */	
	assert(destroy_terme(NULL)==-1);
	assert(destroy_terme(creer_terme())==1);
	
									/*Fonction : destroy_argument() */	
	assert(destroy_argument(NULL)==-1);
	assert(destroy_argument(creer_argument())==1);
	
									/*Fonction : destroy_solutions() */	
	assert(destroy_solutions(NULL)==-1);
	assert(destroy_solutions(creer_solutions())==1);
}
