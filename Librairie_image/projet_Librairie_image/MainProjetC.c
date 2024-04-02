#include <stdlib.h>
#include <stdio.h>

#include "libCIPSI1.h"
#include "libOutils.h"


int main(void)
{
	//TEST FONCTION

	/*IMAGE test = lectureImage("In_1.pgm");
	IMAGE testInv = inverseImage(test);
	test = erosionImageSE(test, SE);*/
	//sauvegardeImage(test, "P5", "W_inv.pgm");

	//IMAGE WTH = whiteTopHat(testInv, 4,30);
	//sauvegardeImage(WTH, "P5", "WTH.pgm");

	//WTH = seuillageOtsu(WTH);
	//sauvegardeImage(WTH, "P5", "WTH_OTSU.pgm");

	//WTH = erosionImage(WTH, 4);
	//WTH = erosionImage(WTH, 4);
	//WTH = dilatationImage(WTH, 4);


	//sauvegardeImage(WTH, "P5", "WTH2.pgm");

	//int rayon = 10;
	//ELEMENT_STRUCTURANT SE = allocation_SE('disk', rayon);

	//for (int i = 0; i < 2 * rayon + 1; i++)
	//{
	//	for (int j = 0; j < 2 * rayon + 1; j++)
	//	{
	//		printf("%d", SE.pixel[i][j]);
	//	}
	//	printf("\n");
	//}

	//IMAGE test = lectureImage("In_1.pgm");
	////test = seuillageOtsu(test);
	//test = erosionImageSE(test, SE);

	//sauvegardeImage(test, "P5", "ZSEERODE.pgm");


	/*int rayon = 20;
	ELEMENT_STRUCTURANT SE = allocation_SE('disk', rayon);

	IMAGE test = lectureImage("In_1.pgm");
	IMAGE testInv = inverseImage(test);
	sauvegardeImage(test, "P5", "A_W_inv.pgm");

	IMAGE WTH = whiteTopHatSE(testInv, SE);
	sauvegardeImage(WTH, "P5", "A_WTH.pgm");

	WTH = seuillageOtsu(WTH);
	sauvegardeImage(WTH, "P5", "A_WTH_OTSU.pgm");

	SE = allocation_SE('disk', 2);
	WTH = erosionImageSE(WTH, SE);
	SE = allocation_SE('disk', 1);
	WTH = dilatationImageSE(WTH,SE);


	sauvegardeImage(WTH, "P5", "A_WTH_FINALE.pgm");*/
	
	
	

	/*float* score = (float*)calloc(600, sizeof(float));
	for (int i = 0; i < 600; i++)
	{
		score[i] = 99.99;
	}

	EnregistrementScore("ScoreAllIn.csv", "allIn", 0, 0,score);
	EnregistrementScore("ScoreAllSc.csv", "allSc", 0, 0,score);
	EnregistrementScore("ScoreAll.csv", "all", 0, 0, score);
	EnregistrementScore("ScoreLotIn.csv", "lotIn", 30, 60,score);
	EnregistrementScore("ScoreLotSc.csv", "lotSc", 30, 80, score);

	
	printf("fin");*/

	//LancementProcess("In", 0, 0, 300);
	//LancementProcess("Sc", 0, 0, 300);
	//LancementProcess("lotIn", 10, 30, 0);
	//LancementProcess("lotSc", 10, 30, 0);
	//LancementProcess("allIn", 0, 0, 0);
	//LancementProcess("allSc", 0, 0, 0);
	//LancementProcess("all", 0, 0, 0);


	//int rayon = 10;
	//ELEMENT_STRUCTURANT SE = allocation_SE("square", rayon);

	//for (int i = 0; i < 2 * rayon + 1; i++)
	//{
	//	for (int j = 0; j < 2 * rayon + 1; j++)
	//	{
	//		printf("%d", SE.pixel[i][j]);
	//	}
	//	printf("\n");
	//}


	//Lancement IHM
	IHMprojet();

	return 0;
}
