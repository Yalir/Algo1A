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

#include "types.h"

typedef enum {
	ResolutionErrNone = 0,
	ResolutionErrImpossible = -1
} ResolutionErr;

/** @brief Créé un système de solution à partir du système d'équations donné
 * @a sys doit être un système valide (non nul)
 * @a sys peut être étendu au cours du traitement
 *
 * @param sys Le système d'équations à traiter (et étendre si besoin)
 * @param err Une référence sur un entier contenant le code d'erreur ayant arrêté
 * le traitement (cf. ResolutionErr)
 * @return Le système de solutions trouvé ou NULL si le @a sys est insoluble
 */
Solutions traiter_systeme(Systeme sys, ResolutionErr *err);


/** @brief Résout une équation et met à jour l'ensemble des solutions
 * @a s et @a e doivent être des objets valides
 * @a dansSys doit être une référence sur référence d'équation non allouée
 * @a dansSolu doit être une référence sur référence d'équation non allouée
 *
 * @param s L'ensemble des solutions trouvées jusqu'à maintenant
 * @param e L'équation à traiter
 * @param dansSys Une référence sur une référence d'équation non allouée
 * @param dansSolu Une référence sur une référence d'équation non allouée
 *
 * @return 0 si l'équation a pu être traitée, -1 si l'équation rend le système
 * insoluble
 */
int traiter_equation(const Solutions s, const Equation *e, Equation **dansSys, Equation **dansSolu);


/** @brief Vérifie si le terme @a conteneur fait référence au terme @a t
 * @a conteneur et @a t doivent être des termes valides (non nuls) sous peine
 * d'arrêt du programme. @a t doit être une variable.
 *
 * @param conteneur Le terme dans lequel on cherche la référence au terme @a t
 * @param t Le terme à rechercher dans le @a conteneur
 * @return 1 si le terme @a t a été trouvé dans le terme @a conteneur, 0 sinon
 */
int contient_terme(const Terme conteneur, const Terme t);

/** @brief Créé un ensemble d'équation à partir des deux fonctions
 * en faisant la correspondance entre les paramètres:
 * f1(a, b, c) = f2(d, e, f) => {a = d, b = e, c = f}
 * @a fgauche et @a fdroit doivent être des fonctions valides (non nuls)
 * sous peine d'arrêt du programme.
 *
 * @param fgauche La fonction gauche de l'équation
 * @param fdroit La fonction droite de l'équation
 * @return Une liste chaînée des équations générées ou NULL si le nombre
 * de paramètres ne correspond pas
 */
Equation *decapsuler_fonctions(const Terme fgauche, const Terme fdroit);


/** @brief Compte le nombre de paramètres de la fonction @a t
 * 
 * @a t doit être une fonction valide (terme non nul) sous peine d'arrêt
 * du programme
 *
 * @param t La fonction dont on veut compter le nombre de paramètres
 * @return Le nombre d'arguments de la fonction @a t
 */
int compter_arguments(const Terme t);


/** @brief Donne le numéro de la fonction @a t
 *
 * @param t Le terme représentant une fonction
 * @return -1 si le @a t est nul ou pas une fonction, l'id de la fonction sinon
 */
int id_fonction(Terme t);


/** @brief Insère l'équation e dans le système des solutions @a s
 * @a s et @a e doivent être des objets valides (non nuls) sous peine
 * d'arrêt du programme
 *
 * @param s Le système dans lequel seront rangées les solutions
 * @param e L'équation à ranger
 */
void ranger_solutions(Solutions s, const Equation *e);

#endif

