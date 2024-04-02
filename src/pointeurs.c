#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "libOutils.h"

/* passage par valeurs / paramètres d'entrée uniquement */
/* cas des variables, des structures et des tableaux */

void echange(int a, int b)
{
	int inter; /* ne sert que localement */

	printf("\tDans echange entree\n\t-> a : %d adresse %p et b : %d adresse %p\n", a, &a, b, &b);

	inter = b;
	b = a;
	a = inter;

	printf("\tDans echange sortie\n\t-> a : %d adresse %p et b : %d adresse %p\n", a, &a, b, &b);
}

typedef struct {
	int a;
	int b;
} TEMPORAIRE;

void echangeStruct(TEMPORAIRE tmp)
{
	int inter;

	printf("\tDans echange entree\n\t-> a : %d et b : %d adresse %p\n", tmp.a, tmp.b, &tmp); 
	
	inter = tmp.b;
	tmp.b = tmp.a;
	tmp.a = inter;

	printf("\tDans echange sortie\n\t-> a : %d et b : %d adresse %p\n", tmp.a, tmp.b, &tmp);
}

void echangeTab(int *pt) /* variable de type pointeur sur int, par son intermédiaire j'accède aux cases du tableau initial via déréférencement */
{
	int inter;

	printf("\tDans echangeTab entree t -> %p %p %d\n", pt, &pt, *pt);

	inter = pt[1];
	pt[1] = pt[0];
	pt[0] = inter;

	printf("\tDans echangeTab sortie t -> %p %p %d\n", pt, &pt, *pt);
}

void main(void)
{
		/* Section 1 : paramètres -> passage par valeur */
		/*int a = 1;
		int b = 2;

		printf("Avant echange\na : %d adresse %p et b : %d adresse %p\n", a, &a, b, &b);

		echange(a, b);

		printf("Apres echange\na : %d adresse %p et b : %d adresse %p\n", a, &a, b, &b);*/

		///* Section 2 : structure ? */

			
		/*TEMPORAIRE st = { 1,2 };

		printf("Avant echange\na : %d et b : %d adresse %p\n", st.a, st.b, &st);

		echangeStruct(st);

		printf("Apres echange\na : %d et b : %d adresse %p\n", st.a, st.b, &st);*/
		

		/* Section 3 : quid avec tableau statique mais même fonction ? */

		
		/*int t[2] = { 1,2 };
		printf("Avant echange\nt[0] : %d adresse %p et t[1] : %d adresse %p\n", t[0], &t[0], t[1], &t[1]);

		echange(t[0],t[1]);

		printf("Avant echange\nt[0] : %d adresse %p et t[1] : %d adresse %p\n", t[0], &t[0], t[1], &t[1]);*/
		

		/* section 4 : solution avec passage du tableau en paramètre */
		/*
		int t[2] = { 1,2 }; 
		printf("Rappels sur nom d'un tableau statique: t -> %p %p %p %d\n", t, &t, &t[0], *t);

		printf("Avant echange\nt[0] : %d adresse %p et t[1] : %d adresse %p\n", t[0], &t[0], t[1], &t[1]);

		echangeTab(t);

		printf("Apres echange\nt[0] : %d adresse %p et t[1] : %d adresse %p\n", t[0], &t[0], t[1], &t[1]);*/
		

		///* cela signifie donc que les tableaux ne sont pas gérés comme les paramètres précédents lors du SEUL passage par valeur */

		///* OBJECTIVEMENT, on aimerait pouvoir modifier le contenu de variables passées en paramètres via cette notion de pointeurs sans devoir passer par des tableeaux */

		///* section 5 : pointeurs */

		//int i = 0, *pi = &i; /* pi de type pointeur sur int */
		//int j = 1, *pj = &j; /* pj de type pointeur sur int */

		//printf("i : %d; j : %d\n", i, j);
		//printf("\t&i : %p, &j : %p -> pi : %p; pj : %p\n", &i,&j,pi,pj);
		//printf("\tpi : %d; pj : %d\n", *pi, *pj);

		///* grâce à pi,pj on accède indirectement à i et j */
		//*pi = j;
		//*pj = i;

		//printf("\t\tpi : %p -> %d; pj : %p -> %d\n", pi, *pi, pj, *pj);
		//// et influence sur i et j ?
		//printf("\t\ti -> %d; j -> %d\n", i, j);

		///* A faire : écriture et usage d'une fonction échange qui fonctionne :
		//	void echange2(int *pa, int *pb); */
	    // celle-ci mérite de devenir echangeInt à intégrer dans notre libOutils !!!

		/*int a = 5;
		int b = 9;

		echangeInt(&a, &b);

		printf("a = %d et b = %d \n", a, b);*/

		TEMPS test = decomposition_TEMPS(39745);
		printf("h = %d m = %d s = %d \n", test.Heure, test.Minutes, test.Secondes);

		int h = 0, m = 0, s = 0;
		decomposition(3661, &h, &m, &s);
		printf("h = %d m = %d s = %d \n", h, m, s);

		int tps = 0;
		lectureTemps(&tps);
		printf("Temps en secondes :  %d \n", tps);

		int n = 10;
		POINT t[10];
		generationAleatoirePoints(t, n, -5, 5);
		printf("Tableau de point : \n");
		for (int i = 0; i < n; i++)
		{
			printf("%d      ", i);
			affichePoint(t[i]);
		}

		float absMin, absMax;
		rechercheAbscissesExtremes(t, n, &absMin, &absMax);
		printf("Abs min : %f Abs max : %f \n", absMin, absMax);

		POINT PointProche, PointLoin;
		recherchePointsExtremes(t, n, &PointProche, &PointLoin);

		printf("Centre gravite : ");
		POINT centreGravite = centreGravitePoints(t, n);
		affichePoint(centreGravite);

		printf("Point proche : ");
		affichePoint(PointProche);

		printf("Point loin : ");
		affichePoint(PointLoin);

		printf("\n");
		for (int i = 0; i < n; i++)
		{
			printf("Dist pt%d avec centre gravite : %f \n",i, distancePoints(t[i], centreGravite));
		}
		
	

	system("pause");
}


