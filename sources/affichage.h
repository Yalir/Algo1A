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


/** @brief cette fonction affiche le système à l'utilisateur qui fait des appels 
 * 		   recursivement la fonction afficher_terme() tant qu'il y'a des equation à afficher 
 *
 * @param un pointeur sur la première equation
 */
void afficher_systeme(Systeme sys);


/** @brief cette fonction affiche tout simplement un terme de l'equation (la constante ou la variable ou la fonction)
 *
 * @param le pointeur qui pointe sur le terme à afficher
 */
void afficher_terme(Terme terme);


/** @brief cette fonction affiche tout simplement un argument d'une fonction
 *
 * @param le pointeur qui pointe sur l'argument à afficher
 */
void afficher_argument(Argument arg);


#endif
