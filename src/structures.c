/* liste des outils nécessaires inclus dans la librairie standard */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "libOutils.h"

void main(void)
{
	srand((unsigned)time(NULL));
	COULEUR jaune = { "jaune",255,255,0 }, blanc = { "blanc",255,255,255 }, noir = { "noir",0,0,0 };

	affichage(jaune);

	// comment passer 'j' en 'J' ?
	//jaune.couleur[0] = 'J';
	jaune.couleur[0] = jaune.couleur[0] - 'a' + 'A';
	affichage(jaune);

	// introduire fonction double distanceEuclidienne(c1,c2)
	double distEuclidienne = distanceEuclidienne(jaune, blanc);
	printf("distance euclidienne entre %s et %s : %lf\n", jaune.couleur, blanc.couleur, distEuclidienne);

	system("pause");

	POINT point1 = lecturePoint();
	POINT point2 = lecturePoint();
	affichePoint(point1);

	float distEucl = distancePoints(point1, point2);
	printf("distance euclidienne entre les deux points est : %f\n", distEucl);

	POINT milieu = milieuPoints(point1, point2);
	printf("Le milieu est : \n");
	affichePoint(milieu);

	printf("Test aleatoire : \n");

	POINT test[10];
	generationAleatoirePoints(test, 10, 3, 5);
	affichePoint(test[0]);

	printf("Test centre gravite : \n");

	POINT centreGravite = centreGravitePoints(test, 10);
	affichePoint(centreGravite);

	system("pause");

	COMPLEXE z1 = lectureComplexe();
	COMPLEXE z2 = lectureComplexe();
	afficheComplexe(z1);

	COMPLEXE conjugue = conjugueComplexe(z1);
	afficheComplexe(conjugue);

	double module = moduleComplexe(z1);
	printf("Le module est : %lf \n", module);

	COMPLEXE zAdd = additionComplexe(z1, z2);
	afficheComplexe(zAdd);

	COMPLEXE zMul = multiplicationComplexe(z1, z2);
	afficheComplexe(zMul);


	system("pause");
}