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
 * @version 0.0.1 / 10-12-2011
 * @todo
 * @bug
 */


/**
 * @file affichage.h
 * @brief Contient les fonctions permettant l'affichage du systeme et des
 * solutions
 *
 * Description des objectifs du programme, le sujet a traiter.
 * Une trace d'execution.
 */

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "Types.h"

void afficher_solutions(Solutions s);
void afficher_systeme(Systeme sys);
void afficher_terme(Terme terme);
void afficher_argument(Argument arg);


#endif
