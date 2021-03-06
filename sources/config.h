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
 * @file config.h
 * @brief Contient les macros permettant d'exécuter des instructions
 * uniquement sur Windows
 */
 
 #ifndef CONFIG_H
 #define CONFIG_H
 
 #if defined(_WIN32) || defined(__WIN32__)
 #define WINDOWS 1
 #endif
 
 #endif
 
