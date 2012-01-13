/**
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

/**
 * @author NAJEM Ali <ali.najem@etumel.esil.univmed.fr>
 * @author SOLTIC Lucas <lucas.soltic@etumel.esil.univmed.fr>
 *
 * @version 0.0.1 / 13-12-2011
 * @todo
 * @bug
 */


/**
 * @file resolution.h
 * @brief Contient les fonctions permettant de résoudre le système
 *
 * Description des objectifs du programme, le sujet a traiter.
 * Une trace d'execution.
 */

#ifndef RESOLUTION_H
#define RESOLUTION_H

#include "Types.h"

/** @brief Créé un système de solution à partir du système d'équations donné
 *
 * @param sys Le système d'équations à traiter
 * @return Le système de solutions trouvé ou NULL si le @a sys est insoluble
 */
Solutions traiter_systeme(Systeme sys);

void obtenir_representant(Terme u, Systeme e, Systeme *dansSolu);
void obtenir_tout_les_representants(Terme u, Systeme s, Systeme *dansSolu);

#endif

