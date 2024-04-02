#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "libOutils.h"

void main(void)
{

		srand((unsigned)time(NULL));

		/* allocation dynamique vs tableau statique */
		//int t[100]; /* habituellement plus grande que nécessaire ... */
		//int n = 50;

		//printf("Nb elements ? ");
		//scanf("%d",&n);
		//initialisationAleatoireTableauInt(t, n, -10, 10);
		//affichageTableauInt(t, n);

		//system("pause");

		//int *tDyn = NULL;
		////initialisationAleatoireTableauInt(tDyn, n, -10, 10);
		////affichageTableauInt(tDyn, n); /* pb dans exécution */

		//printf("%p\n", tDyn);
		//tDyn = (int*)malloc(n*sizeof(t)); 
		//printf("%p\n", tDyn);

		// tDyn = (int*)calloc(n, sizeof(t)); // risque si on enchaîne les deux lignes ainsi ?
		//printf("%p\n", tDyn);

		//initialisationAleatoireTableauInt(tDyn, n, -10, 10);
		//affichageTableauInt(tDyn, n); 

		/* dans une fonction */
		/* structure TABLEAU_INT ? */


		/*TABLEAU_INT test = { NULL, 10 };

		test.tabDyn = AllocTableauInt(test);
		printf("%p\n", test.tabDyn);
		initialisationAleatoireTableauInt(test.tabDyn, test.size, -10, 10);
		affichageTableauInt(test.tabDyn, test.size);*/


		/*printf("Test lettre \n");

		char testLetter;
		for (int i = 0; i < 10; i++)
		{
			testLetter = tirageLettre();
			printf("%c \n", testLetter);
		}

		printf("Test mot \n");

		char* testMot;
		for (int i = 0; i < 10; i++)
		{
			testMot = tirageMot(5);
			for (int i = 0; i < 5; i++)
			{
				printf("%c", testMot[i]);
			}
			printf("\n");
		}

		printf("Test copie mot \n");
		char* Motcopie;
		for (int i = 0; i < 10; i++)
		{
			testMot = tirageMot(5);
			for (int i = 0; i < 5; i++)
			{
				printf("%c", testMot[i]);
			}
			printf("---->");
			Motcopie = copieMot(testMot, 5);
			for (int i = 0; i < 5; i++)
			{
				printf("%c", Motcopie[i]);
			}
			printf("\n");
		}

		printf("Test majuscule \n");
		for (int i = 0; i < 5; i++)
		{
			printf("%c", Motcopie[i]);
		}
		printf("\n");
		transformMotMajuscule(Motcopie);
		for (int i = 0; i < 5; i++)
		{
			printf("%c", Motcopie[i]);
		}
		printf("\n");
		printf("Test minuscule \n");
		for (int i = 0; i < 5; i++)
		{
			printf("%c", Motcopie[i]);
		}
		printf("\n");
		transformMotMinuscule(Motcopie);
		for (int i = 0; i < 5; i++)
		{
			printf("%c", Motcopie[i]);
		}

		printf("\n");
		char* motDupliquer = tirageMot(5);
		int taille2 = 0;
		printf("Test duplication \n");

		multiplicationVoyellesMot(Motcopie, 5, 2, motDupliquer, &taille2);
		for (int i = 0; i < 5; i++)
		{
			printf("%c", Motcopie[i]);
		}
		printf("\n");
		for (int i = 0; i < taille2; i++)
		{
			printf("%c", motDupliquer[i]);
		}
		printf("\n");*/

		MOT test = generationMot(5);
		for (int i = 0; i < test.longueur; i++)
		{
			printf("%c", test.data[i]);
		}




	system("pause");
}




