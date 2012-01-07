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
 * @file donnees.h
 * @brief Contient les instances des structures utilisees pour la representation
 * des systemes d'equation
 *
 * Description des objectifs du programme, le sujet a traiter.
 * Une trace d'execution.
 */
#ifndef DONNEES_H
#define DONNEES_H

#include "Types.h"

/** @brief Créé un nouveau système vide initialisé
 * En cas d'erreur lors de la création, le programme est stoppé
 *
 * @return Le nouveau système
 */
Systeme creer_systeme(void);


/** @brief Créé un nouveau terme vide initialisé
 * En cas d'erreur lors de la création, le programme est stoppé
 *
 * @return Le nouveau terme
 */
Terme creer_terme(void);


/** @brief Créé un nouvel argument vide initialisé
 * En cas d'erreur lors de la création, le programme est stoppé
 *
 * @return Le nouvel argument
 */
Argument creer_argument(void);


/** @brief Créé une nouvelle solution vide initialisée
 * En cas d'erreur lors de la création, le programme est stoppé
 *
 * @return La nouvelle solution
 */
Solutions creer_solutions(void);


/** @brief Détruit récursivement un système en libérant la mémoire allourée
 * @a sys doit être un système valide (non nul)
 *
 * @param sys le système à détruire
 */
void destroy_systeme(Systeme sys);


/** @brief Détruit récursivement un terme en libérant la mémoire allourée
 * @a terme doit être un terme valide (non nul)
 *
 * @param terme le terme à détruire
 */
void destroy_terme(Terme terme);


/** @brief Détruit récursivement un argument en libérant la mémoire allourée
 * @a arg doit être un argument valide (non nul)
 *
 * @param arg l'argument à détruire
 */
void destroy_argument(Argument arg);


/** @brief Détruit récursivement une solution en libérant la mémoire allourée
 * @a sol doit être une solution valide (non nul)
 *
 * @param sol la solution à détruire
 */
void destroy_solutions(Solutions sol);

#endif
