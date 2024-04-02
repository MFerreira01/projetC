#include <stdlib.h>
#include <stdio.h>

#include"libOutils.h"

//CONTROLE_2 SEVE Léo IPSI1

void main(void)
{

#pragma region EX1
	////SI N = 3 -> 1² + 2² + 3² (NE PREND PAS EN COMPTE 0 DANS LES NOMBRES CAR 0² = 0)
	//int n = 0, somme = 0;
	//printf("Entrez n : "); 
	//scanf("%d", &n);
	//somme = 0;
	//for (int i = n; i > 0; i--)
	//{
	//	somme = somme + carre(i);
	//}

	//printf("Somme des %d premiers carres : %d\n", n, somme);
#pragma endregion

#pragma region EX2

	/*int T[5] = { 2,3,2,1,3 };
	int n = 0;

	printf("Avant :");
	affichageTableauInt(T,5);

	n = fonction1(T, 5);

	printf("Apres :");
	affichageTableauInt(T, 5);*/
	
#pragma endregion

#pragma region EX3
//	int t[100];
//	int n = 0; /* taille réelle du tableau */
//	int H[256] = { 0 };
//
//	// recherche min et max des niveaux de gris
//	int min = 0, max = 255;
//
//	srand((unsigned)time(NULL));
//	printf("Taille tableau : "); 
//	scanf("%d", &n);
//	initialisationAleatoireTableauInt(t,  n, 0, 255);
//	histogramme(t, H, n);
//	affichageTableauInt(t, 5);
//	min = minTableauIntViaHisto(H,256);
//	max = maxTableauIntViaHisto(H,256);
//	printf("Ng entre %d et %d\n", min, max);
#pragma endregion

#pragma region EX4
	/*int N, trace1, t[100];
	printf("N : "); 
	scanf("%d", &N);
	initialisationAleatoireTableauInt(t, N * N, 0, 10);
	affichageTableauInt(t, N * N);
	trace1 = trace(t, N);

	printf("trace = %d \n", trace1);*/
#pragma endregion

#pragma region EX4

	/*int test = puissance(2, 2);
	printf("puisannce = %d \n", test);
	int P[6] = { 33,2,-3,0,0,4 };
	test = evalPolynome(P, 5, 2);
	printf("polynome = %d \n", test);
	test = evalPolynomeV2(P, 5, 2);
	printf("polynome = %d \n", test);*/

#pragma endregion

	system("pause");
}