/*
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include "parser.h"
#include "text.h"
#include "donnees.h"
#include "types.h"


Systeme creer_systeme_depuis_texte(const char *input)
{
	if (input == NULL)
		return NULL;
	else if (strlen(input) == 0)
		return NULL;
	else
	{
		
		Systeme sys = NULL;	
		Equation *e = NULL, *prev = NULL;
		Text t = text_creer_depuis_texte(input);
		text_retirer_espaces(t);
		text_en_maj(t);
		
		Text *items = NULL;
		unsigned count = 0;
		unsigned i, should_abort = 0;
		
		text_decoupe_premier_niveau(t, ',', &items, &count);
		
		for (i = 0;i < count && !should_abort;i++)
		{
			e = parse_equation(items[i]);
			
			// Chaîner l'équation
			if (e)
			{
				if (prev)
					prev->suivant = e;
				else
					sys = e;
				
				prev = e;
			}
			// Interrompre le traitement
			else
			{
				should_abort = 1;
			}
		}
		
		if (should_abort)
		{
			if (sys)
				destroy_systeme(sys), sys = NULL;
		}
		
		for (i = 0; i < count;i++)
			text_destroy(items[i]);
		free(items);
		text_destroy(t);
		
		return sys;
	}
}


Equation *parse_equation(Text item)
{
	if (item == NULL)
	{
		fprintf(stderr, "*** erreur : parse_equation() - argument 'item' nul invalide.\n");
		return NULL;
	}
	else if (text_contient_char(item, ' '))
	{
		fprintf(stderr, "*** erreur : parse_equation() - argument 'item' ne doit pas contenir d'espaces.\n");
		return NULL;
	}
	else
	{
		// Forme: ...=...
		Equation *e = NULL;
		Text *items = NULL;
		unsigned count = 0, i;
		
		text_decoupe_premier_niveau(item, '=', &items, &count);
		
		// erreur
		if (count == 2)
		{
			e = creer_equation();
			e->terme_gauche = parse_terme(items[0]);
			e->terme_droit = parse_terme(items[1]);
			
			if (e->terme_gauche == NULL || e->terme_droit == NULL)
				destroy_equation(e), e = NULL;
		}
		else
		{
			fprintf(stderr,
					"*** erreur : parse_equation() - nombre incorrect de parties dans l'équation (%d ≠ 2).\n",
					count);
		}
		
		for (i = 0; i < count;i++)
			text_destroy(items[i]);
		free(items);
		
		return e;
	}
}


Argument parse_arguments(Text item)
{
	if (item == NULL)
	{
		fprintf(stderr, "*** erreur : parse_arguments() - argument 'item' nul invalide.\n");
		return NULL;
	}
	else if (text_contient_char(item, ' '))
	{
		fprintf(stderr, "*** erreur : parse_arguments() - argument 'item' ne doit pas contenir d'espaces.\n");
		return NULL;
	}
	else
	{
		// Forme: a,F(b,c),4
		Argument a = NULL, current = NULL, prev = NULL;
		Text *items = NULL;
		unsigned count = 0, i, should_abort = 0;
		
		text_decoupe_premier_niveau(item, ',', &items, &count);
		
		for (i = 0; i < count && !should_abort;i++)
		{
			Terme term = parse_terme(items[i]);
			
			if (term)
			{
				current = creer_argument();
				current->terme_argument = term;
				
				// Chaîner le terme
				if (prev)
					prev->suivant = current;
				else
					a = current;
				
				prev = current;
			}
			else
			{
				should_abort = 1;
			}
		}
		
		for (i = 0; i < count;i++)
			text_destroy(items[i]);
		free(items);
		
		if (a && should_abort)
			destroy_argument(a), a = NULL;
		
		return a;
	}
}


Terme parse_terme(Text item)
{
	if (item == NULL)
	{
		fprintf(stderr, "*** erreur : parse_terme() - argument 'item' nul invalide.\n");
		return NULL;
	}
	else if (text_contient_char(item, ' '))
	{
		fprintf(stderr, "*** erreur : parse_terme() - argument 'item' ne doit pas contenir d'espaces.\n");
		return NULL;
	}
	else
	{
		// Forme: "a" ou "F(b,c)" ou "4"
		Terme t = NULL;
		const char *cStr = text_obtenir_texte(item);
		
		// Variable
		if (cStr[0] == 'X')
		{
			if (strlen(cStr) > 2)
			{
				fprintf(stderr, "*** erreur : parse_terme() - terme de type Variable formé de plus de 2 caractères.\n");
			}
			else
			{
				int varNum = cStr[1] - '0';
				
				if (varNum <= 5)
				{
					// Créer le terme
					t = creer_terme();
					t->type_terme = Variable;
					t->contenu_terme.val = varNum;
				}
			}
		}
		// Fonction
		else if (cStr[0] == 'F')
		{
			// Créer le terme
			t = parse_fonction(item);
		}
		// Constante
		else if (isdigit(cStr[0]))
		{
			char *endptr;
			int val = (int)strtol(cStr, &endptr, 10);
			
			if (endptr && *endptr != '\0')
			{
				fprintf(stderr, "*** erreur : parse_terme() - terme de type Constante suivi de caractères inutiles.\n");
			}
			else
			{
				// Créer le terme
				t = creer_terme();
				t->type_terme = Constante;
				t->contenu_terme.val = val;
			}
		}
		else
		{
			fprintf(stderr,
					"*** erreur : parse_terme() - type de terme inconnu rencontré (commence par '%c'=0x%X dans \"%s\").\n",
					cStr[0], cStr[0], cStr);
		}
		
		return t;
	}
}


Terme parse_fonction(Text item)
{
	if (item == NULL)
	{
		fprintf(stderr, "*** erreur : parse_fonction() - argument 'item' nul invalide.\n");
		return NULL;
	}
	else if (text_contient_char(item, ' '))
	{
		fprintf(stderr, "*** erreur : parse_fonction() - argument 'item' ne doit pas contenir d'espaces.\n");
		return NULL;
	}
	else
	{
		// Forme: F(a,F(b,c))
		Terme t = NULL;
		const char *cStr = text_obtenir_texte(item);
		
		if (cStr[0] == 'F')
		{
			int fNum = cStr[1] - '0';
			
			// Ne garder que "inner" dans "Fx(inner)"
			text_retirer_prefix(item, 'F');
			text_retirer_prefix(item, '0' + fNum);
			text_retirer_prefix(item, '(');
			text_retirer_suffix(item, ')');
			//text_trim_char(item, '(');
			//text_trim_char(item, ')');
			
			if (est_fonction(Fonction+fNum))
			{
				// Traiter les arguments
				t = creer_terme();
				t->type_terme = Fonction + fNum;
				t->contenu_terme.arguments = parse_arguments(item);
				
				if (t->contenu_terme.arguments == NULL)
					destroy_terme(t), t = NULL;
			}
		}
		
		return t;
	}
}

