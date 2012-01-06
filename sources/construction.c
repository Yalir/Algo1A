/**
 * ESIL (Ecole Superieure d'Ingenieurs de Luminy, Marseille)
 * Case 925 - 163, avenue de Luminy
 * 13288 Marseille CEDEX 9
 *
 * Ce fichier est l'oeuvre d'eleves de l'ESIL. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */ 

#include <stdlib.h>
#include <assert.h>
#include <stdio.h> 
#include "Types.h"
#include "construction.h"
#include "donnees.h"

void construire_systeme(void)
{
	t = creer_systeme();
	
	// construire le premier systeme
	// X3 = 2 
	
	t->terme_gauche= creer_terme();
	t->terme_gauche->type_terme = Variable;
	t->terme_gauche->contenu_terme.val = 2;
	
	t->terme_droit = creer_terme();
	t->terme_droit->type_terme = Constante;
	t->terme_droit->contenu_terme.val= 2;
	
	// F1(X1,X2) = F1(F2(1,X2),X3)
	t->suivant = creer_systeme();
	
	// F1(X1,X2)
	t->suivant->terme_gauche = creer_terme(); 
	t->suivant->terme_gauche->type_terme = Fonction+1;
	t->suivant->terme_gauche->contenu_terme.arguments = creer_argument();
	t->suivant->terme_gauche->contenu_terme.arguments->terme_argument =creer_terme(); 
	t->suivant->terme_gauche->contenu_terme.arguments->terme_argument->type_terme = Variable;
	t->suivant->terme_gauche->contenu_terme.arguments->terme_argument->contenu_terme.val = 1; // X1
	
	
	t->suivant->terme_gauche->contenu_terme.arguments->suivant = creer_argument();
	
	// X2
	t->suivant->terme_gauche->contenu_terme.arguments->suivant->terme_argument=creer_terme(); 
	t->suivant->terme_gauche->contenu_terme.arguments->suivant->terme_argument->type_terme = Variable;
	t->suivant->terme_gauche->contenu_terme.arguments->suivant->terme_argument->contenu_terme.val= 2;
	
	
	// F1(F2(1,X2),X3)
	
	t->suivant->terme_droit = creer_terme(); 
	t->suivant->terme_droit->type_terme = Fonction+1;
	
	t->suivant->terme_droit->contenu_terme.arguments=creer_argument();
	t->suivant->terme_droit->contenu_terme.arguments->terme_argument=creer_terme();
	t->suivant->terme_droit->contenu_terme.arguments->terme_argument->type_terme = Fonction+2;
	
	
	t->suivant->terme_droit->contenu_terme.arguments->terme_argument->contenu_terme.arguments=creer_argument();
	t->suivant->terme_droit->contenu_terme.arguments->terme_argument->contenu_terme.arguments->terme_argument=creer_terme();
	t->suivant->terme_droit->contenu_terme.arguments->terme_argument->contenu_terme.arguments->terme_argument->type_terme= Constante; 
	t->suivant->terme_droit->contenu_terme.arguments->terme_argument->contenu_terme.arguments->terme_argument->contenu_terme.val=1 ; //F1(F2(1),    	   	 
	
	
	t->suivant->terme_droit->contenu_terme.arguments->terme_argument->contenu_terme.arguments->suivant=creer_argument();
	
	t->suivant->terme_droit->contenu_terme.arguments->terme_argument->contenu_terme.arguments->suivant->terme_argument=creer_terme();
	
	t->suivant->terme_droit->contenu_terme.arguments->terme_argument->contenu_terme.arguments->suivant->terme_argument->type_terme= Variable; 
	t->suivant->terme_droit->contenu_terme.arguments->terme_argument->contenu_terme.arguments->suivant->terme_argument->contenu_terme.val=2 ; //F1(F2(1,X2)
	
	t->suivant->terme_droit->contenu_terme.arguments->suivant = creer_argument();
	t->suivant->terme_droit->contenu_terme.arguments->suivant->terme_argument=creer_terme();
	t->suivant->terme_droit->contenu_terme.arguments->suivant->terme_argument->type_terme=Variable;
	
	//F1(F2(1,X2),X3)
	t->suivant->terme_droit->contenu_terme.arguments->suivant->terme_argument->contenu_terme.val=3; 
}
