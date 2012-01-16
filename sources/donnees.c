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


Systeme creer_systeme(void)
{
    Systeme sys;
    sys = (Systeme)malloc(sizeof(*sys));
	
	if (sys == NULL)
	{
		fprintf(stderr, "malloc error\n");
		abort();
	}
	else
	{
		sys->terme_gauche = NULL;
		sys->terme_droit = NULL;
		sys->suivant = NULL;
		return sys;
	}       
}

Equation *creer_equation(void)
{
	return creer_systeme();
}

Terme creer_terme(void)
{
	Terme te;
	te = (Terme)malloc(sizeof(*te));

	if(te == NULL)
	{
		fprintf(stderr, "malloc error\n");
		abort();
	}
	else
	{
		te->type_terme = 0;
		te->contenu_terme.arguments = (Argument)NULL;
		te->contenu_terme.val = 0;
	}
	return te;
}

Argument creer_argument(void)
{
	Argument a;
	a = (Argument)malloc(sizeof(*a));

	if(a == NULL)
	{
		fprintf(stderr, "malloc error\n");
		abort();
	}
	else
	{
		a->suivant=NULL;
		a->terme_argument=NULL;
	}
	return a;
}

Solutions creer_solutions(void)
{
	Solutions sol;
	sol = (Solutions)malloc(sizeof(*sol));
	
	if (sol == NULL)
	{
		fprintf(stderr, "malloc error\n");
		abort();
	}
	else
	{
		sol->terme_droit = NULL;
		sol->suivant = NULL;
	}
	
	return sol;
}


void initialiser_solutions(Solutions s, unsigned n)
{
	assert(s != NULL);
	
	unsigned i;
	for (i = 0; i < n-1;i++)
	{
		s->suivant = creer_solutions();
		s = s->suivant;
	}
}


Equation *copie_equation(const Equation *e)
{
	assert(e != NULL);
	
	Equation *nouv = creer_equation();
	
	if (e->terme_gauche)
		nouv->terme_gauche = copie_terme(e->terme_gauche);
	
	if (e->terme_droit)
		nouv->terme_droit = copie_terme(e->terme_droit);
	
	if (e->suivant)
		nouv->suivant = copie_equation(e->suivant);
	
	return nouv;
}

Terme copie_terme(const Terme t)
{
	assert(t != NULL);
	
	Terme nouv = creer_terme();
	nouv->type_terme = t->type_terme;
	
	if (nouv->type_terme >= Fonction)
	{
		if (nouv->contenu_terme.arguments)
			nouv->contenu_terme.arguments = copie_argument(t->contenu_terme.arguments);
	}
	else
	{
		nouv->contenu_terme.val = t->contenu_terme.val;
	}
	
	return nouv;
}

Argument copie_argument(const Argument arg)
{
	assert(arg != NULL);
	
	Argument nouv = creer_argument();
	
	if (arg->terme_argument)
		nouv->terme_argument = copie_terme(arg->terme_argument);
	
	if (arg->suivant)
		nouv->suivant = copie_argument(arg->suivant);
	
	return nouv;
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

void destroy_equation(Equation *e)
{
	destroy_systeme(e);
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

void destroy_solutions(Solutions sol)
{
	assert(sol != NULL);
	
	if (sol->terme_droit)
		destroy_terme(sol->terme_droit);
	
	if (sol->suivant)
		destroy_solutions(sol->suivant);
	
	
	free(sol);
}

