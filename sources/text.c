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
#include <ctype.h>


struct Text {
	char *data;
	size_t length;
};


unsigned text_obtenir_taille(const Text t)
{
	if(t == NULL)
	{
		fprintf(stderr,"*** erreur :text_obtenir_taille() - Le paramètre 't' ne devrait jamais être nul.\n");
		return 0;
	}
	else
	{
		return (unsigned)t->length;
	}
}


Text text_creer_depuis_texte(const char *string)
{
	if(string == NULL)
	{
		fprintf(stderr,"*** erreur :text_creer_depuis_texte() - Le paramètre 'string' ne devrait jamais être nul.\n");
		return NULL;
	}
	else
	{	
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
}


Text text_creer_depuis_sous_texte(const char *string, unsigned pos, unsigned length)
{
	if(string == NULL)
	{
		fprintf(stderr,"*** erreur :text_creer_depuis_sous_texte() - Le paramètre 'string' ne devrait jamais être nul.\n");
		return NULL;
	}
	else
	{			
		Text texte = (Text)malloc(sizeof(*texte));
		size_t n, i;
		
		if (texte == NULL)
		{
			fprintf(stderr, "malloc error\n");
			abort();
		}
		else
		{
			n = strlen(string);
			if(pos >n)
			{
				fprintf(stderr, "*** erreur: text_creer_depuis_sous_texte() - La position que vous avez choisie est supérieure à la longueure de la chaine (length=%lu, pos=%u).\n",
					n, pos);
				return NULL;
			}
			if(pos+length >n)
			{
				fprintf(stderr, "lenght= %u , n = %lu)\n",
					length,n);
				fprintf(stderr, "*** erreur: text_creer_depuis_sous_texte() - La longueur de la chaine que vous aimeriez avoir depasse la chaine (pos(%u) + lenght(%u) = %u, n = %lu)\n",
					pos,length, pos+length, n);
					return NULL;
			}
			else
			{
				texte->data = (char*)malloc(sizeof(char)*length+1);
				for(i=0;i<length;i++)
				{
					texte->data[i]=string[i+pos];
				}
				texte->data[length]='\0';
				
				texte->length = length;
			}
		}
		return texte;
	}
}


int text_destroy(Text t)
{
	if(t == NULL)
	{
		fprintf(stderr,"*** erreur :text_destroy() - Le paramètre 't' ne devrait jamais être nul.\n");
		return -1;
	}
	else
	{	
		free (t->data);
		free (t);
		return 1;
	}
}


const char *text_obtenir_texte(const Text t)
{	
	if(t == NULL)
	{
		fprintf(stderr,"*** erreur :text_obtenir_texte() - Le paramètre 't' ne devrait jamais être nul.\n");
		return NULL;
	}
	else
	{
		if(t->data == NULL)
		{
			fprintf(stderr,"*** erreur :text_obtenir_texte() - Il n'y a pas des données dans le texte.\n");
			return NULL;
		}
		else
		{
			return t->data;
		}
	}
}


int text_retirer_espaces(Text t)
{	
	if(t == NULL)
	{
		fprintf(stderr,"*** erreur :text_retirer_prefix() - Le paramètre 't' ne devrait jamais être nul.\n");
		return -1;
	}
	else
	{
		if(t->data == NULL)
		{
			fprintf(stderr,"*** erreur :text_retirer_prefix() - Il n'y a pas de données dans le texte.\n");
			return -1;
		}
		else
		{
			int i,j,n;
			
			n=text_obtenir_taille(t);
			// On teste si le texte contient bien le caractère chr ,pour ne pas parcourir les boucles pour rien.
			if(text_contient_char(t,' ')==1)
			{
				for(i=0;i<n;i++)
				{
					while(t->data[i]==' ')
					{
						// La boucle qui décale tous les caractères qui sont apres l'indice i vers la gauche
						for(j=i;j<n-1;j++)
						{
							t->data[j]=t->data[j+1];
						}
						t->data[j]='\0';
						n=n-1;
					}
					
				}
			}
			t->length=n;
			return 1;
		}
	}
}


int text_decoupe_premier_niveau(const Text t, char separator, Text **output, unsigned *count)
{	
	if(t == NULL)
	{
		fprintf(stderr,"*** erreur :text_decoupe_premier_niveau() - Le paramètre 't' ne devrait jamais être nul.\n");
		return -1;
	}
	else if(output == NULL)
	{
		fprintf(stderr,"*** erreur :text_decoupe_premier_niveau() - Le paramètre 'output' ne devrait jamais être nul.\n");
		return -1;
	}
	
	
	else if(count == NULL)
	{
		fprintf(stderr,"*** erreur :text_decoupe_premier_niveau() - Le paramètre 'count' ne devrait jamais être nul.\n");
		return -1;
	}
	
	else if(t->data == NULL)
	{
		fprintf(stderr,"*** erreur :text_decoupe_premier_niveau() - Il n'y a pas des données dans le texte.\n");
		return -1;
	}
	
	else
	{
		Text *textArray = NULL;
		
		unsigned position_apres_derniere_virgule = 0;
		unsigned taille_derniere_chaine = 0;
		
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
			else if(compteur_parenthese == 0)
			{
				if(cursor[i] == separator)
				{
					// Inserer le texte dans le tableau des textes..
					textCount++;
					void *tmp = realloc(textArray, textCount * sizeof(*textArray));
					
					if (tmp)
					{
						position_apres_derniere_virgule = i+1;
						textArray = tmp;
						textArray[textCount-1] = text_creer_depuis_sous_texte(text_obtenir_texte(t),
																	i - compteur_caractere+1,
																	compteur_caractere-1);
					}
					else
					{
						fprintf(stderr, "*** error: texte_decoupe_premier_niveau() - no more memory available.\n");
						return -1;
					}
					
					compteur_caractere=0;
				}
				//Sinon on fait rien
			}
			
		}
				
		if(position_apres_derniere_virgule > 0)
		{
			// Inserer le texte dans le tableau des textes..
			textCount++;
			void *tmp = realloc(textArray, textCount * sizeof(*textArray));
			
			if (tmp)
			{

				textArray = tmp;
				/*
				printf("textCount-1 =%d\n",textCount-1);
				printf("i =%d\n",i);
				printf("position_apres_derniere_virgule =%d\n",position_apres_derniere_virgule);
				printf("i - compteur_caractere+1 =%d\n",i - compteur_caractere+1);
				printf("compteur_caractere =%d\n",compteur_caractere);
				*/
				// on calcule la taille de la derniere chaine
				taille_derniere_chaine = text_obtenir_taille(t)-position_apres_derniere_virgule;
				//printf("taille_derniere_chaine =%d\n",taille_derniere_chaine);
				
				
				textArray[textCount-1] = text_creer_depuis_sous_texte(text_obtenir_texte(t),
															position_apres_derniere_virgule,
															taille_derniere_chaine);
			
			}
			else
			{
				fprintf(stderr, "*** error: texte_decoupe_premier_niveau() - no more memory available.\n");
				return -1;
			}
			
		}
		else
		{
			// c'est le cas où on a pas un separateur à l'exterieur des parenthèses.
			// Inserer le texte dans le tableau des textes..
			textCount++;
			void *tmp = realloc(textArray, textCount * sizeof(*textArray));
			
			if (tmp)
			{

				textArray = tmp;	
				textArray[0] =  text_creer_depuis_sous_texte(text_obtenir_texte(t),
															position_apres_derniere_virgule,
															t->length);
			}
			else
			{
				fprintf(stderr, "*** error: texte_decoupe_premier_niveau() - no more memory available.\n");
				return -1;
			}
			
		}	
			
		*output = textArray;
		*count = textCount;
			
	}
	return 1;
}


int text_contient_char(const Text t, char chr)
{
	if(t == NULL)
	{
		fprintf(stderr,"*** erreur :text_retirer_espaces() - Le paramètre 't' ne devrait jamais être nul.\n");
		return -1;
	}
	else
	{
		if(t->data == NULL)
		{
			fprintf(stderr,"*** erreur :text_retirer_espaces() - Il n'y a pas de données dans le texte.\n");
			return -1;
		}
		else
		{
				
			if (strchr(t->data, chr) != NULL)
				return 1;
			else
				return 0;
		}
	}
}


int text_trim_char(Text t, char chr)
{
	if(t == NULL)
	{
		fprintf(stderr,"*** erreur :text_retirer_espaces() - Le paramètre 't' ne devrait jamais être nul.\n");
		return -1;
	}
	else
	{
		if(t->data == NULL)
		{
			fprintf(stderr,"*** erreur :text_retirer_espaces() - Il n'y a pas de données dans le texte.\n");
			return -1;
		}
		else
		{		
			int j,n;
			n=text_obtenir_taille(t);
			
			//Boucle pour tester si le premier caractère et le supprimer si c'est le cas
			//on teste le premier caractère de la chaine
			while(t->data[0]==chr)
			{
				if(n==0 || n==1)
				{
					t->data=strdup(""); // on retourne une chaine vide;
				}
				else
				{
					for(j=0;j<n-1;j++)
					{
						t->data[j]=t->data[j+1];
					}
					t->data[j]='\0';
					n=n-1; // pour regler la longueure de la chaine
				}
			}
			
			//Boucle pour tester si le dernier caractère et le supprimer si c'est le cas
			//on teste le dernier caractère de la chaine
			while(t->data[n-1]==chr)
			{	
				if(n==0 || n==1)
				{
					t->data=strdup(""); // on retourne une chaine vide;
				}
				else
				{			
					t->data[n-1]='\0';
					n=n-1;
				}
			}
			
			t->length=n ;// pour regler la longueure de la chaine;
			return 1;
		}
	}
}


int text_retirer_prefix(Text t, char chr)
{
	if(t == NULL)
	{
		fprintf(stderr,"*** erreur :text_retirer_espaces() - Le paramètre 't' ne devrait jamais être nul.\n");
		return -1;
	}
	else
	{
		if(t->data == NULL)
		{
			fprintf(stderr,"*** erreur :text_retirer_espaces() - Il n'y a pas de données dans le texte.\n");
			return -1;
		}
		else
		{
			int j,n;
			
			//Boucle pour tester si le premier caractère et le supprimer si c'est le cas
			//on teste le premier caractère de la chaine
			if(t->data[0]==chr)
			{	
				n=text_obtenir_taille(t);
				if(n==0 || n==1)
				{
					t->data=strdup(""); // on retourne une chaine vide;
				}
				else
				{
					for(j=0;j<n-1;j++)
					{
						t->data[j]=t->data[j+1];
					}
					t->data[j]='\0';
					n=n-1; // pour regler la longueure de la chaine
				}
			t->length=n ;// pour regler la longueure de la chaine;
			}
			return 1;	

		}
	}
}


int text_en_maj(Text t)
{
	int res = -1;
	
	if (t)
	{
		size_t taille = text_obtenir_taille(t);
		if (taille > 0)
		{
			size_t i;
			for (i = 0; i < taille;i++)
				t->data[i] = toupper(t->data[i]);
			
			res = 1;
		}
	}
	
	return res;
}

