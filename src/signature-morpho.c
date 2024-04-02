#include <stdlib.h>
#include <stdio.h>

#include "libCIPSI1.h"
#include "libOutils.h"

int main(void)
{

	//IMAGE bouton = lectureImage("boutons.pgm");
	//bouton = seuillageOtsu(bouton);
	//IMAGE LesTrous = bouton;
	//bouton = inverseImage(bouton);
	//int nbcomp;
	//IMAGE boutonlabel = labelImage(bouton, &nbcomp);
	//IMAGE SansBoutonBord;

	//SIGNATURE_COMPOSANTE_CONNEXE* SignaCC = (SIGNATURE_COMPOSANTE_CONNEXE*)malloc((nbcomp + 1) * sizeof(SIGNATURE_COMPOSANTE_CONNEXE));
	//SignaCC = signaturesImage(boutonlabel, nbcomp);
	//for (int i = 0; i < nbcomp + 1; i++)
	//{
	//	printf("Bouton %d \n", i);
	//	printf("Surface : %d \n", SignaCC[i].surface);
	//	printf("Perimetre : %f \n", SignaCC[i].perimetre);
	//	printf("Compacite : %f \n", SignaCC[i].compacite);
	//	printf("Rayon : %f \n", SignaCC[i].rayon);
	//	printf("CG.x : %f & CG.y : %f \n", SignaCC[i].CG.abscisse, SignaCC[i].CG.ordonnee);
	//	printf("Bords : %d \n", SignaCC[i].bord);

	//	printf("\n");
	//}

	//SansBoutonBord = SupprimerComposanteBord(boutonlabel, nbcomp);
	//IMAGERGB SansBoutonRGB = colorisationImage(SansBoutonBord, "ipsi.txt");
	//sauvegardeImageRGB(SansBoutonRGB, "P6", "SansBoutonRGB.ppm");
	//sauvegardeImage(SansBoutonBord, "P5", "SansBouton.pgm");
	//



	//int nbtrou;
	//IMAGE troulabel = labelImage(LesTrous, &nbtrou);
	//SIGNATURE_COMPOSANTE_CONNEXE* SignatureTrou = (SIGNATURE_COMPOSANTE_CONNEXE*)malloc((nbtrou + 1) * sizeof(SIGNATURE_COMPOSANTE_CONNEXE));
	//SignatureTrou = signaturesImage(troulabel, nbtrou);
	//for (int i = 0; i < nbtrou + 1; i++)
	//{
	//	printf("Trou %d \n", i);
	//	printf("Surface : %d \n", SignatureTrou[i].surface);
	//	printf("Perimetre : %f \n", SignatureTrou[i].perimetre);
	//	printf("Compacite : %f \n", SignatureTrou[i].compacite);
	//	printf("Rayon : %f \n", SignatureTrou[i].rayon);
	//	printf("CG.x : %f & CG.y : %f \n", SignatureTrou[i].CG.abscisse, SignatureTrou[i].CG.ordonnee);
	//	printf("Bords : %d \n", SignatureTrou[i].bord);

	//	printf("\n");
	//}
	//IMAGE SansTrouBord = SupprimerComposanteBord(troulabel, nbtrou);
	//IMAGERGB Trou = colorisationImage(SansTrouBord, "ipsi.txt");
	//sauvegardeImageRGB(Trou, "P6", "trou.ppm");



	////Distance euclienne entre CG bouton et CG trou si < Rayon alors dans bouton
	//float distance;
	//int troumax;
	//int* LUT_2trous = (int*)calloc((nbcomp + 1), sizeof(int));
	//int* LUT_4trous = (int*)calloc((nbcomp + 1), sizeof(int));
	//for (int i = 1; i < nbcomp; i++)
	//{
	//	troumax = 0;
	//	if (SignaCC[i].bord != 1)
	//	{
	//		for (int j = 2; j < nbtrou; j++)
	//		{
	//			distance = distancePoints(SignatureTrou[j].CG, SignaCC[i].CG);
	//			if (distance < SignaCC[i].rayon)
	//			{
	//				troumax++;
	//			}
	//		}
	//		
	//		if (troumax == 2)
	//		{
	//			LUT_2trous[i] = troumax;
	//		}
	//		if (troumax == 4)
	//		{
	//			LUT_4trous[i] = troumax;
	//		}
	//	}
	//}

	//affichageTableauInt(LUT_2trous, nbcomp + 1);
	//IMAGE Bouton2Trous = ChangerLUT(SansBoutonBord, LUT_2trous);
	//IMAGERGB Bouton2TrousRGB = colorisationImage(Bouton2Trous, "ipsi.txt");
	//sauvegardeImageRGB(Bouton2TrousRGB, "P6", "Bouton2Trous.ppm");

	//affichageTableauInt(LUT_4trous, nbcomp + 1);
	//IMAGE Bouton4Trous = ChangerLUT(SansBoutonBord, LUT_4trous);
	//IMAGERGB Bouton4TrousRGB = colorisationImage(Bouton4Trous, "ipsi.txt");
	//sauvegardeImageRGB(Bouton4TrousRGB, "P6", "Bouton4Trous.ppm");


	//free(SignaCC);
	//free(SignatureTrou);
	//free(LUT_2trous);
	//free(LUT_4trous);
	//liberationImage(&bouton);
	//liberationImage(&boutonlabel);
	//liberationImage(&troulabel);
	//liberationImageRGB(&Bouton2TrousRGB);
	//liberationImageRGB(&Bouton4TrousRGB);
	//liberationImageRGB(&SansBoutonRGB);
	//liberationImageRGB(&Trou);


	/*IMAGE chro = lectureImage("chro.pgm");
	chro = seuillageOtsu(chro);
	sauvegardeImage(chro, "P5", "chroBW.pgm");
	IMAGE chroErode = erosionImage(chro, 4);
	sauvegardeImage(chroErode, "P5", "chroErode.pgm");
	IMAGE contour = contourImage(chro, 4);
	sauvegardeImage(contour, "P5", "chroContour.pgm");

	IMAGE chroErodeV8 = erosionImage(chro, 8);
	sauvegardeImage(chroErodeV8, "P5", "chroErodeV8.pgm");
	IMAGE contourV8 = contourImage(chro, 8);
	sauvegardeImage(contourV8, "P5", "chroContourV8.pgm");

	IMAGE chroDilate = dilatationImage(chro, 4);
	sauvegardeImage(chroDilate, "P5", "chroDilate.pgm");
	IMAGE chroDilateV8 = dilatationImage(chro, 8);
	sauvegardeImage(chroDilateV8, "P5", "chroDilateV8.pgm");

	int nbchro;
	IMAGE chroLabel = labelImage(chro, &nbchro);
	SIGNATURE_COMPOSANTE_CONNEXE* signatureChro = (SIGNATURE_COMPOSANTE_CONNEXE*)malloc((nbchro + 1) * sizeof(SIGNATURE_COMPOSANTE_CONNEXE));
	signatureChro = signaturesImage(chroLabel, nbchro);
	for (int i = 0; i < nbchro + 1; i++)
	{
		printf("Chro %d \n", i);
		printf("Surface : %d \n", signatureChro[i].surface);
		printf("Perimetre : %f \n", signatureChro[i].perimetre);
		printf("Compacite : %f \n", signatureChro[i].compacite);
		printf("Rayon : %f \n", signatureChro[i].rayon);
		printf("CG.x : %f & CG.y : %f \n", signatureChro[i].CG.abscisse, signatureChro[i].CG.ordonnee);
		printf("Bords : %d \n", signatureChro[i].bord);
	}

	liberationImage(&chro);
	liberationImage(&chroErode);
	liberationImage(&contour);
	liberationImage(&chroErodeV8);
	liberationImage(&contourV8);
	liberationImage(&chroDilate);
	liberationImage(&chroDilateV8);
	free(signatureChro);*/









	//IMAGE test = lectureImage("In_1.pgm");
	//IMAGE testInv = inverseImage(test);
	//sauvegardeImage(test, "P5", "W_inv.pgm");

	//IMAGE WTH = whiteTopHat(testInv, 4,30);
	//sauvegardeImage(WTH, "P5", "WTH.pgm");

	//WTH = seuillageOtsu(WTH);
	//sauvegardeImage(WTH, "P5", "WTH_OTSU.pgm");

	//WTH = erosionImage(WTH, 4);
	//WTH = erosionImage(WTH, 4);
	//WTH = dilatationImage(WTH, 4);


	//sauvegardeImage(WTH, "P5", "WTH2.pgm");

	int rayon = 20;
	ELEMENT_STRUCTURANT SE = allocation_SE('disk', rayon);

	for (int i = 0; i < 2 * rayon + 1; i++)
	{
		for (int j = 0; j < 2 * rayon + 1; j++)
		{
			printf("%d", SE.pixel[i][j]);
		}
		printf("\n");
	}

	return 0;
}
