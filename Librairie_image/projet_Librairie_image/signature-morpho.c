#include <stdlib.h>
#include <stdio.h>

#include "libCIPSI1.h"

int main(void)
{
	IMAGE bouton = lectureImage("boutons.pgm");
	bouton = seuillageOtsu(bouton);
	bouton = inverseImage(bouton);
	int nbcomp;
	IMAGE boutonlabel = labelImage(bouton, &nbcomp);
	IMAGE SansBoutonBord;

	SIGNATURE_COMPOSANTE_CONNEXE* SignaCC = (SIGNATURE_COMPOSANTE_CONNEXE*)malloc((nbcomp + 1) * sizeof(SIGNATURE_COMPOSANTE_CONNEXE));
	SignaCC = signaturesImage(boutonlabel, nbcomp);
	for (int i = 0; i < nbcomp + 1; i++)
	{
		printf("Compo %d \n", i);
		printf("Surface : %d \n", SignaCC[i].surface);
		printf("Perimetre : %f \n", SignaCC[i].perimetre);
		printf("Compacite : %f \n", SignaCC[i].compacite);
		printf("Rayon : %f \n", SignaCC[i].rayon);
		printf("CG.x : %f & CG.y : %f \n", SignaCC[i].CG.abscisse, SignaCC[i].CG.ordonnee);
		printf("Bords : %d \n", SignaCC[i].bord);

		printf("\n");
	}

	SansBoutonBord = SupprimerComposanteBord(boutonlabel, nbcomp);
	IMAGERGB SansBoutonRGB = colorisationImage(SansBoutonBord, "ipsi.txt");
	sauvegardeImageRGB(SansBoutonRGB, "P6", "SansBoutonRGB.ppm");
	
	SansBoutonBord = seuillageOtsu(SansBoutonBord);
	SansBoutonBord = inverseImage(SansBoutonBord);
	sauvegardeImage(SansBoutonBord, "P5", "SansBouton.pgm");

	IMAGE troulabel = labelImage(SansBoutonBord, &nbcomp);
	SIGNATURE_COMPOSANTE_CONNEXE* SignatureBouton = (SIGNATURE_COMPOSANTE_CONNEXE*)malloc((nbcomp + 1) * sizeof(SIGNATURE_COMPOSANTE_CONNEXE));
	SignatureBouton = signaturesImage(troulabel, nbcomp);
	for (int i = 0; i < nbcomp + 1; i++)
	{
		printf("Compo %d \n", i);
		printf("Surface : %d \n", SignaCC[i].surface);
		printf("Perimetre : %f \n", SignaCC[i].perimetre);
		printf("Compacite : %f \n", SignaCC[i].compacite);
		printf("Rayon : %f \n", SignaCC[i].rayon);
		printf("CG.x : %f & CG.y : %f \n", SignaCC[i].CG.abscisse, SignaCC[i].CG.ordonnee);
		printf("Bords : %d \n", SignaCC[i].bord);

		printf("\n");
	}

	//Distance euclienne entre CG bouton et CG trou si < Rayon alors dans bouton


	free(bouton.data);
	free(SignaCC);

	return 0;
}
