#include "SignatureComposanteConnexe.h"
#include "image.h"
#include < stdlib.h >
#include <math.h>

SignatureComposanteConnexe* signaturesImage(image img, int nbComp)
{
	SignatureComposanteConnexe* SignatureCC = (SignatureComposanteConnexe*)calloc((nbComp + 1), sizeof(SignatureComposanteConnexe));

	//Histogramme image labelisé donne surface des composantes
	int* histo = (int*)malloc(256 * sizeof(int));
	histo = image::histogrammeImage(img, 0, 256);

	//Histogramme image contour donne périmetre composantes
	int* histoContour = (int*)malloc(256 * sizeof(int));
	image imgContour = image::contourImage(img, 4);
	histoContour = image::histogrammeImage(imgContour, 0, 256);

	//SURFACE + RAYON + PERIMETRE + COMPACITE
	for (int i = 0; i < nbComp + 1; i++)
	{
		SignatureCC[i].surface = histo[i];
		SignatureCC[i].rayon = sqrt(SignatureCC[i].surface / 3.14159265);
		SignatureCC[i].perimetre = histoContour[i];
		SignatureCC[i].compacite = (SignatureCC[i].perimetre * SignatureCC[i].perimetre) / (4 * 3.14159265 * SignatureCC[i].surface);
		SignatureCC[i].suppr = 1;
	}

	//CENTRE GRAVITE
	int compo;
	for (int i = 0; i < img.getNblig(); i++)
	{
		for (int j = 0; j < img.getNbCol(); j++)
		{
			compo = img.pixel[i][j];
			SignatureCC[compo].CG.abscisse = (SignatureCC[compo].CG.abscisse + j);
			SignatureCC[compo].CG.ordonnee = (SignatureCC[compo].CG.ordonnee + i);
		}
	}

	for (int compo = 0; compo < nbComp + 1; compo++)
	{
		SignatureCC[compo].CG.abscisse = (SignatureCC[compo].CG.abscisse / SignatureCC[compo].surface);
		SignatureCC[compo].CG.ordonnee = (SignatureCC[compo].CG.ordonnee / SignatureCC[compo].surface);
	}

	//BORDS
	//BORD HAUT
	for (int j = 0; j < img.getNbCol(); j++)
	{
		compo = img.pixel[0][j];
		if (compo != 0)
		{
			SignatureCC[compo].bord = 1;
		}
	}
	//BORD BAS
	for (int j = 0; j < img.getNbCol(); j++)
	{
		compo = img.pixel[img.getNblig() - 1][j];
		if (compo != 0)
		{
			SignatureCC[compo].bord = 1;
		}
	}
	//BORD GAUCHE
	for (int i = 0; i < img.getNblig(); i++)
	{
		compo = img.pixel[i][0];
		if (compo != 0)
		{
			SignatureCC[compo].bord = 1;
		}
	}
	//BORD DROIT
	for (int i = 0; i < img.getNblig(); i++)
	{
		compo = img.pixel[i][img.getNbCol() - 1];
		if (compo != 0)
		{
			SignatureCC[compo].bord = 1;
		}
	}

	free(histo);
	free(histoContour);
	delete& imgContour;
	return SignatureCC;
}