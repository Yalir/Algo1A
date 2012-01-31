/*
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


Text text_creer_depuis_sous_texte(const char *string, unsigned pos, unsigned length)
{
	assert(string!=NULL);
	Text texte = (Text)malloc(sizeof(*texte));
	int n,i;
	if (texte == NULL)
	{
		fprintf(stderr, "malloc error\n");
		abort();
	}
	else
	{
		n = strlen(string);
		if(pos >=n)
		{
			fprintf(stderr, "*** error: text_creer_depuis_sous_texte() - La position que vous avez choisie est supérieure à la longueure de la chaine (length=%u, pos=%u).\n",
				n, pos);
			abort();
		}
		if(pos+length >=n)
		{
			fprintf(stderr, "*** error: text_creer_depuis_sous_texte() - La longueur de la chaine que vous aimeriez avoir depasse la chaine (pos+lenght= %u , n = %u)\n",
				pos+length,n);
			abort();
		}
		else
		{
			texte->data = (char*)malloc(sizeof(char)*length+1);
			for(i=0;i<length;i++)
			{
				texte->data[i]=string[i+pos];
			}
			texte->data[length]='\0';
			
			texte->length = length+1;
			return texte;
		}
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
					textArray[textCount-1] = text_creer_depuis_sous_texte(text_obtenir_texte(t),
																i - compteur_caractere+1,
																compteur_caractere-1);
				}
				else
				{
					fprintf(stderr, "*** error: texte_decoupe_premier_niveau() - no more memory available.\n");
					abort();
				}
				
				compteur_caractere=0;
			}
			//Sinon on fait rien
		}
		
	}

	if(compteur_caractere > 0)
	{
		// Inserer le texte dans le tableau des textes..
		textCount++;
		void *tmp = realloc(textArray, textCount * sizeof(*textArray));
		
		if (tmp)
		{
			textArray = tmp;
			textArray[textCount-1] = text_creer_depuis_sous_texte(text_obtenir_texte(t),
														i - compteur_caractere+1,
														compteur_caractere);
		}
		else
		{
			fprintf(stderr, "*** error: texte_decoupe_premier_niveau() - no more memory available.\n");
			abort();
		}
	}			

		
		
	*output = textArray;
	*count = textCount;
}


int text_contient_char(const Text t, char chr)
{
	assert(t!=NULL);
	assert(t->data!=NULL);
	int i=0,n =text_obtenir_taille(t);
	
	while(t->data[i]!=chr && i<n)
	{
		i++;
	}
	//si l'element n'a pas été trouvé
	if(i==n)
	{
		return -1;
	}
	// else
	return 1;
}


void text_trim_char(Text t, char chr)
{
	assert(t!=NULL);
	assert(t->data!=NULL);
	
	int i,j,n,k;
	i=0;
	n=text_obtenir_taille(t);
	k=n;
	
	while(t->data[i]==chr && i<n)
	{
		for(j=i;j<n-1;j++)
		{
			t->data[j]=t->data[j+1];
		}
		i++;
	}
	while((t->data[k]==chr) && (k>=i))
	{
		for(j=k;j>=i;j--)
		{
			t->data[j]='\0';
		}
		k--;
	}
}


void text_retirer_prefix(Text t, char chr)
{
	assert(t!=NULL);
	assert(t->data!=NULL);
	int i,j,n;
	
	n=text_obtenir_taille(t);
	if(text_contient_char(t,chr)==1)
	{
		for(i=0;i<n;i++)
		{
			if(t->data[i]==chr)
			{
				for(j=i;j<n-1;j++)
				{
					t->data[j]=t->data[j+1];
				}
			}
		}
	}
}
