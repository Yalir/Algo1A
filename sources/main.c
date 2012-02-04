/*
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#include <stdio.h>
#include "affichage.h"
#include "construction.h"
#include "resolution.h"
#include "donnees.h"
#include "config.h"
#include "parser.h"
#include <string.h>

/** @brief Breve description de la fonction.
 *
 * Description de la fonction (but, resultats).
 * @param par1  description du parametre.
 * @param par2  description du parametre.
 * @return	description du resultat retourne.
 */


int main (int argc, const char * argv[])
{
	Solutions s;
	Systeme t;
	
	char buffer[4096];
	int run = 1;
	
	while (run)
	{
		printf("Saisissez un système d'équations à résoudre:\n");
		
		if (fgets(buffer, 4096, stdin))
		{
			char *pos = strchr(buffer, '\n');
			
			if (pos)
				*pos = '\0';
			
			if (strlen(buffer) > 0)
			{
				t = creer_systeme_depuis_texte(buffer);
				
				if (t)
				{
					printf("Système: ");
					afficher_systeme(t);
					
					s = traiter_systeme(t);
					
					if (s)
					{
						afficher_solutions(s);
						destroy_solutions(s);
					}
					else
					{
						puts("Système insoluble ou mal écrit");
					}
					
					destroy_systeme(t);
				}
				else
				{
					puts("Erreur à la création du système");
				}
			}
			else
			{
				run = 0;
				puts("Fin du programme.");
			}
		}
		else
		{
			run = 0;
		}
	}
	
#if WINDOWS
	system("PAUSE");
#endif
    return 0;
}

