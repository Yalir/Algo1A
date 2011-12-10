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
 * @file Types.h
 * @brief Contient les structures utilisees pour la representation des systemes
 * d'equation
 *
 * Description des objectifs du programme, le sujet a traiter.
 * Une trace d'execution.
 */

#ifndef TYPES_H
#define TYPES_H

typedef struct terme_s *Terme;

typedef struct subst_s {
	Terme terme_droit;
	struct subst_s* suivant;
} *Solutions;

typedef struct equation_s {
	Terme terme_gauche;
	Terme terme_droit;
	struct equation_s* suivant;
} Equation, *Systeme;


typedef struct argument_s {
	Terme terme_argument;
	struct argument_s* suivant ;
} *Argument;

struct terme_s {
	int type_terme;
	union {
		int val;
		Argument arguments;
	} contenu_terme;
};

#endif

