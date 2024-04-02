#include <stdlib.h>
#include <stdio.h>

#include "libCIPSI1.h"

void main(void)
{
	IMAGE test = allocationImage(256, 256);
	initialisationAleatoireImage(test, 0, 255);
	sauvegardeImage(test, "P5", "test");
	
	liberationImage(&test);
}