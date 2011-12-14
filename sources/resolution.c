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
 
 void traiter_systeme(void)
 {
 
 }
 
 // après l’exécution de la fonction, dansSys contient l’équation qui 
// doit être rajoutée au système, et dansSolu l’équation qui doit
// être rajoutée aux solutions. Si l’un ou les deux paramètres
// contiennent ‘rien’, il n’y a pas à les considérer
void traiter_equation(Equation *e, Equation **dansSys, Equation **dansSolu)
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
 
