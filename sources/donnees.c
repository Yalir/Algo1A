/*
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
		sol->array = NULL;
		sol->size = 0;
	}
	
	return sol;
}


int initialiser_solutions(Solutions s, unsigned n)
{
	if(s == NULL)
	{
		fprintf(stderr,"*** erreur :initialiser_solutions() - Le paramètre 's' ne devrait jamais être nul.\n");
		return -1;
	}
	else
	{
		if (s->array)
			free(s->array);
		s->size = n;
		s->array = (Terme *)malloc(n * sizeof(Terme));
		
		unsigned i;
		for (i = 0; i < n;i++)
			s->array[i] = NULL;
			return 1;
	}
}


Equation *copie_equation(const Equation *e)
{
	if(e == NULL)
	{
		fprintf(stderr,"*** erreur :copie_equation() - Le paramètre 'e' ne devrait jamais être nul.\n");
		return NULL;
	}
	else
	{
		Equation *nouv = creer_equation();
		
		if (e->terme_gauche)
			nouv->terme_gauche = copie_terme(e->terme_gauche);
		
		if (e->terme_droit)
			nouv->terme_droit = copie_terme(e->terme_droit);
		
		if (e->suivant)
			nouv->suivant = copie_equation(e->suivant);
		
		return nouv;
	}
}


Terme copie_terme(const Terme t)
{
	if(t == NULL)
	{
		fprintf(stderr,"*** erreur :copie_terme() - Le paramètre 't' ne devrait jamais être nul.\n");
		return NULL;
	}
	else
	{	
		Terme nouv = creer_terme();
		nouv->type_terme = t->type_terme;
		
		if (est_fonction(nouv->type_terme))
		{
			if (t->contenu_terme.arguments)
				nouv->contenu_terme.arguments = copie_argument(t->contenu_terme.arguments);
		}
		else
		{
			nouv->contenu_terme.val = t->contenu_terme.val;
		}
		
		return nouv;
	}
}


Argument copie_argument(const Argument arg)
{
	if(arg == NULL)
	{
		fprintf(stderr,"*** erreur :copie_argument() - Le paramètre 'arg' ne devrait jamais être nul.\n");
		return NULL;
	}
	else
	{	
		Argument nouv = creer_argument();
		
		if (arg->terme_argument)
			nouv->terme_argument = copie_terme(arg->terme_argument);
		
		if (arg->suivant)
			nouv->suivant = copie_argument(arg->suivant);	
		return nouv;
	}
}


int destroy_systeme(Systeme sys)
{
	if(sys == NULL)
	{
		fprintf(stderr,"*** erreur :destroy_systeme() - Le paramètre 'sys' ne devrait jamais être nul.\n");
		return -1;
	}
	else
	{
		if (sys->terme_gauche)
		{
			if(destroy_terme(sys->terme_gauche)==-1)
			{
				return -1;
			}
		}
		
		if (sys->terme_droit)
		{
			if(destroy_terme(sys->terme_droit)==-1)
			{
				return -1;
			}
		}
		if (sys->suivant)
		{
			if(destroy_systeme(sys->suivant)==-1)
			{
				return -1;
			}
		}
		free(sys);
		return 1;
	}
}


int destroy_equation(Equation *e)
{
	if(e == NULL)
	{
		fprintf(stderr,"*** erreur :destroy_equation() - Le paramètre 'e' ne devrait jamais être nul.\n");
		return -1;
	}
	else
	{
		if(destroy_systeme(e)==-1)
		{
			return -1;
		}
		return 1;
	}
}


int destroy_terme(Terme terme)
{
	if(terme == NULL)
	{
		fprintf(stderr,"*** erreur :destroy_terme() - Le paramètre 'terme' ne devrait jamais être nul.\n");
		return -1;
	}
	else
	{
		if (terme->type_terme >= 30 &&
			terme->type_terme <= 33 &&
			terme->contenu_terme.arguments != NULL)
			if(destroy_argument(terme->contenu_terme.arguments)==-1)
			{
				return -1;
			} 
		
		free(terme);
		return 1;
	}
}


int destroy_argument(Argument arg)
{
	if(arg == NULL)
	{
		fprintf(stderr,"*** erreur :destroy_argument() - Le paramètre 'arg' ne devrait jamais être nul.\n");
		return -1;
	}
	else
	{
		
		if (arg->terme_argument)
		{
			if(destroy_terme(arg->terme_argument)==-1)
			{
				return -1;
			}
		}
		if (arg->suivant)
		{
			if(destroy_argument(arg->suivant)==-1)
			{
				return -1;
			}
		}
		free (arg);
		return 1;
	}
}


int destroy_solutions(Solutions sol)
{
	if(sol == NULL)
	{
		fprintf(stderr,"*** erreur :destroy_solutions() - Le paramètre 'sol' ne devrait jamais être nul.\n");
		return -1;
	}
	else
	{	
		unsigned size = sol->size;
		unsigned i;
		
		for (i = 0;i < size; i++)
		{
			if (sol->array[i])
			{
				if(destroy_terme(sol->array[i])==-1)
				{
					return -1;
				}
			}
		}	
		free(sol);
		return 1;
	}
}
