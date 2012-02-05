/*
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#include <stdio.h>
#include "test_text.h"
#include "text.h"
#include <assert.h>
#include <string.h>

void test_text(void)
{
	assert(text_creer_depuis_texte(NULL) == NULL);
	assert(text_creer_depuis_texte("a") != NULL);
	assert(text_creer_depuis_texte("") != NULL);
	assert(text_creer_depuis_texte("abcdef") != NULL);
	assert(text_obtenir_taille(text_creer_depuis_texte("abcdef")) == 6);
	assert(strcmp(text_obtenir_texte(text_creer_depuis_texte("abc")), "abc") == 0);
	
	assert(text_creer_depuis_sous_texte("abcdef",4,4) == NULL);
	assert(text_creer_depuis_sous_texte("abcdef",2,4) != NULL);
	assert(text_obtenir_taille(text_creer_depuis_sous_texte("abcdef",2,4))==4);
	assert(strcmp(text_obtenir_texte(text_creer_depuis_sous_texte("abcdef", 0, 2)), "ab") == 0);
	assert(strcmp(text_obtenir_texte(text_creer_depuis_sous_texte("abcdef", 4, 2)), "ef") == 0);
	assert(strcmp(text_obtenir_texte(text_creer_depuis_sous_texte("abcdef", 0, 6)), "abcdef") == 0);
	
	assert(text_destroy(text_creer_depuis_texte("")) == 1);
	
	assert(text_retirer_espaces(NULL) == -1);
	assert(text_retirer_espaces(text_creer_depuis_texte("abcdef")) == 1);
	Text t0 = text_creer_depuis_texte("    er ff d   grg ");
	text_retirer_espaces(t0);
	assert(strcmp(text_obtenir_texte(t0), "erffdgrg") == 0);
	
	assert(text_obtenir_texte(NULL) == NULL);
	assert(text_obtenir_texte(text_creer_depuis_texte("")) != NULL);
	
	unsigned int c;
	Text *tt;
	assert(text_decoupe_premier_niveau(text_creer_depuis_texte(""), ' ', NULL, &c) == -1);
	assert(text_decoupe_premier_niveau(text_creer_depuis_texte(""), ' ', &tt, NULL) == -1);
	assert(text_decoupe_premier_niveau(NULL, ' ', &tt, &c) == -1);
	
	Text *output1;
	unsigned count1;
	assert(text_decoupe_premier_niveau(text_creer_depuis_texte("ab,cd,ef"),',',&output1,&count1) == 1);
	assert(count1 == 3);
	assert(strcmp(text_obtenir_texte(output1[0]), "ab") == 0);
	assert(strcmp(text_obtenir_texte(output1[1]), "cd") == 0);
	assert(strcmp(text_obtenir_texte(output1[2]), "ef") == 0);
	
	Text *output2;
	unsigned count2;
	assert(text_decoupe_premier_niveau(text_creer_depuis_texte("f1(x1,x2)=f1(f2(f3(x3))),f4(x4,x5)=f4(f5(x5)),x3=x4"),',',&output2,&count2) == 1);
	assert(count2 == 3);
	assert(strcmp(text_obtenir_texte(output2[0]), "f1(x1,x2)=f1(f2(f3(x3)))") == 0);
	assert(strcmp(text_obtenir_texte(output2[1]), "f4(x4,x5)=f4(f5(x5))") == 0);
	assert(strcmp(text_obtenir_texte(output2[2]), "x3=x4") == 0);

	Text *output3;
	unsigned count3;
	assert(text_decoupe_premier_niveau(text_creer_depuis_texte("f1=f2"),',',&output3,&count3) == 1);
	assert(count3 == 1);
	assert(strcmp(text_obtenir_texte(output3[0]), "f1=f2") == 0);
	
	Text *output4;
	unsigned count4;
	text_decoupe_premier_niveau(text_creer_depuis_texte("99,11,22"), ',', &output4, &count4);
	assert(count4 == 3);
	assert(output4[0] != NULL);
	assert(output4[1] != NULL);
	assert(output4[2] != NULL);
	
	assert(strcmp(text_obtenir_texte(output4[0]), "99") == 0);
	assert(strcmp(text_obtenir_texte(output4[1]), "11") == 0);
	assert(strcmp(text_obtenir_texte(output4[2]), "22") == 0);
	
	assert(text_contient_char(NULL,' ')==-1);
	assert(text_contient_char(text_creer_depuis_texte("ab,cd,ef"),' ')==0);
	assert(text_contient_char(text_creer_depuis_texte("ab ,cd,ef"),' ')==1);
	
	assert(text_trim_char(NULL,' ')==-1);
	Text t1 ; 
	t1 = text_creer_depuis_texte("       ab ,cd,ef     ");
	assert(text_trim_char(t1,' ')==1);
	//printf("'%s'\n",text_obtenir_texte(t1));
	assert(strcmp(text_obtenir_texte(t1), "ab ,cd,ef")== 0);

	
	assert(text_retirer_prefix(NULL,' ')==-1);
	Text t2 ; 
	t2 = text_creer_depuis_texte("        ab, cd , ef");
	assert(text_retirer_prefix(t2,' ')==1);
	//printf("'%s'\n",text_obtenir_texte(t2));
	assert(strcmp(text_obtenir_texte(t2), "       ab, cd , ef")== 0);
	
	assert(text_retirer_suffix(text_creer_depuis_texte("ab"), 'b') == 1);
	assert(text_retirer_suffix(text_creer_depuis_texte("ab"), 'a') == -1);
	
	Text t3 = text_creer_depuis_texte("abc");
	text_retirer_suffix(t3, 'c');
	assert(strcmp("ab", text_obtenir_texte(t3)) == 0);
	
}
