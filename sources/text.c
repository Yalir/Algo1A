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
	assert(t!=NULL);
	assert(t->data!=NULL);
	
	/*unsigned i;
	for (i = 0; i < 9; i++)
		output[i]= NULL;
	*/
	
	int i,n,compteur_parenthese=0,compteur_caractere=0;
	n=strlen(t->data);
	*count =0;
	
	for(i=0;i<n; i++)
	{
		compteur_caractere++;
		
		if(t->data[i]=='(')
		{
			compteur_parenthese++;
		}
		else
		{
			if(t->data[i]==')')
			{
				compteur_parenthese--;
			}
			else
			{
				if(t->data[i]==separator)
				{
					if(compteur_parenthese ==0)
					{
						// Inserer le texte dans le tableau des textes..
						output[i]->data = &(t->data[i]);
						output[i]->length = compteur_caractere;
						t->data = &t->data[i];
						
						count++;
						compteur_caractere=0;
					}
					//Sinon on fait rien
				}
			}
		}
	}
}
