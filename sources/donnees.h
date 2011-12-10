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

extern Solutions s;
extern Systeme t;

void init_solutions(void);
void init_systeme(void);

void destroy_solutions(Solutions sol);
void destroy_systeme(Systeme sys);
void destroy_terme(Terme terme);
void destroy_argument(Argument arg);

#endif
