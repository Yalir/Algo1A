/**
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 
 
 #include "representant.h"
 #include "donnees.h"
 #include "Types.h"
 #include <stdlib.h>
 #include <assert.h>
 
Terme obtenir_representant_terme(const Terme u, const Systeme s)
{
	int trouver=0;
	Terme nouveau_terme ;
	Equation* parcours_solution;
	Terme arg ;
	
	assert(u !=NULL);
	
	nouveau_terme = creer_terme();

	if(u->type_terme == Variable)
	{		
		parcours_solution = creer_equation();

		// si (S contient une équation e2 de la forme u = v alors) 
		parcours_solution = s;
		while (s!=NULL && !trouver) 
		{			
			if(((parcours_solution->terme_gauche->contenu_terme.val) == (u->contenu_terme.val)) && ((parcours_solution->terme_gauche->contenu_terme.val) == (u->contenu_terme.val)) && ((parcours_solution->terme_gauche->type_terme) == (u->type_terme)))
			{
				// on affecte v à u			
				nouveau_terme= parcours_solution->terme_droit;
				trouver = 1;
				// on affecte le representant de v au nouveau_terme
				nouveau_terme = obtenir_representant_terme(u,s);
			}
			parcours_solution = parcours_solution->suivant ; // passer à la solution suivante
		}
	}
	else
	{
		// on affecte le terme u au nouveau_terme dans le cas où u est une constante ou une fonction
		nouveau_terme = u;
		
		if(u->type_terme == Fonction)
		{
			// u est de la forme :  fm(q1,q2,...,qn)
			// Le representant de u dans S est fm(obtenir_representant (q1), obtenir_representant(q2), ..., obtenir_representant(qn))
			arg = creer_terme();
			
			arg = u->contenu_terme.arguments->terme_argument;
			
			while (arg != NULL)
			{
				arg = obtenir_representant_terme(arg->contenu_terme.arguments->terme_argument,s);
				arg->contenu_terme.arguments->terme_argument = arg->contenu_terme.arguments->suivant->terme_argument;
				
				arg->contenu_terme.arguments = arg->contenu_terme.arguments->suivant; // Passer à l'argument suivant
			}
		}
		// si jamais u->type_terme n'est pas une fonction, le représentant de u dans S est lui-même (u est une constante)
	}
	return nouveau_terme ;
} 

Equation* obtenir_representant_equation(const Equation *e, const Systeme s)
{
	assert(s!=NULL);
	Equation *sys = creer_systeme();

	sys->terme_gauche= creer_terme();
	sys->terme_droit = creer_terme();
	
	sys->terme_gauche = obtenir_representant_terme(e->terme_gauche, s);
	sys->terme_droit = obtenir_representant_terme(e->terme_droit, s);
	
	return sys;
}
