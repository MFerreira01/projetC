#include <stdlib.h>
#include <stdio.h>

#include "libCIPSI1.h"

int main(void)
{
	#pragma region EXERCICE 3

	//IMAGE chro = lectureImage("chro.pgm");
	//chro = seuillageOtsu(chro);
	//IMAGERGB chroRGB = colorisationImage(chro, "ipsi.txt");
	//sauvegardeImageRGB(chroRGB, "P6", "exo3.ppm");
	//free(chro.data);

	#pragma endregion


	#pragma region EXERCICE 4

	//IMAGE cellules = lectureImage("cellules.pgm");
	//SIGNATURES stat_cellules = statistiquesImage(cellules);
	//cellules = seuillageImage(cellules, (stat_cellules.moyenne - 0.5 * stat_cellules.ecartType), (stat_cellules.moyenne + 0.5 * stat_cellules.ecartType));
	//sauvegardeImage(cellules, "P5", "exo4.pgm");
	//free(cellules.data);

	#pragma endregion

	#pragma region EXERCICE 5

	/*char* nomImage = (char*)malloc(sizeof(char));
	int voisinage;

	printf("Image : ");
	scanf("%s", nomImage);
	printf("Taille voisinage (NxN) : ");
	scanf("%d", &voisinage);

	int taille = strlen(nomImage);
	char ext = nomImage[taille-2];

	if (ext == 'g')
	{

		IMAGE test = lectureImage(nomImage);
		test = filtreMoyen(test, 3);
		sauvegardeImage(test, "P5", "exo5.pgm");
		free(test.data);
	}
	else
	{

		IMAGERGB testRGB = lectureImageRGB(nomImage);
		testRGB = filtreMoyenRGB(testRGB, 3);
		sauvegardeImageRGB(testRGB, "P6", "exo5.ppm");
		free(testRGB.data);
	}*/

	#pragma endregion
	return 0;
}