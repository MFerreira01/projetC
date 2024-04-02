#include <stdlib.h>
#include <stdio.h>

#include "libCIPSI1.h"
#include "libOutils.h"

int main(void)
{
	IMAGE img = lectureImage("In_1.pgm");
	IMAGE imgGT = lectureImage("In_1GT.pgm");

	img = seuillageOtsu(img);
	sauvegardeImage(img, "P5", "In_1PRES.pgm");


	return 0;
}