/*
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

#include "types.h"


/** @brief Affiche l'ensemble du système d'équations
 * Le système donné doit être valide sous peine d'affichage d'erreur.
 *
 * @param sys le système d'équation à afficher
 */
void afficher_systeme(const Systeme sys);


/** @brief Affiche un terme
 * Le terme donné doit être valide sous peine d'affichage d'erreur.
 *
 * @param terme Le terme à afficher
 */
void afficher_terme(const Terme terme);


/** @brief Affiche un argument
 * L'argument donné doit être valide sous peine d'affichage d'erreur.
 *
 * @param arg L'argument à afficher
 */
void afficher_argument(const Argument arg);


/** @brief Affiche l'ensemble des solutions trouvées
 *
 * @param s Le système de solutions à afficher
 */
void afficher_solutions(const Solutions s);


#endif
