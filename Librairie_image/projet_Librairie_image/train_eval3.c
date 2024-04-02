#include <stdlib.h>
#include <stdio.h>
#include <libCIPSI1.h>
#include <libOutils.h>

IMAGE bruitAleatoireImage(IMAGE img, int amplitude)
{
	IMAGE bruit = img;
	int valMin = -amplitude;
	int ValMax = amplitude;

	for (int i = 0; i < img.Nbcol * img.Nblig; i++)
	{
		bruit.data[i] = bruit.data[i] + (unsigned char)(valMin + rand() % (ValMax + 1 - valMin));
	}
	return bruit;
}

IMAGERGB bruitAleatoireImageRGB(IMAGERGB img, int amplitude)
{
	IMAGERGB bruit = img;
	int valMin = -amplitude;
	int ValMax = amplitude;

	for (int i = 0; i < img.Nbcol * img.Nblig; i++)
	{
		int rando = ((valMin + rand() % (ValMax + 1 - valMin)));
		double ampl = 1 + rando/255.0;
		bruit.data[i].R = bruit.data[i].R * ampl;
		bruit.data[i].G = bruit.data[i].G * ampl;
		bruit.data[i].B = bruit.data[i].B * ampl;
	}
	return bruit;
}

IMAGERGB masqueImage(IMAGE img, IMAGERGB masque)
{
	IMAGERGB rgb = allocationImageRGB(img.Nblig, img.Nbcol);

	int j = 0;
	while(j < img.Nblig * img.Nbcol)
	{
		if (masque.data[j].R == 0 && masque.data[j].G == 0 && masque.data[j].B == 0)
		{
			rgb.data[j].R = img.data[j];
			rgb.data[j].G = img.data[j];
			rgb.data[j].B = img.data[j];
		}
		else
		{
			rgb.data[j].R = masque.data[j].R;
			rgb.data[j].G = masque.data[j].G;
			rgb.data[j].B = masque.data[j].B;
		}
		j++;
	}

	return rgb;
}

void main(void)
{
	srand((unsigned)time(NULL));

	//EX1
	IMAGE lena = lectureImage("lena.pgm");

	FILE* ampli = fopen("bruit.txt", "r");
	char* ligne[1];
	int amplitude;
	while (fgets(ligne, 255, ampli) != NULL)
	{
		sscanf(ligne, "%d", &amplitude);
	}
	fclose(ampli);

	IMAGE bruit = bruitAleatoireImage(lena, amplitude);
	sauvegardeImage(bruit, "P5", "bruit.pgm");

	//EX1 BIS
	IMAGERGB lenaRGB = lectureImageRGB("lena.ppm");

	FILE* ampliRGB = fopen("bruit.txt", "r");
	char* ligneRGB[1];
	int amplitudeRGB;
	while (fgets(ligneRGB, 255, ampliRGB) != NULL)
	{
		sscanf(ligneRGB, "%d", &amplitudeRGB);
	}
	fclose(ampliRGB);

	IMAGERGB bruitRGB = bruitAleatoireImageRGB(lenaRGB, amplitudeRGB);
	sauvegardeImageRGB(bruitRGB, "P6", "bruitRGB.ppm");

	//EX2
	IMAGE chro = lectureImage("chro.pgm");
	IMAGERGB masque = lectureImageRGB("mask.ppm");

	IMAGERGB imageMasque = masqueImage(chro, masque);
	sauvegardeImageRGB(imageMasque, "P6", "imageMasque.ppm");


	//EX3 PEUT PAS FAIRE POUR L'INSTANT
	IMAGE bouton = lectureImage("boutons.pgm");
	bouton = inverseImage(bouton);
	bouton = seuillageOtsu(bouton);
	int cmpt = 0;
	IMAGE boutonlabel = labelImage(bouton, &cmpt);
	IMAGERGB boutonlabelRGB = colorisationImage(boutonlabel, "ipsi.txt");
	sauvegardeImageRGB(boutonlabelRGB, "P6", "boutonlabel.ppm");





}