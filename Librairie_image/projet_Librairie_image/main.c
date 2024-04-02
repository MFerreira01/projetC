#include <stdlib.h>
#include <stdio.h>

#include <libCIPSI1.h>

void main(void)
{

	IMAGE img = lectureImage("lena1.pgm");
	sauvegardeImage(img, "P5", "res\\test.pgm");

	IMAGE img1 = lectureImage("lena1.pgm");
	sauvegardeImage(img1, "P2", "res\\test1.pgm");

	IMAGERGB img2 = lectureImageRGB("lena1.ppm");
	sauvegardeImageRGB(img2, "P6", "res\\test2.ppm");

	IMAGERGB img3 = lectureImageRGB("lena1.ppm");
	sauvegardeImageRGB(img3, "P3", "res\\test3.ppm");

	system("pause");
}