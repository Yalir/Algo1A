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
 * @file reprensentant.h
 * @brief Contient les fonctions permettant d'obtenir les representants d'une equation
 *
 * Description des objectifs du programme, le sujet a traiter.
 * Une trace d'execution.
 */

#ifndef REPRESENTANT_H
#define REPRESENTANT_H

#include "Types.h"


/** @brief fonction qui retourne le reprensentant d'un terme
 *
 * @param Un terme valide et le systeme de solution
 * @return Le reprensentant d'un terme
 */
Terme obtenir_representant_terme(const Terme u,const Systeme s);


/** @brief fonction qui retourne la nouvelle equation en remplaçant les termes (gauche et droit) par leurs representants
 *
 * @param Une equation et le systeme de solution
 * @return La nouvelle equation d'un terme
 */
 
Equation* obtenir_representant_equation(const Equation *e,const Systeme s);

#endif

