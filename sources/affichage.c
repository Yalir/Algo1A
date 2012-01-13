/**
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#include "affichage.h"
#include "donnees.h"
#include "Types.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void afficher_systeme(Systeme sys)
{
	printf("{");
	while (sys != NULL)
	{
		afficher_terme(sys->terme_gauche);
		printf(" = ");
		afficher_terme(sys->terme_droit);
		sys = sys->suivant;
		
		if(sys!=NULL)
		{
			printf(", ");
		}
	}
	printf("}\n");
}

void afficher_terme(Terme terme)
{
	assert(terme != NULL);
	
	switch(terme->type_terme)
	{
		case Variable:
			printf("X%d", terme->contenu_terme.val);
			break;
			
		case Constante:
			printf("%d", terme->contenu_terme.val);
			break;
			
		case Fonction:
		case Fonction+1:
		case Fonction+2:
		case Fonction+3:
			printf("F%d(", terme->type_terme - Fonction);
			afficher_argument(terme->contenu_terme.arguments);
			printf(")");
			break;
			
		default:
			fprintf(stderr, "type de terme invalide");
			abort();
			break;
	}
}

void afficher_argument(Argument arg)
{
	assert(arg != NULL);
	
	if (arg->terme_argument)
	{
		afficher_terme(arg->terme_argument);
	}
	
	if (arg->suivant)
	{
		printf(", ");
		afficher_argument(arg->suivant);
	}
}

void afficher_solutions(Solutions s)
{
	Solutions p = s;
	int i = 1;
	
	if (s != NULL)
	{
		while (p != NULL)
		{
			printf("X%d = ", i);
			afficher_terme(p->terme_droit);
			printf("\n");
			
			i++;
			p = p->suivant;
		}
	}
	else
	{
		puts("Système insoluble ou pas encore résolu");
	}
	
}
