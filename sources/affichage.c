/*
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#include "affichage.h"
#include "donnees.h"
#include "types.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


void afficher_systeme(const Systeme sys)
{
	Equation *current = sys;
	
	printf("{");
	while (current != NULL)
	{
		afficher_terme(current->terme_gauche);
		printf(" = ");
		afficher_terme(current->terme_droit);
		
		current = current->suivant;
		
		if(current != NULL)
			printf(", ");
	}
	
	printf("}\n");
}


void afficher_terme(const Terme terme)
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


void afficher_argument(const Argument arg)
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


void afficher_solutions(const Solutions s)
{
	int i;
	
	if (s)
	{
		printf("Solutions:\n");
		
		for (i = 0; i < s->size;i++)
		{
			if (s->array[i])
			{
				printf("X%d = ", i+1);
				afficher_terme(s->array[i]);
				printf("\n");
			}
		}
	}
	else
	{
		puts("Système insoluble ou pas encore résolu");
	}
	
}
