//-----------------------------------------------------------------------------------//
// Nom du projet 		: Projet 2 - Calculs Trigo
// Nom du fichier 		: FctCalculTrigo.c
// Date de cr�ation 	: 14.02.2024
// Date de modification : 14.02.2024
//
// Auteur 				: Philou (Ph. Bovey)
//
// Description          : 
//
// Remarques			: voir donnee de l'�preuve            
//----------------------------------------------------------------------------------//

//-- definission pour utiliser la lib math sous VS --// 
#define _USE_MATH_DEFINES

//--- librairie standart ---//
//#include <stdint.h>					//-- standard library of integer 
#include <stdio.h>					// for the Input-Ouput system 
#include <math.h>


//--- librairie perso ---//
#include "CalculTrigo.h"

/* ----------------------------------------------------------------------------------
// -> NOM FCT					: InitialiserStructure 
// -> PARAMETRES ENTRES			: 
// -> PARAMETRE SORTIE			: e_validation 
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle 
// -> description				: tous les champs de la structure seront mis � z�ro
 ----------------------------------------------------------------------------------*/
e_validation InitialiserStructure(str_triangleRectangle* pt_strTriangle)
{
	//-- d�claration variables --// 
	//-- pirmaire --// 

	short i; //indice de boucle

	//-- enumeration --// 
	//e_validation e_valid = ok; //avec le teste par pointeur
	e_validation e_valid = nok; //avec le teste if()

	//-- pointeur --//
	//char* pt_strOctet = pt_strTriangle; // pointeur en octet

	//-- boucle pour initilaiser le tableau des angles --//
	for (i = 0; i < 4 ; i++)
	{
		pt_strTriangle->tb_Angle[i] = 0;
	}

	//-- initialisation des cot�s -> adj - hyp - opp --// 
	pt_strTriangle->triangle_s.adjacent = 0;
	pt_strTriangle->triangle_s.hypotenuse = 0;
	pt_strTriangle->triangle_s.oppose = 0;

	//-- initialisation des champs de air et perim�tres --// 
	pt_strTriangle->air = 0;
	pt_strTriangle->perimetre = 0;

	//-- validation -> de la fct --// 

	//l'addition de toute les champs doit �tre �gale a z�ro
	if ( (pt_strTriangle->tb_Angle[0] 
		+ pt_strTriangle->tb_Angle[1]
		+ pt_strTriangle->tb_Angle[2] 
		+ pt_strTriangle->tb_Angle[3]
		+ pt_strTriangle->triangle_s.adjacent 
		+ pt_strTriangle->triangle_s.hypotenuse
		+ pt_strTriangle->triangle_s.oppose 
		+ pt_strTriangle->air
		+ pt_strTriangle->perimetre) == 0) 
	{
		printf("\n-> initialisation OK\n");
		e_valid = ok;
	}
	else
	{
		printf("\n-> initialisation NOK\n");
		//e_valid est par d�faut nok
	}

	//proposition teste par pointeur mais ne fonctionne pas a l'indice 19
	//valeur retourn�e -52
	/*for (i = 0; i < 22; i++)
	{
		printf_s("%d",(int)*(pt_strOctet +i));
		if ((pt_strOctet + i) != 0)
		{
			e_valid = nok;
		}
	}*/

	//-- valeur � retourner --// 
	return e_valid;
}
/* ----------------------------------------------------------------------------------
// -> NOM FCT					: Conversion_DegRad
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			: 
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: depuis un angle en degr� -> d�terminer sa valeur 
//								  en radian 
 ----------------------------------------------------------------------------------*/
void Conversion_DegRad(str_triangleRectangle* pt_strTriangle)
{

	//-- test si angle � convertir --//
	if (pt_strTriangle->tb_Angle[0] != 0)
	{
		//--> alpha 
		//						[1] -> alpha rad										   [0] -> alpha deg
		pt_strTriangle->tb_Angle[1] = (float)(M_PI / DEMICERCLE) * pt_strTriangle->tb_Angle[0];
	}
	if (pt_strTriangle->tb_Angle[2] != 0)
	{
		//--> beta 
		//						[3] -> beta rad											   [2] -> beta deg 
		pt_strTriangle->tb_Angle[3] = (float)(M_PI / DEMICERCLE) * pt_strTriangle->tb_Angle[2];
	}

}
/* ----------------------------------------------------------------------------------
// -> NOM FCT					: Conversion_RadDeg
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			:
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: depuis un angle en radian -> d�terminer sa valeur
//								  en degr�
 ----------------------------------------------------------------------------------*/
void Conversion_RadDeg(str_triangleRectangle* pt_strTriangle)
{

	//-- test si angle � convertir --//
	if (pt_strTriangle->tb_Angle[1] != 0)
	{
		//--> alpha 
		//						[0] -> alpha deg										   [1] -> alpha rad
		pt_strTriangle->tb_Angle[0] = (float)(DEMICERCLE / M_PI) * pt_strTriangle->tb_Angle[1];
	}
	if (pt_strTriangle->tb_Angle[3] != 0)
	{
		//--> beta 
		//						[2] -> beta deg											   [3] -> beta rad
		pt_strTriangle->tb_Angle[2] = (float)(DEMICERCLE / M_PI) * pt_strTriangle->tb_Angle[3];
	}
}
/* ----------------------------------------------------------------------------------
// -> NOM FCT					: CalculAllAngles
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			: e_validation
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: si angle rentr� alors alors d�termine le 2�me angle 
 ----------------------------------------------------------------------------------*/
e_validation CalculerAllAngles(str_triangleRectangle* pt_strTriangle)
{
	//-- d�claration variables --// 
	//-- pirmaire --// 

	float tmp; //valeur temporaire des rapport pour les arctan/arcsin/arccos

	//-- enumeration --//
	e_validation e_valid = nok;

	//--test si pas d'angle d�fini 
	if ((pt_strTriangle->tb_Angle[0] == 0) && (pt_strTriangle->tb_Angle[2] == 0))
	{
		//-- si cot� non d�fini -> hypoth�nuse -> fonction trigo invers�e arctan
		if ((pt_strTriangle->triangle_s.hypotenuse == 0) && (pt_strTriangle->triangle_s.oppose != 0) && (pt_strTriangle->triangle_s.adjacent != 0))
		{
			tmp = ((float)pt_strTriangle->triangle_s.oppose / (float)pt_strTriangle->triangle_s.adjacent);
			pt_strTriangle->tb_Angle[1] = (float)atan((double)tmp);
			//pt_strTriangle->tb_Angle[1] = (float)atan((pt_strTriangle->triangle_s.oppose / pt_strTriangle->triangle_s.adjacent));
		}
		//-- si cot� non d�fini -> oppos� -> fonction trigo invers�e arccos
		if ((pt_strTriangle->triangle_s.oppose == 0) && (pt_strTriangle->triangle_s.adjacent != 0) && (pt_strTriangle->triangle_s.hypotenuse != 0))
		{
			tmp = ((float)pt_strTriangle->triangle_s.adjacent / (float)pt_strTriangle->triangle_s.hypotenuse);
			pt_strTriangle->tb_Angle[1] = (float)acos((double)tmp);
			//pt_strTriangle->tb_Angle[1] = (float)acos((pt_strTriangle->triangle_s.adjacent / pt_strTriangle->triangle_s.hypotenuse));
		}
		//-- si cot� non d�fini -> adjacent -> fonction trigo invers�e arcsin
		if ((pt_strTriangle->triangle_s.adjacent == 0) && (pt_strTriangle->triangle_s.oppose != 0) && (pt_strTriangle->triangle_s.hypotenuse != 0))
		{
			tmp = ((float)pt_strTriangle->triangle_s.oppose / (float)pt_strTriangle->triangle_s.hypotenuse);
			pt_strTriangle->tb_Angle[1] = (float)asin((double)tmp);
			//pt_strTriangle->tb_Angle[1] = (float)asin((pt_strTriangle->triangle_s.oppose / pt_strTriangle->triangle_s.hypotenuse));
		}
		//-- conversion Radian - Degr�
		Conversion_RadDeg(pt_strTriangle);
	}

	//-- test si un angle a �t� d�finit alpha ou beta 
	if ((pt_strTriangle->tb_Angle[0] != 0) && (pt_strTriangle->tb_Angle[2] == 0))
	{
		pt_strTriangle->tb_Angle[2] = 90 - pt_strTriangle->tb_Angle[0]; //-- calcul de beta
	}
	else if ((pt_strTriangle->tb_Angle[0] == 0) && (pt_strTriangle->tb_Angle[2] != 0))
	{
		pt_strTriangle->tb_Angle[0] = 90 - pt_strTriangle->tb_Angle[2]; //-- calcul de alpha 
	}
	//-- conversion Degr� - Radian 
	Conversion_DegRad(pt_strTriangle);
	
	//-- affichge des valeur des angle pour debug --//
	//printf("%f \n", pt_strTriangle->tb_Angle[0]);
	//printf("%f \n", pt_strTriangle->tb_Angle[1]);
	//printf("%f \n", pt_strTriangle->tb_Angle[2]);
	//printf("%f \n", pt_strTriangle->tb_Angle[3]);

	//-- test si tous les champs sont remplis 
	//fonction ET de toute les champs des angles doit �tre diff�rant de z�ro
	if ((pt_strTriangle->tb_Angle[0] != 0) &&
		(pt_strTriangle->tb_Angle[1] != 0) &&
		(pt_strTriangle->tb_Angle[2] != 0) &&
		(pt_strTriangle->tb_Angle[3] != 0))
	{
		printf("\n-> CalculerAllAngles OK\n");
		e_valid = ok;
	}
	else
	{
		printf("\n-> CalculerAllAngles NOK\n");
		//e_valid est par d�faut nok
	}

	return e_valid;
}

/* ----------------------------------------------------------------------------------
// -> NOM FCT					: CalculerPerimetreAir
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			: e_validation
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: calculer le p�rimetre et l'air du triangle
//								  selon les param�tres ins�rer par l'utilisateur
 ----------------------------------------------------------------------------------*/
e_validation CalculerPerimetreAir(str_triangleRectangle* pt_strTriangle)
{
	//-- enumeration --// 
	e_validation e_valid = nok;

	// Si les segment on �t� calcul�, calculer le p�rimetre et l'Air
	if ((pt_strTriangle->triangle_s.hypotenuse != 0) &&
		(pt_strTriangle->triangle_s.adjacent != 0) &&
		(pt_strTriangle->triangle_s.oppose != 0))
	{
		//somme des segment est �gale au perimetre
		pt_strTriangle->perimetre = (pt_strTriangle->triangle_s.hypotenuse + pt_strTriangle->triangle_s.adjacent + pt_strTriangle->triangle_s.oppose);
		//(base * hauteur) /2 est �gale a l'air (adjacent * oppos�) /2
		pt_strTriangle->air = (pt_strTriangle->triangle_s.adjacent * pt_strTriangle->triangle_s.oppose) / 2;
	}


	//fonction ET de toute les champs des angles doit �tre diff�rant de z�ro
	if ((pt_strTriangle->air != 0) &&
		(pt_strTriangle->perimetre != 0))
	{
		printf("\n-> CalculerPerimetreAir OK\n");
		e_valid = ok;
	}
	else
	{
		printf("\n-> CalculerPerimetreAir NOK\n");
		//e_valid est par d�faut nok
	}

	return e_valid;



}

/* ----------------------------------------------------------------------------------
// -> NOM FCT					: CalculerLongeursSgements
// -> PARAMETRES ENTRES			:
// -> PARAMETRE SORTIE			: e_validation
// -> PARAMETRE IN/OUT -> ptr	: str_triangleRectangle pt_strTriangle
// -> description				: calculer les diff�rents segments du triangle 
//								  [adjacent - hypoth�nuse - oppos�] 
//								  selon les param�tres ins�rer par l'utilisateur
 ----------------------------------------------------------------------------------*/
e_validation CalculerLongueurSegment(str_triangleRectangle* pt_strTriangle)
{
	//-- enumeration --// 
	e_validation e_valid = nok; 


	//-- calcule les angles--//
	e_valid = CalculerAllAngles(pt_strTriangle);

	// si les angle on pu �tre d�termin� calculer les segments
	// et que au moins un des cot� du triangle est d�finit
	if ((e_valid == ok) &&
		((pt_strTriangle->triangle_s.hypotenuse +
			pt_strTriangle->triangle_s.adjacent +
			pt_strTriangle->triangle_s.oppose) != 0))
	{
		//-- test si sgement hypoth�nuse entr� 
		if (pt_strTriangle->triangle_s.hypotenuse != 0)
		{
			//Calcul -> cos(alpha) = adj / hyp => ... 
			if (pt_strTriangle->triangle_s.adjacent == 0)
			{
				pt_strTriangle->triangle_s.adjacent = (char)(cos(pt_strTriangle->tb_Angle[1]) * pt_strTriangle->triangle_s.hypotenuse);
			}
			//Calcul -> sin(alpha) = opp / hyp => ...
			if (pt_strTriangle->triangle_s.oppose == 0)
			{
				pt_strTriangle->triangle_s.oppose = (char)(sin(pt_strTriangle->tb_Angle[1]) * pt_strTriangle->triangle_s.hypotenuse);
			}	
		}
		//-- test si sgement adjacent entr� 
		else if (pt_strTriangle->triangle_s.adjacent != 0)
		{
			
			//Calcul -> cos(alpha) = adj/hyp => ...
			if (pt_strTriangle->triangle_s.hypotenuse == 0)
			{
				pt_strTriangle->triangle_s.hypotenuse = (char)(pt_strTriangle->triangle_s.adjacent / cos(pt_strTriangle->tb_Angle[1]));
			}
			//Calcul -> tan(alpha) = opp/adj => ...
			if (pt_strTriangle->triangle_s.oppose == 0)
			{
				pt_strTriangle->triangle_s.oppose = (char)(tan(pt_strTriangle->tb_Angle[1]) * pt_strTriangle->triangle_s.adjacent);
			}
		}
		//-- test si sgement oppos� entr�  			
		else if (pt_strTriangle->triangle_s.oppose != 0)
		{
			//Calcul -> sin(alpha) = opp/hyp => ...
			if (pt_strTriangle->triangle_s.hypotenuse == 0)
			{
				pt_strTriangle->triangle_s.hypotenuse = (char)(pt_strTriangle->triangle_s.oppose / sin(pt_strTriangle->tb_Angle[1]));
			}
			//Calcul -> tan(alpha) = opp/adj => ... 
			if (pt_strTriangle->triangle_s.adjacent == 0)
			{
				pt_strTriangle->triangle_s.adjacent = (char)(pt_strTriangle->triangle_s.oppose / tan(pt_strTriangle->tb_Angle[1]));
			}
		}
	}
	//si aucun des cot� n'est d�finis affiche qu'il n'y a pas de cot� d�finis
	else
	{
		printf("\n-> Aucun cote definnis\n");
	}

	//-- calcule le p�rimetre et la surface --//
	e_valid = CalculerPerimetreAir(pt_strTriangle);

	//-- test si tous les champs sont remplis 
	//fonction ET de toute les champs des segment doit �tre diff�rant de z�ro
	if ((e_valid == ok) && // contr�le que les ancienne fonction ce sont execut� correctement
		(pt_strTriangle->triangle_s.hypotenuse != 0) &&
		(pt_strTriangle->triangle_s.adjacent != 0) &&
		(pt_strTriangle->triangle_s.oppose != 0))
	{
		//-- retourne OK
		printf("\n-> CalculerLongueurSegment OK\n");
		e_valid = ok;
	}
	else
	{
		//-- retourne NOK
		printf("\n-> CalculerLongueurSegment NOK\n");
		e_valid = nok;
	}
	
	return e_valid; 
}








