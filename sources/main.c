

#include <stdio.h>
#include "affichage.h"
#include "construction.h"
#include "resolution.h"
#include "config.h"

/** @brief Breve description de la fonction.
 *
 * Description de la fonction (but, resultats).
 * @param par1  description du parametre.
 * @param par2  description du parametre.
 * @return	description du resultat retourne.
 */


int main (int argc, const char * argv[])
{
	construire_systeme();
	traiter_systeme();
	afficher_solutions();
	
#if WINDOWS
	system("PAUSE");
#endif
    return 0;
}

