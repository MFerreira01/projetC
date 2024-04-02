#include <stdlib.h>
#include <stdio.h>
//#include <time.h>

#include "libOutils.h"

void main(void)
{
	srand((unsigned)time(NULL));

	#pragma region MATRICE
	////PARTI MATRICE
	//MATRICE matrice = { 0,0,NULL };
	//matrice = initialisationMatrice(4, 3, -10, 10);
	//affichageMatrice(matrice);
	//liberationMatrice(&matrice);

	//printf("\n");

	//int trace;
	//matrice = initialisationMatrice(4, 3, -10, 10); 
	//affichageMatrice(matrice);
	//trace = traceMatrice(matrice);
	//printf("Trace : %d", trace);
	//liberationMatrice(&matrice);

	//printf("\n");

	//MATRICE matrice1 = { 0,0,NULL };
	//MATRICE matrice2 = { 0,0,NULL };
	//matrice1 = initialisationMatrice(2, 2, -10, 10);
	//matrice2 = initialisationMatrice(2, 2, -10, 10);
	//MATRICE matriceAdd = additionMatrice(matrice1, matrice2);
	//MATRICE matriceMult = multiplicationMatrice(matrice1, matrice2);

	//affichageMatrice(matrice1);
	//printf("\n");
	//affichageMatrice(matrice2);
	//printf("\n");
	//affichageMatrice(matriceAdd);
	//printf("\n");
	//affichageMatrice(matriceMult);
	//printf("\n");

	//liberationMatrice(&matrice1);
	//liberationMatrice(&matrice2);
	//liberationMatrice(&matriceAdd);
	//liberationMatrice(&matriceMult);
	#pragma endregion	

	#pragma region iMATRICE
	////PARTI iMATRICE
	//iMATRICE imatrice = allocation_iMatrice(3, 3);
	//remplissageAleatoire_iMatrice(imatrice, -10, 10);
	//affichage_iMatrice(imatrice);
	//printf("\n");

	//printf("%p", &imatrice.valeurs[3]);
	//printf("\n");
	//printf("%p", imatrice.ptLignes[1]);
	//printf("\n");

	//printf("1er pixel : %d", imatrice.valeurs[0]);
	//printf(" ");
	//printf("1er pixel : %d", imatrice.ptLignes[0][0]);

	//printf("\n");
	//printf("Dernier pixel : %d", imatrice.valeurs[imatrice.hauteur * imatrice.largeur - 1]);
	//printf(" ");
	//printf("Dernier pixel : %d", imatrice.ptLignes[imatrice.largeur - 1][imatrice.largeur - 1]);
	//	
	//liberation_iMatrice(&imatrice);
	#pragma endregion

	#pragma region iMATRICE_sauvegarder_une_image
	//SAUVEGARDE D'UN FICHIER BINAIRE
	//iMATRICE mat = { 0,0,NULL , NULL};
	//mat = allocation_iMatrice(5, 2);
	//remplissageAleatoire_iMatrice(mat, 0, 255);
	//printf("\nVers une image...\n");
	//affichage_iMatrice(mat);


	////ECRIRE UN FICHIER
	//FILE* F = NULL;
	//int retour;

	//F = fopen("essai.dat", "wb");
	//retour = fwrite(&mat.hauteur, sizeof(int), 1, F);
	//printf("Octets ecrits : %d \n",retour);
	//retour = fwrite(&mat.largeur, sizeof(int), 1, F);
	//printf("Octets ecrits : %d \n", retour);
	//retour = fwrite(mat.valeurs, sizeof(int), mat.hauteur*mat.largeur, F);
	//printf("Octets ecrits : %d \n", retour);
	//fclose(F);


	////LIRE UN FICHIER
	//iMATRICE matRead = { 0,0,NULL , NULL };
	//FILE* F1 = NULL;

	//F1 = fopen("essai.dat", "rb");
	//retour = fread(&matRead.hauteur, sizeof(int), 1, F1);
	//printf("Octets lus : %d \n", retour);
	//retour = fread(&matRead.largeur, sizeof(int), 1, F1);
	//printf("Octets lus : %d \n", retour);
	//matRead = allocation_iMatrice(matRead.hauteur, matRead.largeur);
	//retour = fread(matRead.valeurs, sizeof(int), matRead.hauteur * matRead.largeur, F1);
	//printf("Octets lus : %d \n", retour);
	//fclose(F1);

	//affichage_iMatrice(matRead);


	////SAUVEGARDE D'UN FICHIER TEXTE
	iMATRICE mat = { 0,0,NULL , NULL };
	mat = allocation_iMatrice(5, 2);
	remplissageAleatoire_iMatrice(mat, 0, 255);
	printf("\nVers une image...\n");
	affichage_iMatrice(mat);

	//ECRIRE UN FICHIER
	FILE* F = NULL;
	int retour;

	F = fopen("essai2.txt", "w");
	fprintf(F,"%d\n", mat.hauteur);
	fprintf(F,"%d\n", mat.largeur);
	for (int i = 0; i < mat.hauteur * mat.largeur; i++)
	{
		fprintf(F, "%d\n", mat.valeurs[i]);
	}
	printf("Fichier ecrit \n");
	fclose(F);

	//LIRE UN FICHIER
	iMATRICE matRead = { 0,0,NULL , NULL };
	FILE* F1 = NULL;

	F1 = fopen("essai2.txt", "r");
	fscanf(F1, "%d\n", &matRead.hauteur);
	fscanf(F1, "%d\n", &matRead.largeur);
	matRead = allocation_iMatrice(matRead.hauteur, matRead.largeur);
	for (int i = 0; i < mat.hauteur * mat.largeur; i++)
	{
		fscanf(F1, "%d\n", &matRead.valeurs[i]);
	}
	printf("Fichier lu \n");
	fclose(F1);

	affichage_iMatrice(matRead);

	system("pause");

	liberation_iMatrice(&mat);
	liberation_iMatrice(&matRead);

	#pragma endregion
}
