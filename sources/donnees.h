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
 * @file donnees.h
 * @brief Contient les instances des structures utilisees pour la representation
 * des systemes d'equation
 *
 * Description des objectifs du programme, le sujet a traiter.
 * Une trace d'execution.
 */
#ifndef DONNEES_H
#define DONNEES_H

#include "types.h"

/** @brief Créé un nouveau système vide initialisé
 * En cas d'erreur lors de la création, le programme est stoppé
 *
 * @return Le nouveau système
 */
Systeme creer_systeme(void);


/** @brief Créé une nouvelle équation vide initialisée
 * En cas d'erreur lors de la création, le programme est stoppé
 *
 * @return La nouvelle équation
 */
Equation *creer_equation(void);


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


/** @brief Alloue @a n-1 maillons pour pouvoir stocker les solutions
 * @a s doit être un système valide (non nul) sous peine d'arrêt du programme
 *
 * @param s Le système de solutions à initialiser
 * @param n Le nombre de solutions que doit pouvoir contenir @a s
 */
void initialiser_solutions(Solutions s, unsigned n);


/** @brief Créé une copie de l'équation donnée
 * L'équation donnée doit être valide (non nulle) sous peine d'arrêt
 * du programme
 *
 * @param e Une équation valide à recopier
 * @return Une copie de l'équation d'origine
 */
Equation *copie_equation(const Equation *e);


/** @brief Créé une copie du terme donné
 * Le terme donne doit être valide (non nul) sous peine d'arrêt
 * du programme
 *
 * @param e Un terme valide à recopier
 * @return Une copie du terme d'origine
 */
Terme copie_terme(const Terme t);


/** @brief Créé une copie de l'argument donné
 * L'argument donné doit être valide (non nul) sous peine d'arrêt
 * du programme
 *
 * @param e Un argument valide à recopier
 * @return Une copie de l'argument d'origine
 */
Argument copie_argument(const Argument arg);


/** @brief Détruit récursivement un système en libérant la mémoire allourée
 * @a sys doit être un système valide (non nul)
 *
 * @param sys le système à détruire
 */
void destroy_systeme(Systeme sys);


/** @brief Détruit récursivement une équation en libérant la mémoire allourée
 * @a e doit être une équation valide (non nul)
 *
 * @param e l'équation à détruire
 */
void destroy_equation(Equation *e);


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
