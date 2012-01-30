/**
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#include "text.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>


struct Text {
	char *data;
	unsigned length;
};


unsigned text_obtenir_taille(const Text t)
{
	assert(t != NULL);
	return t->length;
}

Text text_creer_depuis_texte(const char *string)
{
	assert(string != NULL);
	Text texte = (Text)malloc(sizeof(*texte));
	if (texte == NULL)
	{
		fprintf(stderr, "malloc error\n");
		abort();
	}
	else
	{
		texte->data = strdup(string);
		texte->length = strlen(string);
		return texte;
	} 
}


Text text_creer_depuis_sous_texte(const char *string, unsigned pos, unsigned length);

void text_destroy(Text t)
{
	assert(t!=NULL);
	free (t->data);
	free (t);
}

const char *text_obtenir_texte(const Text t)
{
	assert(t!=NULL);
	assert(t->data!=NULL);
	return t->data;
}

void text_retirer_espaces(Text t)
{	
	assert(t!=NULL);
	assert(t->data!=NULL);
	
	int j,i,n;
	
	n=strlen(t->data);

	for(i=0;i<n;i++)
	{
		if(t->data[i]==' ')
		{
			for(j=i;j<n;j++)
			{
				t->data[j]=t->data[j+1];
			}
		}
	}
}

void text_decoupe_premier_niveau(const Text t, char separator, Text **output, unsigned *count)
{
	assert(t != NULL);
	assert(t->data != NULL);
	assert(output != NULL);
	assert(count != NULL);
	
	Text *textArray = NULL;
	unsigned textCount = 0;
	const char *cursor = t->data;
	
	int i, n;
	int compteur_parenthese = 0;
	int compteur_caractere = 0;
	
	n = text_obtenir_taille(t);
	
	for (i = 0;i < n;i++)
	{
		compteur_caractere++;
		
		if (cursor[i] == '(')
		{
			compteur_parenthese++;
		}
		else if(cursor[i] == ')')
		{
			compteur_parenthese--;
		}
		else if(cursor[i] == separator)
		{
			if(compteur_parenthese == 0)
			{
				// Inserer le texte dans le tableau des textes..
				textCount++;
				void *tmp = realloc(textArray, textCount * sizeof(*textArray));
				
				if (tmp)
				{
					textArray = tmp;
					textArray[i] = text_creer_depuis_sous_texte(text_obtenir_texte(t),
																i - compteur_caractere,
																compteur_caractere);
				}
				else
				{
					fprintf(stderr, "*** error: texte_decoupe_premier_niveau() - no more memory available.\n");
					abort();
				}
				
				textCount++;
				compteur_caractere=0;
			}
			//Sinon on fait rien
		}
	}
	
	*output = textArray;
	*count = textCount;
}
