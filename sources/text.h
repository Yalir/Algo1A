/**
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#ifndef TEXT_H
#define TEXT_H

typedef struct Text* Text;

/** @brief Créé un nouveau Text
 *
 * @param string Une chaîne C à importer
 * @return Un nouveau Text
 */
Text text_creer_depuis_texte(const char *string);

/** @brief Libère la mémoire du Text @a t
 * @param t Le Text à détruire
 */
void text_destroy(Text t);

/** @brief Récupère la chaîne de caractère C du Text @a t
 *
 * @param t Le Text depuis lequel est récupérée la chaîne de caractères
 * @return La chaîne de caractère C du Text
 */
const char *text_obtenir_texte(Text t);

/** @brief Donne la taille du Text @a t en nombre de caractères
 *
 * @return Le nombre de caractères de @a t
 */
unsigned text_obtenir_taille(Text t);

/** @brief Retire les espaces en début et fin du Text @a t
 *
 * @param t Le Text qui doit être élagué
 */
void text_trim_espaces(Text t);

/** @brief Génère une liste de Text à partir du Text t, d'après le séparateur ","
 * Seuls les éléments de premier niveau sont découpées. Un niveau est défini par
 * des parenthèses.
 * Le Text "F(a,b),c,d" donne donc la liste {"F(a,b)", "c", "d"}.
 *
 * @param t Le Text d'où doivent être extraits les sous-textes
 * @param output Une référence sur un tableau dynamique de Text qui contiendra
 * la liste des Text extraits de @a t
 * @param count Une référence sur un entier qui contiendra le nombre d'éléments
 * extraits du Text @a t
 */
void text_decoupe_premier_niveau(Text t, Text **output, unsigned *count);

#endif
