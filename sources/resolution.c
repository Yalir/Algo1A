/*
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
#include "types.h"
#include "affichage.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


Solutions traiter_systeme(Systeme sys, ResolutionErr *err)
{
	if (sys == NULL)
	{
		fprintf(stderr, "*** erreur : traiter_systeme() - le paramètre 'sys' ne devrait jamais être nul.\n");
		return NULL;
	}
	
	Solutions s = creer_solutions();
	initialiser_solutions(s, 5);
	
	Equation *e = sys;
	int insoluble = 0;
	
	while (s != NULL && insoluble == 0 && e)
	{
		Equation *dansSys = NULL;
		Equation *dansSolu = NULL;
		Equation *representee = NULL;
		
		representee = obtenir_representant_equation(e, s);
		insoluble = traiter_equation(s, representee, &dansSys, &dansSolu);
		
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
			destroy_equation(dansSolu);
		}
		
		if (representee)
			destroy_equation(representee);
		e = e->suivant;
	}
	
	if (insoluble == -1)
	{
		destroy_solutions(s), s = NULL;
	}
	
	if (err)
	{
		if (insoluble == -1)
			*err = ResolutionErrImpossible;
		else
			*err = ResolutionErrNone;
	}
	
	return s;
}


// après l’exécution de la fonction, dansSys contient l’équation qui 
// doit être rajoutée au système, et dansSolu l’équation qui doit
// être rajoutée aux solutions. Si l’un ou les deux paramètres
// contiennent ‘rien’, il n’y a pas à les considérer
int traiter_equation(const Solutions s, const Equation *e, Equation **dansSys, Equation **dansSolu)
{
	if (s == NULL)
	{
		fprintf(stderr, "*** erreur : traiter_equation() - le paramètre 's' ne devrait jamais être nul.\n");
		return -2;
	}
	else if (e == NULL)
	{
		fprintf(stderr, "*** erreur : traiter_equation() - le paramètre 'e' ne devrait jamais être nul.\n");
		return -2;
	}
	else if (dansSys == NULL)
	{
		fprintf(stderr, "*** erreur : traiter_equation() - le paramètre 'dansSys' ne devrait jamais être nul.\n");
		return -2;
	}
	else if (dansSolu == NULL)
	{
		fprintf(stderr, "*** erreur : traiter_equation() - le paramètre 'dansSolu' ne devrait jamais être nul.\n");
		return -2;
	}
	
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
				(*dansSys)->terme_gauche = copie_terme(t_droit);
				(*dansSys)->terme_droit = copie_terme(t_gauche);
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
	else if (t_gauche->type_terme == Variable && est_fonction(t_droit->type_terme))
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
		else if (est_fonction(t_gauche->type_terme) && est_fonction(t_droit->type_terme))
		{
			// décapsuler les fonctions et faire les correspondances
			*dansSys = decapsuler_fonctions(t_gauche, t_droit); 
			
			if (*dansSys == NULL) // nombre différent de paramètres ou fonctions différentes
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
	if (conteneur == NULL)
	{
		fprintf(stderr, "*** erreur : contient_terme() - le paramètre 'conteneur' ne devrait jamais être nul.\n");
		return 0;
	}
	else if (t == NULL)
	{
		fprintf(stderr, "*** erreur : contient_terme() - le paramètre 't' ne devrait jamais être nul.\n");
		return 0;
	}
	else if (t->type_terme != Variable)
	{
		fprintf(stderr, "*** erreur : contient_terme() - le terme 't' devrait être de type Variable.\n");
		return 0;
	}
	
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
	else if (est_fonction(conteneur->type_terme))
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
	if (fgauche == NULL)
	{
		fprintf(stderr, "*** erreur : decapsuler_fonctions() - le paramètre 'fgauche' ne devrait jamais être nul.\n");
		return NULL;
	}
	else if (fdroit == NULL)
	{
		fprintf(stderr, "*** erreur : decapsuler_fonctions() - le paramètre 'fdroit' ne devrait jamais être nul.\n");
		return NULL;
	}
	else if (!est_fonction(fgauche->type_terme))
	{
		fprintf(stderr, "*** erreur : decapsuler_fonctions() - le terme 'fgauche' devrait être de type Fonction.\n");
		return NULL;
	}
	else if (!est_fonction(fdroit->type_terme))
	{
		fprintf(stderr, "*** erreur : decapsuler_fonctions() - le terme 'fdroit' devrait être de type Fonction.\n");
		return NULL;
	}
	
	Equation *chaine_eq = NULL;
	Equation *prev_eq = NULL;
	
	int fgauche_compte = compter_arguments(fgauche);
	int fdroit_compte = compter_arguments(fdroit);
	int fgauche_id = id_fonction(fgauche);
	int fdroit_id = id_fonction(fdroit);
	
	// on vérifie que le nombre d'arguments correspond
	if (fgauche_compte == fdroit_compte && fgauche_compte > 0 &&
		fgauche_id == fdroit_id)
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
	if (t == NULL)
	{
		fprintf(stderr, "*** erreur : compter_arguments() - le paramètre 't' ne devrait jamais être nul.\n");
		return -1;
	}
	else if (!est_fonction(t->type_terme))
	{
		fprintf(stderr, "*** erreur : compter_arguments() - le terme 't' devrait être de type Fonction.\n");
		return -1;
	}
	
	int compteur = 0;
	Argument args = t->contenu_terme.arguments;
	
	while (args)
	{
		args = args->suivant;
		compteur++;
	}
	
	return compteur;
}

int id_fonction(const Terme t)
{
	int id = -1;
	
	if (t && est_fonction(t->type_terme))
	{
		id = t->type_terme - Fonction;
	}
	
	return id;
}

void ranger_solutions(Solutions s, const Equation *e)
{
	if (s == NULL)
	{
		fprintf(stderr, "*** erreur : ranger_solutions() - le paramètre 's' ne devrait jamais être nul.\n");
		return;
	}
	else if (e == NULL)
	{
		fprintf(stderr, "*** erreur : ranger_solutions() - le paramètre 'e' ne devrait jamais être nul.\n");
		return;
	}
	
	// parcourir la liste indiquée par e
	while (e)
	{
		assert(e->terme_gauche != NULL);
		assert(e->terme_droit != NULL);
		
		// on vérifie qu'on a bien une variable à gauche
		if (e->terme_gauche->type_terme == Variable)
		{
			int i = e->terme_gauche->contenu_terme.val;
			
			if (s->array[i-1])
			{
				fprintf(stderr, "*** warning: erasing previously set solution\n");
				destroy_terme(s->array[i-1]);
			}
			
			//printf("storing solution at index %d\n", i-1);
			s->array[i-1] = copie_terme(e->terme_droit);
		}
		// sinon on ne peut pas enregistrer cette solution
		else
		{
			fprintf(stderr, "*** erreur : en train d'essayer de ranger une équation avec un terme gauche de type différent de Variable. Comportement inconsistent. Arrêt.\n");
			abort();
		}
		
		e = e->suivant;
	}
}



 
