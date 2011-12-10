/**
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#include "donnees.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

Solutions s = NULL;
Systeme t = NULL;

void init_solutions(void)
{
	assert(s == NULL);
	
	s = (Solutions)malloc(sizeof(*s));
	
	if (s == NULL)
	{
		fprintf(stderr, "malloc error\n");
		abort();
	}
	else
	{
		s->terme_droit = NULL;
		s->suivant = NULL;
	}
}

void init_systeme(void)
{
	assert(t == NULL);
	
	t = (Systeme)malloc(sizeof(*t));
	
	if (t == NULL)
	{
		fprintf(stderr, "malloc error\n");
		abort();
	}
	else
	{
		t->terme_gauche = NULL;
		t->terme_droit = NULL;
		t->suivant = NULL;
	}
}


void destroy_solutions(Solutions sol)
{
	assert(sol != NULL);
	
	if (sol->terme_droit)
		destroy_terme(sol->terme_droit);
	
	if (sol->suivant)
		destroy_solutions(sol->suivant);
	
	
	free(sol);
}

void destroy_systeme(Systeme sys)
{
	assert(sys != NULL);
	if (sys->terme_gauche)
		destroy_terme(sys->terme_gauche);
	
	if (sys->terme_droit)
		destroy_terme(sys->terme_droit);
	
	if (sys->suivant)
		destroy_systeme(sys->suivant);
	
	free(sys);
}

void destroy_terme(Terme terme)
{
	assert(terme != NULL);
	
	if (terme->type_terme >= 30 &&
		terme->type_terme <= 33 &&
		terme->contenu_terme.arguments != NULL)
		destroy_argument(terme->contenu_terme.arguments);
	
	free(terme);
}

void destroy_argument(Argument arg)
{
	assert(arg != NULL);
	
	if (arg->terme_argument)
		destroy_terme(arg->terme_argument);
	
	if (arg->suivant)
		destroy_argument(arg->suivant);
	
	free (arg);
}

