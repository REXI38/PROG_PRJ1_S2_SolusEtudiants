//-----------------------------------------------------------------------------------//
// Nom du projet 		: Projet 2 - Calculs Trigo
// Nom du fichier 		: mainProjet1_s2.c
// Date de cr�ation 	: 21.10.2022
// Date de modification : 14.02.2024
//
// Auteur 				: Philou (Ph. Bovey)
// 
// Modification			: LCX
// 
// Description          : 
//
// Remarques			: voir donnee de l'�preuve            
//----------------------------------------------------------------------------------//
//-- directive pr�processeur pour supprimer certains warining --//
#pragma warning(disable : 4996)		//-- warning concernant les scanf

//--- librairie standart ---//
#include <stdio.h>                  // entr�e - sortie
#include <stdlib.h>					// fonctions syst�me 

//--- librairie perso ---//
#include "CalculTrigo.h"

//-- d�claration de constantes --// 
const char* ptNOM_CANDIDAT = "Louis Cardinaux"; 
const char VERSION_PROJET = 1; 
const unsigned short ANNEE_TEST = 2025; 


//-- programme principal --// 
void main()
{
	//-- d�claration de variables locales --//
	//-- enum�ration 
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
	//-- it�ration -> max 2 choix possible 
	while ((testFct == ok) && (nbChoix < NB_CHOIX_MAX))
	{
		printf("\n=> choix de selection entrez : 0 -> pour cote | 1 -> pour angle : ");
		scanf_s("%d", &choix_C_A);

		//-- nettoyer le bufferclavier --// 
		while ((getchar() != '\n') && (getchar() != EOF));
		
		//--> choix de la s�quence de s�lection 
		switch (choix_C_A)
		{
			case cote:
				//-- msg user pour s�lection --// 
				printf("\n=> choix du cote, entrer : 1 -> pour adj | 2 -> pour hyp | 3 -> pour opp :  "); 
				scanf_s("%d", &choix_AHC);

				//-- nettoyer le bufferclavier --// 
				while ((getchar() != '\n') && (getchar() != EOF));

				//-- msg user pour inserer une valeur de longeur 
				printf("\n=> inserez une valeur entre 1 et 100  : "); 
				scanf_s("%d", (int*)&longueurSegment);
							
				//-- nettoyer le bufferclavier --// 
				while ((getchar() != '\n') && (getchar() != EOF));

				//-- test de la s�lection + maj structure triangle  
				//-> adjacent
				if (choix_AHC == adj) 
				{
					//MAJ variable triangle -> champs : adjacent
					triangle.triangle_s.adjacent = longueurSegment;
				}
				//-> hypoth�nuse
				else if (choix_AHC == hyp)
				{
					//MAJ variable triangle -> champs : hypth�nuse
					triangle.triangle_s.hypotenuse = longueurSegment;
				}
				//-> oppos� 
				else 	
				{
					//MAJ variable triangle -> champs : oppos�
					triangle.triangle_s.oppose = longueurSegment;
				}
				//-- MAJ de nb de choix � disposition --// 
				nbChoix++; 

				break;

			case angle:
				//-- msg user pour s�lection --// 
				printf("\n=> choix de l'angle, entrer : 1 -> pour Alpha | 2 -> pour Beta :  ");
				scanf_s("%d", &choix_AB);

				//-- nettoyer le bufferclavier --// 
				while ((getchar() != '\n') && (getchar() != EOF));

				//-- msg user pour inserer une valeur d'angle 
				printf("\n=> inserez une valeur entre 0.1 et 90.0 degre : ");
				scanf_s("%f", &angle_deg);

				//-- nettoyer le bufferclavier --// 
				while ((getchar() != '\n') && (getchar() != EOF));

				//-- test de la s�lection + maj structure triangle  
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
				//-- MAJ de nb de choix � disposition --// 
				nbChoix++;

				break;

			default:
				printf("\n !! Aucune valeur n'a ete choisie !! "); 
				break;
		}
	}

	//-- appel de fct pour le calcul des segments
	
	testFct = CalculerLongueurSegment(&triangle);
	

	//-- msg user - �tat calcul --// 
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