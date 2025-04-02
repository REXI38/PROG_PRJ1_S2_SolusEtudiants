//-----------------------------------------------------------------------------------//
// Nom du projet 		: Projet 2 - Calculs Trigo
// Nom du fichier 		: mainProjet1_s2.c
// Date de création 	: 21.10.2022
// Date de modification : 14.02.2024
//
// Auteur 				: Philou (Ph. Bovey)
// 
// Modification			: LCX
// 
// Description          : 
//
// Remarques			: voir donnee de l'épreuve            
//----------------------------------------------------------------------------------//
//-- directive préprocesseur pour supprimer certains warining --//
#pragma warning(disable : 4996)		//-- warning concernant les scanf

//--- librairie standart ---//
#include <stdio.h>                  // entrée - sortie
#include <stdlib.h>					// fonctions système 

//--- librairie perso ---//
#include "CalculTrigo.h"

//-- déclaration de constantes --// 
const char* ptNOM_CANDIDAT = "Louis Cardinaux"; 
const char VERSION_PROJET = 1; 
const unsigned short ANNEE_TEST = 2025; 


//-- programme principal --// 
void main()
{
	//-- déclaration de variables locales --//
	//-- enumération 
	e_choixCoteAngle choix_C_A;
	e_choixCote choix_AHC;
	e_choixAngle choix_AB; 
	e_validation testFct = nok; 

	//-- type primaire 
	char nbChoix = 0; 
	char longueurSegment; 
	float angle_deg; 

	//-- variable structure
	str_triangleRectangle triangle;

	//test
	
	//InitialiserStructure(&triangle);

	//-- message utilisateur --// 
	printf("-- TEST n%02d - annee : %d - Nom Candidat : %s --\n", VERSION_PROJET, ANNEE_TEST, ptNOM_CANDIDAT); 

	//-- msg -> taille structure --// 
	printf("\n-> taille en memoire de la structure triangle : %d[o] \n", (int)sizeof(triangle) );
	
	//-- initialisation de la structure --//
	testFct = InitialiserStructure(&triangle);
	
	//-- msg user & selection valeur --// 
	//-- itération -> max 2 choix possible 
	while ((testFct == ok) && (nbChoix < NB_CHOIX_MAX))
	{
		printf("\n=> choix de selection entrez : 0 -> pour cote | 1 -> pour angle : ");
		scanf_s("%d", &choix_C_A);

		//-- nettoyer le bufferclavier --// 
		while ((getchar() != '\n') && (getchar() != EOF));
		
		//--> choix de la séquence de sélection 
		switch (choix_C_A)
		{
			case cote:
				//-- msg user pour sélection --// 
				printf("\n=> choix du cote, entrer : 1 -> pour adj | 2 -> pour hyp | 3 -> pour opp :  "); 
				scanf_s("%d", &choix_AHC);

				//-- nettoyer le bufferclavier --// 
				while ((getchar() != '\n') && (getchar() != EOF));

				//-- msg user pour inserer une valeur de longeur 
				printf("\n=> inserez une valeur entre 1 et 100  : "); 
				scanf_s("%d", (int*)&longueurSegment);
							
				//-- nettoyer le bufferclavier --// 
				while ((getchar() != '\n') && (getchar() != EOF));

				//-- test de la sélection + maj structure triangle  
				//-> adjacent
				if (choix_AHC == adj) 
				{
					//MAJ variable triangle -> champs : adjacent
					triangle.triangle_s.adjacent = longueurSegment;
				}
				//-> hypothénuse
				else if (choix_AHC == hyp)
				{
					//MAJ variable triangle -> champs : hypthénuse
					triangle.triangle_s.hypotenuse = longueurSegment;
				}
				//-> opposé 
				else 	
				{
					//MAJ variable triangle -> champs : opposé
					triangle.triangle_s.oppose = longueurSegment;
				}
				//-- MAJ de nb de choix à disposition --// 
				nbChoix++; 

				break;

			case angle:
				//-- msg user pour sélection --// 
				printf("\n=> choix de l'angle, entrer : 1 -> pour Alpha | 2 -> pour Beta :  ");
				scanf_s("%d", &choix_AB);

				//-- nettoyer le bufferclavier --// 
				while ((getchar() != '\n') && (getchar() != EOF));

				//-- msg user pour inserer une valeur d'angle 
				printf("\n=> inserez une valeur entre 0.1 et 90.0 degre : ");
				scanf_s("%f", &angle_deg);

				//-- nettoyer le bufferclavier --// 
				while ((getchar() != '\n') && (getchar() != EOF));

				//-- test de la sélection + maj structure triangle  
				if (choix_AB == alpha)
				{
					//-- MAJ de l'angle Alpha -> case 0
					triangle.tb_Angle[0] = angle_deg;
				}
				else
				{
					//-- MAJ de l'angle Beta -> case 2
					triangle.tb_Angle[2] = angle_deg;
				}
				//-- MAJ de nb de choix à disposition --// 
				nbChoix++;

				break;

			default:
				printf("\n !! Aucune valeur n'a ete choisie !! "); 
				break;
		}
	}

	//-- appel de fct pour le calcul des segments
	
	testFct = CalculerLongueurSegment(&triangle);
	

	//-- msg user - état calcul --// 
	if (testFct == ok)
	{
		//-- Affichage
		printf("\n -> Resultats : longeur adjacent %d ", triangle.triangle_s.adjacent);
		printf("\n -> Resultats : longeur hypotenuse %d ", triangle.triangle_s.hypotenuse);
		printf("\n -> Resultats : longeur oppose %d ", triangle.triangle_s.oppose);
		printf("\n -> Resultats : angle alpha %.2f ", triangle.tb_Angle[0]);
		printf("\n -> Resultats : angle beta %.2f ", triangle.tb_Angle[2]);
		printf("\n -> Resultats : perimetre du triangle %d ", triangle.perimetre);
		printf("\n -> Resultats : air du triangle %d \n", triangle.air);
	}
	else
	{
		printf("\n -> erreur de calcul !!!\n");
	}
	//-> pause -> system
	system("pause"); 
}