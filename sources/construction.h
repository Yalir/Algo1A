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
 * @file construction.h
 * @brief Contient les fonctions permettant de construire la structure du
 * système à résoudre
 */

#ifndef CONSTRUCTION_H
#define CONSTRUCTION_H

#include "types.h"


/** @brief cette fonction construit manuellement un système d'équations à résoudre 
 *
 * @return Le nouveau système d'équations
 */
Systeme construire_systeme(void);

#endif

