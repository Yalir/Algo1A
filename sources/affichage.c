//
//  affichage.c
//  Algo1A
//
//  Created by Ceylo on 10/12/11.
//  Copyright 2011 Yalir. All rights reserved.
//

#include "affichage.h"
#include "donnees.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void afficher_solutions(void)
{
	// Solutions s;
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
		puts("Système insoluble");
	}
	
}

void afficher_terme(Terme terme)
{
	assert(terme != NULL);
	
	switch(terme->type_terme)
	{
		case 1: // variable
			printf("X%d", terme->contenu_terme.val);
			break;
			
		case 2: // constante
			printf("%d", terme->contenu_terme.val);
			break;
			
		case 30:
		case 31:
		case 32:
		case 33:
			printf("F(");
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
		printf(" ");
	}
	
	if (arg->suivant)
		afficher_argument(arg->suivant);
}
