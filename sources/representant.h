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


Terme obtenir_representant_terme(Terme u, Systeme s);


/** @brief Créé un nouvel argument vide initialisé
 * En cas d'erreur lors de la création, le programme est stoppé
 *
 * @return Le nouvel argument
 */
 
Equation* obtenir_representant_equation(Equation *e, Systeme s);

#endif

