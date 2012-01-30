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
#include "representant.h"
#include "Types.h"
#include "affichage.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

Solutions traiter_systeme(Systeme sys)
{
	assert(sys != NULL);
	
	Solutions s = creer_solutions();
	initialiser_solutions(s, 5);
	
	Equation *e = sys;
	int insoluble = 0;
	
	while (s != NULL && insoluble == 0 && e)
	{
		puts("check point 1");
		afficher_systeme((const Systeme)e);
		Equation *representee = obtenir_representant_equation(e, s);
		afficher_systeme((const Systeme)representee);
		puts("check point 2");
		
		Equation *dansSys = NULL;
		Equation *dansSolu = NULL;
		
		insoluble = traiter_equation(s, representee, &dansSys, &dansSolu);
		
		printf("insoluble = %d , dansSys = %p , dansSolu = %p\n",
			   insoluble, dansSys, dansSolu);
		
		// s'il y a des équations à ajouter au système d'équations
		if (dansSys)
		{
			Equation *current = sys;
			
			// aller au dernier maillon du système
			while (current->suivant)
				current = current->suivant;
			
			// rajouter la liste d'équation au système
			current->suivant = dansSys;
		}
		
		// s'il y a des équations à ajouter au système de solutions
		if (dansSolu)
		{
			// rajouter la liste des termes droit au système
			ranger_solutions(s, dansSolu);
		}
		
		destroy_equation(representee);
		e = e->suivant;
	}
	
	return s;
}
 
// après l’exécution de la fonction, dansSys contient l’équation qui 
// doit être rajoutée au système, et dansSolu l’équation qui doit
// être rajoutée aux solutions. Si l’un ou les deux paramètres
// contiennent ‘rien’, il n’y a pas à les considérer
int traiter_equation(const Solutions s, const Equation *e, Equation **dansSys, Equation **dansSolu)
{
	assert(s != NULL);
	assert(e != NULL);
	assert(dansSys != NULL);
	assert(dansSolu != NULL);
	
	*dansSys = NULL;
	*dansSolu = NULL;
	
	int flag = 0;
	Terme t_gauche = e->terme_gauche;
	Terme t_droit = e->terme_droit;
	
	// s et t variables
	if (t_gauche->type_terme == Variable && t_droit->type_terme == Variable)
	{
		// même variable
		if (t_gauche->contenu_terme.val == t_droit->contenu_terme.val) // si indice de s = indice de t alors
		{
			// rien à faire, on supprimera cette équation
		}
		else
		{
			// X3 = X4
			if (t_gauche->contenu_terme.val < t_droit->contenu_terme.val) // si indice de s < indice de t alors
			{
				*dansSolu = copie_equation(e); // on rangera l’éq. dans S
			}
			// X4 = X3
			else
			{
				// on réinsère l’éq inversée dans le système
				// intervertir s et t
				*dansSys = creer_equation();
				(*dansSys)->terme_gauche = t_droit;
				(*dansSys)->terme_droit = t_gauche;
			}
		}
	}
	// s variable et t constante
	else if (t_gauche->type_terme == Variable && t_droit->type_terme == Constante)
	{
		// on rangera l’éq. dans S
		*dansSolu = copie_equation(e);
		//**dansSolu = *e;
	}
	else if (t_gauche->type_terme == Variable && t_droit->type_terme >= Fonction)
	{
		// si t est une fonction dépendant de s -> insoluble
		if (contient_terme(t_droit, t_gauche))
		{
			flag = -1;
		}
		// sinon ranger simplement l'équation dans les solutions
		else
		{
			*dansSolu = copie_equation(e); // on rangera l’éq. dans S
		}
	}
	else if (t_gauche->type_terme != Variable && t_droit->type_terme == Variable)
	{
		// intervertir s et t
		*dansSys = creer_equation();
		(*dansSys)->terme_gauche = copie_terme(t_droit);
		(*dansSys)->terme_droit = copie_terme(t_gauche);
	}
	else if (t_gauche->type_terme != Variable && t_droit->type_terme != Variable)
	{
		if (t_gauche->type_terme == Constante && t_droit->type_terme == Constante)
		{
			if (t_gauche->contenu_terme.val == t_droit->contenu_terme.val)
			{
				// ignorer l'équation
			}
			else
			{
				// {2 = 3} -> insoluble
				flag = -1;
			}
		}
		else if (t_gauche->type_terme >= Fonction && t_droit->type_terme >= Fonction)
		{
			// décapsuler les fonctions et faire les correspondances
			*dansSys = decapsuler_fonctions(t_gauche, t_droit); 
			
			if (*dansSys == NULL) // nombre différent de paramètres
			{
				flag = -1; // insoluble
			}
			
		}
		else
		{
			flag = -1;
		}
	}
	else
	{
		flag = -1;
	}
	
	return flag;
}

int contient_terme(Terme conteneur, Terme t)
{
	assert(conteneur != NULL);
	assert(t != NULL);
	assert(t->type_terme == Variable);
	
	int found = 0;
	
	// si le terme est une variable, on vérifie si elle correspond
	// à celle que l'on cherchait
	if (conteneur->type_terme == Variable)
	{
		if (conteneur->contenu_terme.val == t->contenu_terme.val)
			found = 1;
	}
	// si le terme est une constante, ce n'est certainement pas la variable
	// qu'on cherchait
	else if (conteneur->type_terme == Constante)
	{
		// rien à faire
	}
	// si le terme est une fonction, on doit chercher plus en profondeur
	else if (conteneur->type_terme >= Fonction)
	{
		Argument args = conteneur->contenu_terme.arguments;
		
		while (args != NULL && found == 0)
		{
			found = contient_terme(args->terme_argument, t);
			args = args->suivant;
		}
	}
	
	return found;
}

Equation *decapsuler_fonctions(Terme fgauche, Terme fdroit)
{
	assert(fgauche != NULL);
	assert(fdroit != NULL);
	assert(fgauche->type_terme >= Fonction);
	assert(fdroit->type_terme >= Fonction);
	
	Equation *chaine_eq = NULL;
	Equation *prev_eq = NULL;
	
	int fgauche_compte = compter_arguments(fgauche);
	int fdroit_compte = compter_arguments(fdroit);
	
	// on vérifie que le nombre d'arguments correspond
	if (fgauche_compte == fdroit_compte && fgauche_compte > 0)
	{
		Argument arg_gauche = fgauche->contenu_terme.arguments;
		Argument arg_droit = fdroit->contenu_terme.arguments;
		
		// on traite chaque argument
		while (arg_gauche /* && arg_droit */)
		{
			Equation *eq = creer_equation();
			eq->terme_gauche = copie_terme(arg_gauche->terme_argument);
			eq->terme_droit = copie_terme(arg_droit->terme_argument);
			
			// si c'est le premier maillon, on l'enregistre comme tel
			if (chaine_eq == NULL)
			{
				// chaine_eq est le début de la chaîne
				chaine_eq = eq;
				prev_eq = chaine_eq;
			}
			else
			{
				// on fait le chaînage et on garde un pointeur sur le précédent
				// maillon
				prev_eq->suivant = eq;
				prev_eq = eq;
			}
			
			// puis on passe à l'argument suivant
			arg_gauche = arg_gauche->suivant;
			arg_droit = arg_droit->suivant;
		}
	}
	
	return chaine_eq;
}


int compter_arguments(Terme t)
{
	assert(t != NULL);
	assert(t->type_terme >= Fonction);
	
	int compteur = 0;
	Argument args = t->contenu_terme.arguments;
	
	while (args)
	{
		args = args->suivant;
		compteur++;
	}
	
	return compteur;
}


void ranger_solutions(Solutions s, const Equation *e)
{
	assert(s != NULL);
	assert(e != NULL);
	
	// parcourir la liste indiquée par e
	while (e)
	{
		assert(e->terme_gauche != NULL);
		assert(e->terme_droit != NULL);
		
		// on vérifie qu'on a bien une variable à gauche
		if (e->terme_gauche->type_terme == Variable)
		{
			int i = e->terme_gauche->contenu_terme.val;
			
			if (s->array[i])
			{
				fprintf(stderr, "*** warning: erasing previously set solution\n");
				destroy_terme(s->array[i]);
			}
			
			printf("storing solution at index %d\n", i-1);
			s->array[i-1] = copie_terme(e->terme_droit);
		}
		// sinon on ne peut pas enregistrer cette solution
		else
		{
			fprintf(stderr, "*** error: trying to store equation with non variable type as left component\n");
			abort();
		}
		
		e = e->suivant;
	}
}



 
