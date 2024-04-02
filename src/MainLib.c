#include <stdlib.h>
#include <stdio.h>

#include "libCIPSI1.h"

void main(void)
{
	//IMAGE img;
	//img = allocationImage(256, 256);
	//initialisationAleatoireImage(img, 0, 255);
	//sauvegardeImage(img, "P5", "img");
	//liberationImage(&img);

	//IMAGERGB RGB;
	//RGB = allocationImageRGB(256, 256);
	//initialisationAleatoireImageRGB(RGB, 0, 255);
	//sauvegardeImageRGB(RGB, "P6", "imgRGB");
	//liberationImageRGB(&RGB);

	//IMAGERGB rizRGB;
	//IMAGE riz = lectureImage("riz.pgm");
	//int nb;
	//riz = inverseImage(riz);
	//sauvegardeImage(riz, "P2", "RizInverse");
	////riz = egalisationImage(riz);
	//riz = seuillageOtsu(riz);
	//sauvegardeImage(riz, "P2", "RizSeuil");
	//riz = labelImage(riz, &nb);
	//printf("Il y a %d grains", nb);
	//rizRGB = colorisationImage(riz, "ipsi.txt");
	//sauvegardeImageRGB(rizRGB, "P6", "RizRGB");
	//liberationImage(&riz);

	//IMAGE chro;
	//chro = lectureImage("chro.pgm");
	////Choix sert à savoir si on veut l'histo en .csv
	////n est le nb de niveau de gris
	//int* test = histogrammeImage(chro, 1, 0);
	//liberationImage(&chro);

	/*IMAGERGB lena;
	lena = lectureImageRGB("lena.ppm");
	int* test = histogrammeImageRGB(lena, 1, 256);
	liberationImage(&lena);*/


	//IMAGE chro;
	//IMAGERGB chroRGB;
	//chro = lectureImage("chro.pgm");
	//chroRGB = colorisationImage(chro, "spectrum.txt");
	//sauvegardeImageRGB(chroRGB, "P6", "chroRGB");

	//liberationImage(&chroRGB);

	int choix;
	printf("Choix image (0 - 14) ");
	scanf("%d", &choix);

	int caractereLu, ligne = 1;
	FILE* fichier = fopen("listing.txt", "r");
	char mot1[100];
	while (ligne < choix + 1)
	{
		caractereLu = fgetc(fichier);
		if (caractereLu == '\n')
			ligne++;
	}
	fgets(mot1, 100, fichier);
	printf("%s\n", mot1);
	fclose(fichier);


	fichier = fopen("listing.txt", "r");
	int temp = 0;
	ligne = 0;
	SIGNATURES signature;
	double dist;
	IMAGE img;
	IMAGE cible = lectureImage(mot1);
	int* h1;
	int* h2;
	char mot[100];
	char proche[100];

	double ecartPROCHE = 100000000000000;
	double distPROCHE = 100000000000000;



	for (int i = 0; i < 16; i++)
	{
		while (ligne < 1)
		{
			caractereLu = fgetc(fichier);
			if (caractereLu == '\n')
				ligne++;
		}
		fgets(mot, 100, fichier);
		printf("%s\n", mot);

		img = lectureImage(mot);
		signature = statistiquesImage(img);
		h1 = histogrammeImage(cible, 0, 256);
		h2 = histogrammeImage(img, 0, 256);

		dist = distanceHistogrammeImage(h1, h2, 256);

		if (signature.ecartType < ecartPROCHE)
		{
			ecartPROCHE = signature.ecartType;
		}
		if (dist < distPROCHE)
		{
			distPROCHE = dist;
		}
	}

	printf("L'image la plus proche de %s avec ecart type est %s avec : %p", &mot, &proche, &ecartPROCHE);
	printf("L'image la plus proche de %s avec distance est %s avec : %f", &mot, &proche, &distPROCHE);


	fclose(fichier);

	system("PAUSE");
}

