#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct INT_TABLEAU {
	int longueur;
	int* data;
} INT_TABLEAU;

typedef struct disque
{
	int rayon;
	double surface;
	double perimetre;
} DISQUE;

INT_TABLEAU question1(int n)
{
	INT_TABLEAU tab;
	tab.longueur = n;
	tab.data = (int*)malloc(tab.longueur * sizeof(int));
	return tab;
}

INT_TABLEAU question2(int n, int valMin, int valMax)
{
	INT_TABLEAU tab = question1(n);
	for (int i = 0; i < tab.longueur; i++)
		tab.data[i] = valMin + rand() % (valMax + 1 - valMin);
	return tab;
}

void affichageTableauInt(int t[], int n)
{

	for (int i = 0; i < n; i++)
		printf("%d ", t[i]);
	printf("\n");
}

DISQUE question3(int r)
{
	DISQUE disque;
	disque.rayon = r;
	disque.surface = acos(-1) * r * r;
	disque.perimetre = 2 * acos(-1) * r;

	return disque;
}

void question4(DISQUE d)
{
	printf("rayon: %d ->P = %f et S = %f \n", d.rayon, d.perimetre, d.surface);
}

DISQUE* question5(INT_TABLEAU rayons)
{
	DISQUE* disque = (DISQUE*)malloc(rayons.longueur * sizeof(DISQUE));

	for (int i = 0; i < rayons.longueur; i++)
	{
		disque[i] = question3(rayons.data[i]);
	}

	return disque;
}


void main(void)
{
	int nombre = 0;
	printf("Veuillez entrer un nombre entier \n", nombre);
	scanf("%d", &nombre);
	printf("Votre nombre : %d \n", nombre);

	INT_TABLEAU tab = question2(nombre, 0, 100);
	affichageTableauInt(tab.data, tab.longueur);

	DISQUE* disque = question5(tab);

	for (int i = 0; i < nombre; i++)
	{
		question4(disque[i]);
	}

	free(tab.data);
	free(disque);
}