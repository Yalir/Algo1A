/**
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 
 
 #include "resolution.h"
 #include "donnees.h"
 #include "Types.h"
 #include <stdlib.h>
 #include <assert.h>
 
Solutions traiter_systeme(Systeme sys)
{
	return NULL;
}
 
// après l’exécution de la fonction, dansSys contient l’équation qui 
// doit être rajoutée au système, et dansSolu l’équation qui doit
// être rajoutée aux solutions. Si l’un ou les deux paramètres
// contiennent ‘rien’, il n’y a pas à les considérer
void traiter_equation(Solutions s, Equation *e, Equation **dansSys, Equation **dansSolu)
{
	assert(e != NULL);
	assert(dansSys != NULL);
	assert(dansSolu != NULL);
	
	*dansSys = NULL;
	*dansSolu = NULL;
	
	Terme ps = e->terme_gauche;
	Terme pt = e->terme_droit;
	
	if (ps->type_terme == Variable && pt->type_terme == Variable)
	{
		if (ps->contenu_terme.val == pt->contenu_terme.val) // si indice de s = indice de t alors
		{
			// rien à faire, on supprimera cette équation
		}
		else
		{
			if (ps->contenu_terme.val < pt->contenu_terme.val) // si indice de s < indice de t alors
			{
				*dansSolu = e; // on rangera l’éq. dans S
			}
			else
			{
				// intervertir s et t
				e->terme_gauche = pt;
				e->terme_droit = ps;
				// on réinsère l’éq inversée dans le système
				*dansSys = e;
			}
		}
	}
	else if (ps->type_terme == Variable && pt->type_terme == Constante)
	{
		*dansSolu = e; // on rangera l’éq. dans S
	}
	else if (ps->type_terme == Variable && pt->type_terme >= Fonction) // && (t est une fonction dépendant de S)
	{
		// S <- insoluble
		destroy_solutions(s);
		s = NULL;
	}
	else
	{
		*dansSolu = e;
	}
}
 
void obtenir_representant(Terme u ,Systeme e, Systeme *dansSolu)
{
	int trouver=0;
	assert(e != NULL);
	u = e->terme_gauche;
	assert(u !=NULL);

	if(u->type_terme == Variable)
	{
		// si (S contient une équation e2 de la forme u = v alors) 
		while (*dansSolu!=NULL && !trouver) 
		{
			assert((*dansSolu)->terme_gauche);
			
			if((((*dansSolu)->terme_gauche->contenu_terme.val) == (u->contenu_terme.val)) && (((*dansSolu)->terme_gauche->contenu_terme.val) == (u->contenu_terme.val)) && (((*dansSolu)->terme_gauche->type_terme) == (u->type_terme)))
			{
				// on affecte v à u 
				u= (*dansSolu)->terme_droit;
				trouver = 1;
				obtenir_representant((*dansSolu)->terme_droit,e,dansSolu);
			}
		}
	}
	else
	{
		// le représentant de u dans S est lui-même pour si u est une constante
		
		if(u->type_terme == Fonction)
		{
			// u est fm(q1,q2,...,qn)
			// le representant de u dans S est fm(obtenir_representant (q1), obtenir_representant(q2), ..., obtenir_representant(qn))
			
			while (u->contenu_terme.arguments != NULL)
			{
				obtenir_representant(u->contenu_terme.arguments->terme_argument,e,dansSolu);
				u->contenu_terme.arguments->terme_argument = u->contenu_terme.arguments->suivant;
			}
		}
	}
}
