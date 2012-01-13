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
 
Terme obtenir_representant_terme(Terme u, Systeme s)
{
	int trouver=0;
	assert(u !=NULL);

	if(u->type_terme == Variable)
	{
		// si (S contient une équation e2 de la forme u = v alors) 
		while (s!=NULL && !trouver) 
		{
			assert(s->terme_gauche);
			
			if(((s->terme_gauche->contenu_terme.val) == (u->contenu_terme.val)) && ((s->terme_gauche->contenu_terme.val) == (u->contenu_terme.val)) && ((s->terme_gauche->type_terme) == (u->type_terme)))
			{
				// on affecte v à u 
				u= s->terme_droit;
				trouver = 1;
				u = obtenir_representant_terme(u,s);
			}
			s = s->suivant ; // passer à la solution suivante
		}
	}
	else
	{
		// le représentant de u dans S est lui-même pour si u est une constante
		
		if(u->type_terme == Fonction)
		{
			// u est de la forme :  fm(q1,q2,...,qn)
			// Le representant de u dans S est fm(obtenir_representant (q1), obtenir_representant(q2), ..., obtenir_representant(qn))
			Terme arg ;
			arg = creer_terme();
			
			arg = u->contenu_terme.arguments->terme_argument;
			
			while (arg != NULL)
			{
				arg = obtenir_representant_terme(arg->contenu_terme.arguments->terme_argument,s);
				arg->contenu_terme.arguments->terme_argument = arg->contenu_terme.arguments->suivant->terme_argument;
				
				arg->contenu_terme.arguments = arg->contenu_terme.arguments->suivant; // Passer à l'argument suivant
			}
		}
	}
	return u ;
}

Equation* obtenir_representant_equation(Equation *e, Systeme s)
{
	assert(s!=NULL);
	Equation *sys = creer_systeme();

	sys->terme_gauche= creer_terme();
	sys->terme_droit = creer_terme();
	
	sys->terme_gauche = obtenir_representant_terme(e->terme_gauche, s);
	sys->terme_droit = obtenir_representant_terme(e->terme_droit, s);
	
	return sys;
}
