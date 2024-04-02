#include <stdlib.h>
#include <stdio.h>
#include <libCIPSI1.h>
#include <libOutils.h>

int main(void)
{

	//EX3
	//TAB_RESISTANCE resistance = lectureData("resistances.txt");
	//enregistreDATA("ResultatResistance.txt", resistance);
	//free(resistance.data);

	//EX4
	POINT* tab = (POINT*)calloc(9, sizeof(POINT));
	generationAleatoirePoints(tab, 9, -6, 6);
	float a, b;
	regression(tab, 9, &a, &b);
	printf("a = %f et b = %f \n", a, b);

	sortieRegression("Sortieregression.csv", tab, 9);
	
	free(tab);

	//POUR I
	IMAGE contours = lectureImage("contours.pgm");
	int n;
	POINT* pointContoursI = ImageVersPoints(contours, &n, 'i');
	regression(pointContoursI, n, &a, &b);
	printf("a = %f et b = %f pour i \n", a, b);
	IMAGE sortieRegI = imageSortieRegression(contours, 'i');
	IMAGERGB sortieRegIRGB = colorisationImage(sortieRegI, "ipsi.txt");
	sauvegardeImageRGB(sortieRegIRGB, "P6", "sortieRegI_RGB.ppm");

	//POUR J
	IMAGE contours2 = lectureImage("contours.pgm");
	POINT* pointContoursJ = ImageVersPoints(contours2, &n, 'j');
	regression(pointContoursJ, n, &a, &b);
	printf("a = %f et b = %f pour j \n", a, b);
	IMAGE sortieRegJ = imageSortieRegression(contours2, 'j');
	IMAGERGB sortieRegJRGB = colorisationImage(sortieRegJ, "ipsi.txt");
	sauvegardeImageRGB(sortieRegJRGB, "P6", "sortieRegJ_RGB.ppm");

	free(pointContoursI);
	free(pointContoursJ);

	return 0;
}