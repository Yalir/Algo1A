/*
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#ifndef PARSER_H
#define PARSER_H

#include "types.h"
#include "text.h"

/** Créé un système d'équations à partir du texte donné
 * 
 * @param input Le texte à évaluer
 * @return Le système généré à partir du texte, ou NULL si une erreur
 * est survenue
 */
Systeme creer_systeme_depuis_texte(const char *input);


/** @brief Traite une équation de la forme "...=..." contenue dans @a item.
 * La fonction considère que @a item ne contient aucun espace.
 *
 * @param item Le Text d'où doit être extrait l'équation
 * @return L'équation générée à partir du Text @a item,
 * ou NULL si une erreur est survenue
 */
Equation *parse_equation(Text item);


/** @brief Traite une liste d'arguments de la forme "a,F(b,c),4"
 * contenue dans @a item.
 * La fonction considère que @a item ne contient aucun espace.
 *
 * @param item Le Text d'où doit être extrait la liste d'arguments
 * @return La liste d'arguments générée à partir du Text @a item,
 * ou NULL si une erreur est survenue
 */
Argument parse_arguments(Text item);


/** @brief Traite un terme de la forme "a" ou "F(b,c)" ou "4" contenu dans @a item.
 * La fonction considère que @a item ne contient aucun espace.
 *
 * @param item Le Text d'où doit être extrait le terme
 * @return Le terme généré à partir du Text @a item,
 * ou NULL si une erreur est survenue
 */
Terme parse_terme(Text item);


/** @brief Traite une fonction de la forme "F(a,F(b,c))" contenue dans @a item.
 * La fonction considère que @a item ne contient aucun espace.
 *
 * @param item Le Text d'où doit être extraite la fonction
 * @return La fonction générée à partir du Text @a item,
 * ou NULL si une erreur est survenue
 */
Terme parse_fonction(Text item);

#endif
