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
	Terme nouveau_terme=NULL;
	Argument arg;
	Equation* parcours_solution;
	
	assert(u !=NULL);

	if(u->type_terme == Variable)
	{
		parcours_solution = copie_equation((Equation*)s); // associer s à parcours_solution
	
		// si (S contient une équation e2 de la forme u = v alors) 

		while (parcours_solution != NULL && !trouver) 
		{			
			if(((parcours_solution->terme_gauche->contenu_terme.val) == (u->contenu_terme.val)) && ((parcours_solution->terme_gauche->contenu_terme.val) == (u->contenu_terme.val)) && ((parcours_solution->terme_gauche->type_terme) == (u->type_terme)))
			{
				trouver = 1;
				// on affecte v à u			
				nouveau_terme = copie_terme(parcours_solution->terme_droit);
				// on affecte le representant de v au nouveau_terme
				nouveau_terme = obtenir_representant_terme(nouveau_terme,s);
			}
			parcours_solution = parcours_solution->suivant ; // passer à la solution suivante
		}
	}
	else
	{
		// on affecte le terme u au nouveau_terme dans le cas où u est une constante ou une fonction
		nouveau_terme = copie_terme(u);
		
		if(nouveau_terme->type_terme == Fonction)
		{
			// u est de la forme :  fm(q1,q2,...,qn)
			// Le representant de u dans S est fm(obtenir_representant (q1), obtenir_representant(q2), ..., obtenir_representant(qn))
			arg = nouveau_terme->contenu_terme.arguments;
			
			// boucle qui parcour tout les arguments de la fonction fm 
			while (arg != NULL)
			{
				
				arg->terme_argument = obtenir_representant_terme(arg->terme_argument,s); // pour obtenir le representant de l'argument
		
				arg = arg->suivant ; // Passer à l'argument suivant
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
