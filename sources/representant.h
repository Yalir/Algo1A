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
 */


/**
 * @file representant.h
 * @brief Contient les fonctions permettant d'obtenir les representants d'une equation
 *
 */

#ifndef REPRESENTANT_H
#define REPRESENTANT_H

#include "types.h"


/** @brief fonction qui retourne le reprensentant d'un terme
 *
 * @param Un terme valide et le systeme de solution
 * @return Le reprensentant d'un terme s'il n'y a pas eu d'erreurs et NULL sinon (si u ou s sont nul)
 */
Terme obtenir_representant_terme(const Terme u,const Solutions s);


/** @brief fonction qui retourne la nouvelle equation en remplaçant les termes (gauche et droit) par leurs representants
 *
 * @param Une equation et le systeme de solution
 * @return La nouvelle equation d'un terme s'il n'y a pas eu d'erreurs et NULL sinon (si e ou s sont nul)
 */
 
Equation* obtenir_representant_equation(const Equation *e,const Solutions s);

#endif

