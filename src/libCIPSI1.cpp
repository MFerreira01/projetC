// libCIPSI1.c 
// Hubert Konik - filière IPSI

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "elementStructurant.h"
#include "libCIPSI1.h"

/* static -> non extern */

typedef struct
{
	int Nblig;
	int Nbcol;
	int* data;
	int** pixel;
} intIMAGE;


#pragma region POINTT

POINT lecturePoint(void)
{
	POINT point;

	printf("Entrer une abscisse \n");
	scanf("%f", &point.abscisse);
	printf("Entrer une ordonnee \n");
	scanf("%f", &point.ordonnee);

	return point;
}

void affichePoint(POINT point)
{
	printf("Abscisse : %f Ordonnee : %f \n", point.abscisse, point.ordonnee);
}


float distancePoints(POINT point1, POINT point2)
{
	return sqrt(pow(point2.abscisse - point1.abscisse, 2) + pow(point2.ordonnee - point1.ordonnee, 2));
}

POINT milieuPoints(POINT point1, POINT point2)
{
	POINT milieu;
	milieu.abscisse = (point1.abscisse + point2.abscisse) / 2;
	milieu.ordonnee = (point1.ordonnee + point2.ordonnee) / 2;

	return milieu;
}

void generationAleatoirePoints(POINT t[], int n, float min, float max)
{
	for (int i = 0; i < n; i++)
	{
		POINT point;
		float scale1 = rand() / (float)RAND_MAX;
		point.abscisse = min + scale1 * (max - min);
		float scale2 = rand() / (float)RAND_MAX;
		point.ordonnee = min + scale2 * (max - min);
		t[i] = point;
	}
}

POINT centreGravitePoints(POINT t[], int n)
{
	POINT centreGravite = { 0,0 };

	for (int i = 0; i < n; i++)
	{
		centreGravite.abscisse += t[i].abscisse;
		centreGravite.ordonnee += t[i].ordonnee;
	}
	centreGravite.abscisse /= n;
	centreGravite.ordonnee /= n;

	return centreGravite;
}

void rechercheAbscissesExtremes(POINT tab[], int n, float* absMin, float* absMax)
{
	*absMin = tab[0].abscisse;
	*absMax = tab[0].abscisse;


	for (int i = 1; i < n; i++)
	{
		if (tab[i].abscisse < *absMin)
		{
			*absMin = tab[i].abscisse;
		}

		if (tab[i].abscisse > *absMax)
		{
			*absMax = tab[i].abscisse;
		}
	}
}

void recherchePointsExtremes(POINT tab[], int n, POINT* ptDistMin, POINT* ptDistMax)
{

	POINT centreGravité = centreGravitePoints(tab, n);

	float distEuclmin = distancePoints(tab[0], centreGravité);
	float distEuclmax = distEuclmin;
	*ptDistMin = tab[0];
	*ptDistMax = tab[0];

	for (int i = 1; i < n; i++)
	{
		float tempDist = distancePoints(tab[i], centreGravité);
		if (tempDist < distEuclmin)
		{
			distEuclmin = tempDist;
			*ptDistMin = tab[i];
		}

		if (tempDist > distEuclmax)
		{
			distEuclmax = tempDist;
			*ptDistMax = tab[i];
		}
	}
}

#pragma endregion


static intIMAGE allocationIntImage(int Nblig, int Nbcol)
{
	intIMAGE mat = { 0,0,NULL,NULL };
	int i;

	mat.Nblig = Nblig;
	mat.Nbcol = Nbcol;
	mat.data = (int*)calloc(Nblig * Nbcol, sizeof(int)); /* mise à 0 par défaut, gestion des bords lors de l'agrandissement opéré dans l'étiquetage */
	if (mat.data == NULL)
		return(mat);
	mat.pixel = (int**)malloc(Nblig * sizeof(int*));
	if (mat.pixel == NULL) {
		free(mat.data);
		mat.data = NULL;
		return(mat);
	}
	for (i = 0; i < Nblig; i++)
		mat.pixel[i] = &mat.data[i * Nbcol];

	return(mat);
}

static void liberationIntImage(intIMAGE* img)
{
	if (img->data != NULL) {
		free(img->data);
		img->data = NULL;
	}
	if (img->pixel != NULL) {
		free(img->pixel);
		img->pixel = NULL;
	}
}

/* fonctionnalités -> exportables */

IMAGE allocationImage(int Nblig, int Nbcol)
{
	IMAGE mat = { 0,0,NULL,NULL };
	int i;

	mat.Nblig = Nblig;
	mat.Nbcol = Nbcol;
	mat.data = (unsigned char*)malloc(Nblig * Nbcol * sizeof(unsigned char));
	if (mat.data == NULL)
		return(mat);
	mat.pixel = (unsigned char**)malloc(Nblig * sizeof(unsigned char*));
	if (mat.pixel == NULL) {
		free(mat.data);
		mat.data = NULL;
		return(mat);
	}
	for (i = 0; i < Nblig; i++)
		mat.pixel[i] = &mat.data[i * Nbcol];

	return(mat);
}

void initialisationAleatoireImage(IMAGE img, int ngMin, int ngMax)
{
	int i, j;
	printf("Dans initialisation : img -> %p img.data -> %p img.pixel -> %p\n", &img, img.data, img.pixel);

	for (i = 0; i < img.Nblig; i++)
		for (j = 0; j < img.Nbcol; j++)
			img.pixel[i][j] = (unsigned char)(ngMin + rand() % (ngMax + 1 - ngMin));

	/* solution avec un seul indice
	for (i=0;i<img.Nblig*img.Nbcol;i++)
	img.data[i] = (unsigned char)(ngMin + rand() % (ngMax + 1 - ngMin));
	*/
}

void liberationImage(IMAGE* img)
{
	if (img->data != NULL) {
		free(img->data);
		img->data = NULL;
	}
	if (img->pixel != NULL) {
		free(img->pixel);
		img->pixel = NULL;
	}
}

IMAGE lectureImage(const char* in)
{
	FILE* F = NULL;
	IMAGE img = { 0,0,NULL };
	int dynamique = 0;

	if ((F = fopen(in, "r")) == NULL)
	{
		printf("Pb image inexistante");
	}
	else
	{
		char type[3];

		fgets(type, 3, F);
		fclose(F);
		/* selon le type ouverture binaire ou texte */
		if (strcmp(type, "P2") == 0)  /* cas ASCII niveaux de gris */
		{
			char buf;

			F = fopen(in, "r");

			/* lecture caractère après caractère compte-tenu de la diversité des entêtes possibles */
			fscanf(F, "%c", &type[0]);
			fscanf(F, "%c", &type[1]);
			fscanf(F, "%c", &buf); /* caractère espacement */

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) { /* possibilité d'utiliser également isdigit de la librairie standard <ctype.h> */
				img.Nbcol = img.Nbcol * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
				img.Nblig = img.Nblig * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
				dynamique = dynamique * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			/* début des data */

			//printf("Lecture image NG type %s avec %d lignes et %d colonnes...\n", type, img.Nblig, img.Nbcol);

			/* taille connue, allocation dynamique possible */
			img = allocationImage(img.Nblig, img.Nbcol);

			/* lecture pixel par pixel */
			{
				int i, j;
				int tmp;

				for (i = 0; i < img.Nblig; i++)
					for (j = 0; j < img.Nbcol; j++)
					{
						fscanf(F, "%d", &tmp);
						img.pixel[i][j] = (unsigned char)tmp;
					}
			}
		}
		else
			if (strcmp(type, "P5") == 0)  /* cas brut niveaux de gris */
			{
				char buf;

				F = fopen(in, "rb");

				/* lecture caractère après caractère compte-tenu de la diversité des entêtes possibles */
				type[0] = fgetc(F);
				type[1] = fgetc(F);
				buf = fgetc(F); /* caractère espacement */

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) { /* possibilité d'utiliser également isdigit de la librairie standard <ctype.h> */
					img.Nbcol = img.Nbcol * 10 + (buf - '0');
					buf = fgetc(F);
				}

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
					img.Nblig = img.Nblig * 10 + (buf - '0');
					buf = fgetc(F);
				}

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
					dynamique = dynamique * 10 + (buf - '0');
					buf = fgetc(F);
				}

				/* début des data */

				//printf("Lecture image NG type %s avec %d lignes et %d colonnes...\n", type, img.Nblig, img.Nbcol);

				/* taille connue, allocation dynamique possible */
				img = allocationImage(img.Nblig, img.Nbcol);

				/* lecture d'un bloc */
				fread(img.data, sizeof(unsigned char), img.Nbcol * img.Nblig, F);
			}
			else
				printf("Format non supporte pour l'instant...\n");
		fclose(F);
	}
	return img;
}

void sauvegardeImage(IMAGE img, const char* type, const char* out)
{
	FILE* F = NULL;

	if (img.data) /* image non vide */
	{
		printf("Sauvegarde image au type %s avec %d lignes et %d colonnes...\n", type, img.Nblig, img.Nbcol);
		/* selon le type ouverture binaire ou texte */
		if (strcmp(type, "P2") == 0)  /* cas ASCII niveaux de gris */
		{
			F = fopen(out, "w");

			fprintf(F, "%s\n", type);
			fprintf(F, "# Created by TSE FISA IPSI\n");
			fprintf(F, "%d %d %d\n", img.Nbcol, img.Nblig, 255);
			/* sauvegarde pixel par pixel */
			{
				int i, j;

				for (i = 0; i < img.Nblig; i++)
					for (j = 0; j < img.Nbcol; j++)
						fprintf(F, "%d ", img.pixel[i][j]);
			}
			fclose(F);
		}
		else
			if (strcmp(type, "P5") == 0)  /* cas brut niveaux de gris */
			{
				char tmp[255];

				F = fopen(out, "wb");

				fputs("P5\n", F);
				fputs("# Created by TSE FISA IPSI\n", F);
				sprintf(tmp, "%d %d %d\n", img.Nbcol, img.Nblig, 255);
				fputs(tmp, F);
				/* sauvegarde par bloc */
				fwrite(img.data, sizeof(unsigned char), img.Nbcol * img.Nblig, F);
				fclose(F);
			}
	}
	else
		printf("Image vide\n");
}

IMAGERGB allocationImageRGB(int Nblig, int Nbcol)
{
	IMAGERGB mat = { 0,0,NULL,NULL };
	int i;

	mat.Nblig = Nblig;
	mat.Nbcol = Nbcol;
	mat.data = (RGB*)malloc(Nblig * Nbcol * sizeof(RGB));
	if (mat.data == NULL)
		return(mat);
	mat.pixel = (RGB**)malloc(Nblig * sizeof(RGB*));
	if (mat.pixel == NULL) {
		free(mat.data);
		mat.data = NULL;
		return(mat);
	}
	for (i = 0; i < Nblig; i++)
		mat.pixel[i] = &(mat.data[i * Nbcol]);

	return(mat);
}

void initialisationAleatoireImageRGB(IMAGERGB img, int ngMin, int ngMax)
{
	int i, j;
	printf("Dans initialisation : img -> %p img.data -> %p img.pixel -> %p\n", &img, img.data, img.pixel);

	for (i = 0; i < img.Nblig * img.Nbcol; i++)
	{
		img.data[i].R = (unsigned char)(ngMin + rand() % (ngMax + 1 - ngMin));
		img.data[i].G = (unsigned char)(ngMin + rand() % (ngMax + 1 - ngMin));
		img.data[i].B = (unsigned char)(ngMin + rand() % (ngMax + 1 - ngMin));
	}
}

int* histogrammeImageRGB(IMAGERGB img, int choix, int n)
{
	int* h = NULL; /* RGB pas possible car UC, donc 3xint avec R G B successivement pour chaque niveau */

	if (img.data)
	{
		int i;
		if (n <= 0 || n > 256)
		{
			n = 256;
		}
		int puissance = log(n) / log(2);
		int bins = 256 >> (8 - puissance);

		h = (int*)calloc(3 * bins, sizeof(int));

		for (i = 0; i < img.Nbcol * img.Nblig; i++)
		{
			h[3 * (((int)img.data[i].R) >> (8 - puissance))] += 1; /* R */
			h[3 * (((int)img.data[i].G) >> (8 - puissance)) + 1] += 1; /* G */
			h[3 * (((int)img.data[i].B) >> (8 - puissance)) + 2] += 1; /* B */
		}

		if (choix)
		{
			/* sauvegarde dans histo.csv */
			FILE* F;

			F = fopen("res/histoRGB.csv", "w");
			int i;
			for (i = 0; i < bins; i++)
				fprintf(F, "%d ; %d; %d; %d\n", i, h[3 * i], h[3 * i + 1], h[3 * i + 2]);
			fclose(F);
		}
	}

	return h;
}

void liberationImageRGB(IMAGERGB* m)
{
	if (m->data != NULL) {
		free(m->data);
		m->data = NULL;
	}
	if (m->pixel != NULL) {
		free(m->pixel);
		m->pixel = NULL;
	}
}

IMAGERGB lectureImageRGB(const char* in)
{
	FILE* F = NULL;
	IMAGERGB img = { 0,0,NULL };
	int dynamique = 0;

	if ((F = fopen(in, "r")) == NULL)
	{
		printf("Pb image inexistante");
	}
	else
	{
		char type[3];

		fgets(type, 3, F);
		fclose(F);
		/* selon le type ouverture binaire ou texte */
		if (strcmp(type, "P3") == 0)  /* cas ASCII couleur */
		{
			char tmp[255] = "";
			char buf;

			F = fopen(in, "r");

			/* lecture caractère après caractère compte-tenu de la diversité des entêtes possibles */
			fscanf(F, "%c", &type[0]);
			fscanf(F, "%c", &type[1]);
			fscanf(F, "%c", &buf); /* caractère espacement */

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) { /* possibilité d'utiliser également isdigit de la librairie standard <ctype.h> */
				img.Nbcol = img.Nbcol * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
				img.Nblig = img.Nblig * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
				dynamique = dynamique * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			/* début des data */

			printf("Lecture image RGB type %s avec %d lignes et %d colonnes...\n", type, img.Nblig, img.Nbcol);

			/* taille connue, allocation dynamique possible */
			img = allocationImageRGB(img.Nblig, img.Nbcol);

			/* lecture pixel par pixel */
			{
				int i, j;
				int tmp;

				for (i = 0; i < img.Nblig; i++)
					for (j = 0; j < img.Nbcol; j++)
					{
						fscanf(F, "%d", &tmp);
						img.pixel[i][j].R = (unsigned char)tmp;
						fscanf(F, "%d", &tmp);
						img.pixel[i][j].G = (unsigned char)tmp;
						fscanf(F, "%d", &tmp);
						img.pixel[i][j].B = (unsigned char)tmp;
					}
			}
		}
		else
			if (strcmp(type, "P6") == 0)  /* cas brut couleur */
			{
				char buf;

				F = fopen(in, "rb");

				/* lecture caractère après caractère compte-tenu de la diversité des entêtes possibles */
				type[0] = fgetc(F);
				type[1] = fgetc(F);
				buf = fgetc(F); /* caractère espacement */

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) { /* possibilité d'utiliser également isdigit de la librairie standard <ctype.h> */
					img.Nbcol = img.Nbcol * 10 + (buf - '0');
					buf = fgetc(F);
				}

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
					img.Nblig = img.Nblig * 10 + (buf - '0');
					buf = fgetc(F);
				}

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
					dynamique = dynamique * 10 + (buf - '0');
					buf = fgetc(F);
				}

				/* début des data */

				printf("Lecture image RGB type %s avec %d lignes et %d colonnes...\n", type, img.Nblig, img.Nbcol);

				/* taille connue, allocation dynamique possible */
				img = allocationImageRGB(img.Nblig, img.Nbcol);

				/* lecture d'un bloc */
				fread(img.data, sizeof(RGB), img.Nbcol * img.Nblig, F);
			}
			else
				printf("Format non supporte pour l'instant...\n");
		fclose(F);
	}
	return img;
}

void sauvegardeImageRGB(IMAGERGB img, const char* type, const char* out)
{
	FILE* F = NULL;

	if (img.data) /* image non vide */
	{
		printf("Sauvegarde image au type %s avec %d lignes et %d colonnes...\n", type, img.Nblig, img.Nbcol);
		/* selon le type ouverture binaire ou texte */
		if (strcmp(type, "P3") == 0)  /* cas ASCII couleur */
		{
			F = fopen(out, "w");

			fprintf(F, "%s\n", type);
			fprintf(F, "# Created by TSE FISA IPSI\n");
			fprintf(F, "%d %d %d\n", img.Nbcol, img.Nblig, 255);
			/* sauvegarde pixel par pixel */
			{
				int i, j;

				for (i = 0; i < img.Nblig; i++)
					for (j = 0; j < img.Nbcol; j++) {
						fprintf(F, "%d ", img.pixel[i][j].R);
						fprintf(F, "%d ", img.pixel[i][j].G);
						fprintf(F, "%d ", img.pixel[i][j].B);
					}
				fclose(F);
			}
		}
		else
			if (strcmp(type, "P6") == 0)  /* cas brut couleur */
			{
				char tmp[255];

				F = fopen(out, "wb");

				fputs("P6\n", F);
				fputs("# Created by TSE FISA IPSI\n", F);
				sprintf(tmp, "%d %d %d\n", img.Nbcol, img.Nblig, 255);
				fputs(tmp, F);

				/* sauvegarde par bloc */
				fwrite(img.data, sizeof(RGB), img.Nbcol * img.Nblig, F);
				fclose(F);
			}
	}
	else
		printf("Image vide\n");
}

IMAGE inverseImage(IMAGE img)
{
	IMAGE out = { 0,0,NULL,NULL };
	int* lut = NULL;
	int i;

	lut = (int*)calloc(256, sizeof(int)); /* LUT pour optimiser */
	for (i = 0; i < 256; i++)
		lut[i] = 255 - i;

	out = allocationImage(img.Nblig, img.Nbcol);
	for (i = 0; i < img.Nbcol * img.Nblig; i++)
		out.data[i] = lut[img.data[i]];

	free(lut);

	return out;
}

IMAGE seuillageImage(IMAGE img, int sInf, int sSup)
{
	IMAGE out = { 0,0,NULL,NULL };
	int* lut = NULL;
	int i;

	lut = (int*)calloc(256, sizeof(int));
	for (i = sInf; i <= sSup; i++)
		lut[i] = 255;

	out = allocationImage(img.Nblig, img.Nbcol);
	for (i = 0; i < img.Nbcol * img.Nblig; i++)
		out.data[i] = lut[img.data[i]];

	free(lut);

	return out;
}


IMAGE planImage(IMAGERGB img, int plan)
{
	IMAGE out = { 0,0,NULL,NULL };
	int i;

	out = allocationImage(img.Nblig, img.Nbcol);
	switch (plan)
	{
	case 0: /* plan rouge */
		for (i = 0; i < out.Nbcol * out.Nblig; i++)
			out.data[i] = img.data[i].R;
		break;
	case 1: /* plan vert */
		for (i = 0; i < out.Nbcol * out.Nblig; i++)
			out.data[i] = img.data[i].G;
		break;
	case 2: /* plan bleu */
		for (i = 0; i < out.Nbcol * out.Nblig; i++)
			out.data[i] = img.data[i].B;
		break;
	}
	return(out);
}

IMAGE luminanceImage(IMAGERGB img, float r, float g, float b)
{
	IMAGE out = { 0,0,NULL,NULL };
	int i;

	out = allocationImage(img.Nblig, img.Nbcol);

	for (i = 0; i < out.Nbcol * out.Nblig; i++)
		out.data[i] = (unsigned char)((float)img.data[i].R * r + (float)img.data[i].G * g + (float)img.data[i].B * b);
	return(out);
}


int* histogrammeImage(IMAGE img, int choix, int n)
{
	int* h = NULL;

	if (img.data)
	{
		int i;
		if (n <= 0 || n > 256)
		{
			n = 256;
		}
		int puissance = log(n) / log(2);
		int bins = 256 >> (8 - puissance);

		h = (int*)calloc(bins, sizeof(int));

		for (i = 0; i < img.Nbcol * img.Nblig; i++)
			h[((int)img.data[i]) >> (8 - puissance)] += 1;

		if (choix)
		{
			/* sauvegarde dans histo.csv */
			FILE* F;

			F = fopen("res/histo.csv", "w");
			int i;
			for (i = 0; i < bins; i++)
				fprintf(F, "%d ; %d\n", i, h[i]);
			fclose(F);
		}
	}

	return h;
}

IMAGE expansionImage(IMAGE img, int outMin, int outMax)
{
	IMAGE out = { 0,0,NULL,NULL };
	int* lut = NULL;
	int i;
	float a, b;
	int mini = 255, maxi = 0;

	for (i = 0; i < img.Nblig * img.Nbcol; i++)
	{
		mini = (img.data[i] < mini) ? img.data[i] : mini;
		maxi = (img.data[i] > maxi) ? img.data[i] : maxi;
	}

	a = (float)(outMax - outMin) / ((float)(maxi - mini));
	b = (float)outMin - a * mini;

	lut = (int*)calloc(256, sizeof(int));
	for (i = mini; i <= maxi; i++)
		lut[i] = (int)(a * i + b);

	out = allocationImage(img.Nblig, img.Nbcol);
	for (i = 0; i < img.Nbcol * img.Nblig; i++)
		out.data[i] = lut[img.data[i]];

	free(lut);

	return out;
}

IMAGE egalisationImage(IMAGE img)
{
	IMAGE out = { 0,0,NULL,NULL };
	int* h = histogrammeImage(img, 0, 256);
	int* hC = NULL;
	int* lut = NULL;
	int i;

	hC = (int*)calloc(256, sizeof(int));
	hC[0] = h[0];
	for (i = 1; i < 256; i++)
		hC[i] = hC[i - 1] + h[i];
	free(h);
	h = NULL;

	lut = (int*)calloc(256, sizeof(int));
	for (i = 0; i < 256; i++)
		lut[i] = (int)((255 / (float)(img.Nbcol * img.Nblig)) * hC[i]);
	free(hC);
	hC = NULL;

	out = allocationImage(img.Nblig, img.Nbcol);
	for (i = 0; i < img.Nbcol * img.Nblig; i++)
		out.data[i] = lut[img.data[i]];
	free(lut);

	return(out);
}

SIGNATURES statistiquesImage(IMAGE img)
{
	SIGNATURES sig;
	int i;
	double som = 0, som2 = 0;
	int somme, moitPop = (img.Nbcol * img.Nblig) / 2;
	int* h = histogrammeImage(img, 0, 256);

	for (i = 0; i < img.Nbcol * img.Nblig; i++) {
		som += (double)img.data[i];
		som2 += (double)img.data[i] * (double)img.data[i];
	}

	som /= (double)(img.Nblig * img.Nbcol);
	som2 = sqrt(som2 / (double)(img.Nblig * img.Nbcol) - som * som);

	sig.moyenne = som;
	sig.ecartType = som2;

	i = 0;
	while (h[i] == 0)
		i += 1;
	sig.min = i;

	i = 255;
	while (h[i] == 0)
		i -= 1;
	sig.max = i;

	i = 0;
	somme = h[i];
	while (somme < moitPop) {
		i += 1;
		if (i < 256)
			somme += h[i];
	}
	sig.mediane = i;

	free(h);
	h = NULL;

	return sig;
}

IMAGE seuillageOtsu(IMAGE img)
{
	IMAGE out = { 0, 0, NULL, NULL };
	int* h = histogrammeImage(img, 0, 256);
	int* hC = NULL;

	double* tab = NULL;
	int i, seuil;
	double M1, M2;
	double w1;
	int* lut = NULL;
	int min, max;

	/* recherche min et max */
	i = 0;
	while (h[i] == 0)
		i++;
	min = i;
	i = 255;
	while (h[i] == 0)
		i--;
	max = i;

	hC = (int*)calloc(256, sizeof(int));
	hC[0] = h[0];
	for (i = 1; i < 256; i++)
		hC[i] = hC[i - 1] + h[i];

	tab = (double*)calloc(256, sizeof(double));

	/* parcours entre min et max pour éviter divisions par 0 */
	/* initialisation */
	M1 = min;
	seuil = min;
	w1 = (double)hC[min] / (double)(img.Nbcol * img.Nblig);
	M2 = 0;
	for (int i = min + 1; i <= max; i++)
		M2 += (double)h[i] * i;
	M2 /= (double)(hC[max] - h[min]);
	tab[min] = w1 * (1 - w1) * (M1 - M2) * (M1 - M2);

	// parcours
	for (int i = min + 1; i < max; i++) {
		M1 = ((double)hC[i - 1] * M1 + (double)h[i] * i) / hC[i];
		M2 = ((double)(hC[255] - hC[i - 1]) * M2 - (double)(h[i] * i)) / (double)(hC[255] - hC[i]);
		w1 = (double)hC[i] / (double)(img.Nbcol * img.Nblig);
		tab[i] = w1 * (1 - w1) * (M1 - M2) * (M1 - M2);
		if (tab[i] > tab[seuil])
			seuil = i;
	}

	free(h); h = NULL;
	free(hC); hC = NULL;

	free(tab);

	lut = (int*)calloc(256, sizeof(int));
	for (i = seuil; i <= max; i++)
		lut[i] = 255;

	out = allocationImage(img.Nblig, img.Nbcol);
	for (i = 0; i < img.Nbcol * img.Nblig; i++)
		out.data[i] = lut[img.data[i]];

	free(lut);
	return out;
}

/* étiquetage V8 */
IMAGE labelImage(IMAGE img, int* nbComp)
{
	IMAGE out = { 0,0,NULL,NULL };

	int i, ii, j, jj;

	int k = 1, kk;
	int eps;
	int predNonNul[5];
	int nbPredNonNuls;

	int nbMaxEtiquettes = img.Nblig * img.Nbcol;
	intIMAGE withBords = { 0,0,NULL,NULL };

	withBords = allocationIntImage(img.Nblig + 2, img.Nbcol + 2);

	for (i = 0, ii = 1; i < img.Nblig; i++, ii++) // pure copie 
		for (j = 0, jj = 1; j < img.Nbcol; j++, jj++)
			withBords.pixel[ii][jj] = (int)img.pixel[i][j];

	int* tableEtiquette = NULL;
	tableEtiquette = (int*)calloc(nbMaxEtiquettes, sizeof(int));

	for (kk = 0; kk < nbMaxEtiquettes; kk++) {
		tableEtiquette[kk] = kk;
	}

	for (i = 1; i < withBords.Nblig - 1; i++)
		for (j = 1; j < withBords.Nbcol - 1; j++) {
			if (withBords.pixel[i][j] != 0) {
				// voisinage V8 
				int pred1 = withBords.pixel[i][j - 1];
				int pred2 = withBords.pixel[i - 1][j - 1];
				int pred3 = withBords.pixel[i - 1][j];
				int pred4 = withBords.pixel[i - 1][j + 1];

				nbPredNonNuls = 0;
				if (pred1) predNonNul[nbPredNonNuls++] = pred1;
				if (pred2) predNonNul[nbPredNonNuls++] = pred2;
				if (pred3) predNonNul[nbPredNonNuls++] = pred3;
				if (pred4) predNonNul[nbPredNonNuls++] = pred4;

				if (nbPredNonNuls == 0) {
					withBords.pixel[i][j] = k;
					k++;
				}
				else {
					eps = 0;
					int minPred = tableEtiquette[predNonNul[0]];
					int maxPred = tableEtiquette[predNonNul[0]];
					while (eps < nbPredNonNuls) {
						if (tableEtiquette[predNonNul[eps]] < minPred) minPred = tableEtiquette[predNonNul[eps]];
						if (tableEtiquette[predNonNul[eps]] > maxPred) maxPred = tableEtiquette[predNonNul[eps]];
						eps++;
					}
					if (minPred == maxPred)
						withBords.pixel[i][j] = minPred;
					else {
						withBords.pixel[i][j] = minPred;
						for (eps = 0; eps < nbPredNonNuls; eps++) {
							int beta = predNonNul[eps];
							while (tableEtiquette[beta] != minPred) {
								int m = tableEtiquette[beta];
								tableEtiquette[beta] = minPred;
								beta = m;
							}
						}
					}
				}
			}
		}


	// actualisation de la table d'équivalence
	for (int kk = 1; kk < k; kk++) {
		int m = kk;
		while (tableEtiquette[m] != m)
			m = tableEtiquette[m];
		tableEtiquette[kk] = m;
	}

	int* etiquettes = (int*)calloc(k + 1, sizeof(int));

	// histo pour repérer les trous
	for (int kk = 1; kk < k; kk++)
		etiquettes[tableEtiquette[kk]]++;

	// on remet à jour les index (etiquetage définitif hors trou)
	etiquettes[0] = 0;
	int compt = 1;
	for (int kk = 1; kk < k; kk++) {
		if (etiquettes[kk])
			etiquettes[kk] = compt++;
	}

	for (i = 0; i < withBords.Nblig; i++)
		for (j = 0; j < withBords.Nbcol; j++) {
			withBords.pixel[i][j] = etiquettes[tableEtiquette[withBords.pixel[i][j]]];
		}

	free(etiquettes);
	free(tableEtiquette);

	out = allocationImage(img.Nblig, img.Nbcol);

	*nbComp = compt - 1;
	for (i = 0, ii = 1; i < img.Nblig; i++, ii++)
		for (j = 0, jj = 1; j < img.Nbcol; j++, jj++)
			out.pixel[i][j] = (unsigned char)withBords.pixel[ii][jj];

	liberationIntImage(&withBords);

	return out;
}

IMAGERGB colorisationImage(IMAGE img, char* table)
{
	IMAGERGB imgRGB = allocationImageRGB(img.Nblig, img.Nbcol);
	imgRGB.data->R = img.data;
	imgRGB.data->G = img.data;
	imgRGB.data->B = img.data;

	RGB* LUT = (RGB*)calloc(256, sizeof(RGB));

	int ndg, R, G, B;
	char* ligne[256];
	FILE* lut = fopen(table, "r");
	while (fgets(ligne, 255, lut) != NULL)
	{
		sscanf(ligne, "%d %d %d %d", &ndg, &R, &G, &B);
		LUT[ndg].R = R;
		LUT[ndg].G = G;
		LUT[ndg].B = B;
	}
	fclose(lut);

	for (int i = 0; i < img.Nbcol * img.Nblig; i++)
	{
		imgRGB.data[i].R = LUT[img.data[i]].R;
		imgRGB.data[i].G = LUT[img.data[i]].G;
		imgRGB.data[i].B = LUT[img.data[i]].B;
	}

	return imgRGB;
}

double distanceHistogrammeImage(int* h1, int* h2, int taille)
{
	double res = 0;

	for (int i = 0; i < taille; i++)
	{
		res = res + pow((h1[i] - h2[i]), 2);
	}

	res = res * (1 / taille);
	res = sqrt(res);

	return res;
}

SIGNATURE_COMPOSANTE_CONNEXE* signaturesImage(IMAGE img, int nbComp)
{
	SIGNATURE_COMPOSANTE_CONNEXE* SignatureCC = (SIGNATURE_COMPOSANTE_CONNEXE*)calloc((nbComp + 1), sizeof(SIGNATURE_COMPOSANTE_CONNEXE));

	//Histogramme image labelisé donne surface des composantes
	int* histo = (int*)malloc(256 * sizeof(int));
	histo = histogrammeImage(img, 0, 256);

	//Histogramme image contour donne périmetre composantes
	int* histoContour = (int*)malloc(256 * sizeof(int));
	IMAGE imgContour = contourImage(img, 4);
	histoContour = histogrammeImage(imgContour, 0, 256);

	//SURFACE + RAYON + PERIMETRE + COMPACITE
	for (int i = 0; i < nbComp + 1; i++)
	{
		SignatureCC[i].surface = histo[i];
		SignatureCC[i].rayon = sqrt(SignatureCC[i].surface / 3.14159265);
		SignatureCC[i].perimetre = histoContour[i];
		SignatureCC[i].compacite = (SignatureCC[i].perimetre * SignatureCC[i].perimetre) / (4 * 3.14159265 * SignatureCC[i].surface);
		SignatureCC[i].suppr = 1;
	}

	//CENTRE GRAVITE
	int compo;
	for (int i = 0; i < img.Nblig; i++)
	{
		for (int j = 0; j < img.Nbcol; j++)
		{
			compo = img.pixel[i][j];
			SignatureCC[compo].CG.abscisse = (SignatureCC[compo].CG.abscisse + j);
			SignatureCC[compo].CG.ordonnee = (SignatureCC[compo].CG.ordonnee + i);
		}
	}

	for (int compo = 0; compo < nbComp + 1; compo++)
	{
		SignatureCC[compo].CG.abscisse = (SignatureCC[compo].CG.abscisse / SignatureCC[compo].surface);
		SignatureCC[compo].CG.ordonnee = (SignatureCC[compo].CG.ordonnee / SignatureCC[compo].surface);
	}

	//BORDS
	//BORD HAUT
	for (int j = 0; j < img.Nbcol; j++)
	{
		compo = img.pixel[0][j];
		if (compo != 0)
		{
			SignatureCC[compo].bord = 1;
		}
	}
	//BORD BAS
	for (int j = 0; j < img.Nbcol; j++)
	{
		compo = img.pixel[img.Nblig - 1][j];
		if (compo != 0)
		{
			SignatureCC[compo].bord = 1;
		}
	}
	//BORD GAUCHE
	for (int i = 0; i < img.Nblig; i++)
	{
		compo = img.pixel[i][0];
		if (compo != 0)
		{
			SignatureCC[compo].bord = 1;
		}
	}
	//BORD DROIT
	for (int i = 0; i < img.Nblig; i++)
	{
		compo = img.pixel[i][img.Nbcol - 1];
		if (compo != 0)
		{
			SignatureCC[compo].bord = 1;
		}
	}

	free(histo);
	free(histoContour);
	liberationImage(&imgContour);
	return SignatureCC;
}

IMAGE SupprimerComposanteBord(IMAGE img, int nbComp)
{
	IMAGE SansObjetBord = allocationImage(img.Nblig, img.Nbcol);
	SIGNATURE_COMPOSANTE_CONNEXE* SignatureCC = signaturesImage(img, nbComp);
	int* LUT = (int*)calloc((nbComp + 1), sizeof(int));
	for (int i = 1; i < nbComp + 1; i++)
	{
		if (SignatureCC[i].bord != 0)
		{
			LUT[i] = 0;
		}
		else
		{
			LUT[i] = i;
		}
	}

	SansObjetBord = ChangerLUT(img, LUT);

	free(SignatureCC);
	return SansObjetBord;
}

IMAGE SupprimerComposante(IMAGE img, int nbComp, SIGNATURE_COMPOSANTE_CONNEXE* SignatureCC)
{
	IMAGE SansObjetIndesirable = allocationImage(img.Nblig, img.Nbcol);
	int* LUT = (int*)calloc((nbComp + 1), sizeof(int));
	for (int i = 1; i < nbComp + 1; i++)
	{
		if (SignatureCC[i].suppr != 0)
		{
			LUT[i] = 0;
		}
		else
		{
			//LUT[i] = i;
			LUT[i] = 255;
		}
	}

	SansObjetIndesirable = ChangerLUT(img, LUT);

	return SansObjetIndesirable;
}

IMAGE ChangerLUT(IMAGE img, int* LUT)
{
	IMAGE imgLUT = allocationImage(img.Nblig, img.Nbcol);
	for (int i = 0; i < img.Nblig * img.Nbcol; i++)
	{
		int compo = img.data[i];
		imgLUT.data[i] = LUT[compo];
	}

	return imgLUT;
}

IMAGE erosionImage(IMAGE img, int voisinage)
{
	IMAGE imgErode = allocationImage(img.Nblig, img.Nbcol);

	if (voisinage == 4)
	{
		//Pixel haut gauche
		imgErode.pixel[0][0] = min(img.pixel[0][0], min(img.pixel[1][0], img.pixel[0][1]));
		//Pixel haut droit
		imgErode.pixel[0][img.Nbcol - 1] = min(img.pixel[0][img.Nbcol - 1], min(img.pixel[1][img.Nbcol - 1], img.pixel[0][img.Nbcol - 2]));
		//Pixel bas gauche
		imgErode.pixel[img.Nblig - 1][0] = min(img.pixel[img.Nblig - 1][0], min(img.pixel[img.Nblig - 2][0], img.pixel[img.Nblig - 1][1]));
		//Pixel bas droit
		imgErode.pixel[img.Nblig - 1][img.Nbcol - 1] = min(img.pixel[img.Nblig - 1][img.Nbcol - 1], min(img.pixel[img.Nblig - 1][img.Nbcol - 2], img.pixel[img.Nblig - 2][img.Nbcol - 1]));

		//BORD HAUT
		for (int j = 1; j < img.Nbcol - 1; j++)
		{
			imgErode.pixel[0][j] = min(min(img.pixel[0][j], img.pixel[0][j - 1]), min(img.pixel[1][j], img.pixel[0][j + 1]));
		}
		//BORD BAS
		for (int j = 1; j < img.Nbcol - 1; j++)
		{
			imgErode.pixel[img.Nblig - 1][j] = min(min(img.pixel[img.Nblig - 1][j], img.pixel[img.Nblig - 1][j - 1]), min(img.pixel[img.Nblig - 2][j], img.pixel[img.Nblig - 1][j + 1]));
		}
		//BORD GAUCHE
		for (int i = 1; i < img.Nblig - 1; i++)
		{
			imgErode.pixel[i][0] = min(min(img.pixel[i][0], img.pixel[i - 1][0]), min(img.pixel[i + 1][0], img.pixel[i][1]));
		}
		//BORD DROIT
		for (int i = 1; i < img.Nblig - 1; i++)
		{
			imgErode.pixel[i][img.Nbcol - 1] = min(min(img.pixel[i][img.Nbcol - 1], img.pixel[i - 1][img.Nbcol - 1]), min(img.pixel[i + 1][img.Nbcol - 1], img.pixel[i][img.Nbcol - 2]));
		}

		//MILIEU IMAGE
		for (int i = 1; i < img.Nblig - 1; i++)
		{
			for (int j = 1; j < img.Nbcol - 1; j++)
			{
				imgErode.pixel[i][j] = min(min(img.pixel[i][j], img.pixel[i][j]), min(min(img.pixel[i - 1][j], img.pixel[i + 1][j]), min(img.pixel[i][j - 1], img.pixel[i][j + 1])));
			}
		}
	}
	if (voisinage == 8)
	{
		//Pixel haut gauche
		imgErode.pixel[0][0] = min(min(img.pixel[0][0], img.pixel[1][1]), min(img.pixel[1][0], img.pixel[0][1]));
		//Pixel haut droit
		imgErode.pixel[0][img.Nbcol - 1] = min(min(img.pixel[0][img.Nbcol - 1], img.pixel[1][img.Nbcol - 2]), min(img.pixel[1][img.Nbcol - 1], img.pixel[0][img.Nbcol - 2]));
		//Pixel bas gauche
		imgErode.pixel[img.Nblig - 1][0] = min(min(img.pixel[img.Nblig - 1][0], img.pixel[img.Nblig - 2][1]), min(img.pixel[img.Nblig - 2][0], img.pixel[img.Nblig - 1][1]));
		//Pixel bas droit
		imgErode.pixel[img.Nblig - 1][img.Nbcol - 1] = min(min(img.pixel[img.Nblig - 1][img.Nbcol - 1], img.pixel[img.Nblig - 2][img.Nbcol - 2]), min(img.pixel[img.Nblig - 1][img.Nbcol - 2], img.pixel[img.Nblig - 2][img.Nbcol - 1]));

		//BORD HAUT
		for (int j = 1; j < img.Nbcol - 1; j++)
		{
			imgErode.pixel[0][j] = min(min(img.pixel[1][j - 1], img.pixel[1][j + 1]), min(min(img.pixel[0][j], img.pixel[0][j - 1]), min(img.pixel[1][j], img.pixel[0][j + 1])));
		}
		//BORD BAS
		for (int j = 1; j < img.Nbcol - 1; j++)
		{
			imgErode.pixel[img.Nblig - 1][j] = min(min(img.pixel[img.Nblig - 1][j - 1], img.pixel[img.Nblig - 1][j + 1]), min(min(img.pixel[img.Nblig - 1][j], img.pixel[img.Nblig - 1][j - 1]), min(img.pixel[img.Nblig - 2][j], img.pixel[img.Nblig - 1][j + 1])));
		}
		//BORD GAUCHE
		for (int i = 1; i < img.Nblig - 1; i++)
		{
			imgErode.pixel[i][0] = min(min(img.pixel[i + 1][1], img.pixel[i - 1][1]), min(min(img.pixel[i][0], img.pixel[i - 1][0]), min(img.pixel[i + 1][0], img.pixel[i][1])));
		}
		//BORD DROIT
		for (int i = 1; i < img.Nblig - 1; i++)
		{
			imgErode.pixel[i][img.Nbcol - 1] = min(min(img.pixel[i + 1][img.Nbcol - 2], img.pixel[i - 1][img.Nbcol - 2]), min(min(img.pixel[i][img.Nbcol - 1], img.pixel[i - 1][img.Nbcol - 1]), min(img.pixel[i + 1][img.Nbcol - 1], img.pixel[i][img.Nbcol - 2])));
		}

		//Milieu image
		for (int i = 1; i < img.Nblig - 1; i++)
		{
			for (int j = 1; j < img.Nbcol - 1; j++)
			{
				//imgErode.pixel[i][j] = min(img.pixel[i][j], img.pixel[i][j]) + min(img.pixel[i - 1][j], img.pixel[i + 1][j]) + min(img.pixel[i][j - 1], img.pixel[i][j + 1]) + min(img.pixel[i - 1][j - 1], img.pixel[i - 1][j + 1]) + min(img.pixel[i + 1][j - 1], img.pixel[i + 1][j + 1]);

				imgErode.pixel[i][j] = min(min(min(img.pixel[i][j], img.pixel[i][j]), min(img.pixel[i - 1][j], img.pixel[i + 1][j])), min(min(min(img.pixel[i][j - 1], img.pixel[i][j + 1]), min(img.pixel[i - 1][j - 1], img.pixel[i - 1][j + 1])), min(img.pixel[i + 1][j - 1], img.pixel[i + 1][j + 1])));
			}
		}
	}

	return imgErode;
}

IMAGE dilatationImage(IMAGE img, int voisinage)
{
	IMAGE imgDilate = allocationImage(img.Nblig, img.Nbcol);

	if (voisinage == 4)
	{
		//Pixel haut gauche
		imgDilate.pixel[0][0] = max(img.pixel[0][0], max(img.pixel[1][0], img.pixel[0][1]));
		//Pixel haut droit
		imgDilate.pixel[0][img.Nbcol - 1] = max(img.pixel[0][img.Nbcol - 1], max(img.pixel[1][img.Nbcol - 1], img.pixel[0][img.Nbcol - 2]));
		//Pixel bas gauche
		imgDilate.pixel[img.Nblig - 1][0] = max(img.pixel[img.Nblig - 1][0], max(img.pixel[img.Nblig - 2][0], img.pixel[img.Nblig - 1][1]));
		//Pixel bas droit
		imgDilate.pixel[img.Nblig - 1][img.Nbcol - 1] = max(img.pixel[img.Nblig - 1][img.Nbcol - 1], max(img.pixel[img.Nblig - 1][img.Nbcol - 2], img.pixel[img.Nblig - 2][img.Nbcol - 1]));

		//BORD HAUT
		for (int j = 1; j < img.Nbcol - 1; j++)
		{
			imgDilate.pixel[0][j] = max(max(img.pixel[0][j], img.pixel[0][j - 1]), max(img.pixel[1][j], img.pixel[0][j + 1]));
		}
		//BORD BAS
		for (int j = 1; j < img.Nbcol - 1; j++)
		{
			imgDilate.pixel[img.Nblig - 1][j] = max(max(img.pixel[img.Nblig - 1][j], img.pixel[img.Nblig - 1][j - 1]), max(img.pixel[img.Nblig - 2][j], img.pixel[img.Nblig - 1][j + 1]));
		}
		//BORD GAUCHE
		for (int i = 1; i < img.Nblig - 1; i++)
		{
			imgDilate.pixel[i][0] = max(max(img.pixel[i][0], img.pixel[i - 1][0]), max(img.pixel[i + 1][0], img.pixel[i][1]));
		}
		//BORD DROIT
		for (int i = 1; i < img.Nblig - 1; i++)
		{
			imgDilate.pixel[i][img.Nbcol - 1] = max(max(img.pixel[i][img.Nbcol - 1], img.pixel[i - 1][img.Nbcol - 1]), max(img.pixel[i + 1][img.Nbcol - 1], img.pixel[i][img.Nbcol - 2]));
		}

		//MILIEU IMAGE
		for (int i = 1; i < img.Nblig - 1; i++)
		{
			for (int j = 1; j < img.Nbcol - 1; j++)
			{
				imgDilate.pixel[i][j] = max(max(img.pixel[i][j], img.pixel[i][j]), max(max(img.pixel[i - 1][j], img.pixel[i + 1][j]), max(img.pixel[i][j - 1], img.pixel[i][j + 1])));
			}
		}
	}
	if (voisinage == 8)
	{
		//Pixel haut gauche
		imgDilate.pixel[0][0] = max(max(img.pixel[0][0], img.pixel[1][1]), max(img.pixel[1][0], img.pixel[0][1]));
		//Pixel haut droit
		imgDilate.pixel[0][img.Nbcol - 1] = max(max(img.pixel[0][img.Nbcol - 1], img.pixel[1][img.Nbcol - 2]), max(img.pixel[1][img.Nbcol - 1], img.pixel[0][img.Nbcol - 2]));
		//Pixel bas gauche
		imgDilate.pixel[img.Nblig - 1][0] = max(max(img.pixel[img.Nblig - 1][0], img.pixel[img.Nblig - 2][1]), max(img.pixel[img.Nblig - 2][0], img.pixel[img.Nblig - 1][1]));
		//Pixel bas droit
		imgDilate.pixel[img.Nblig - 1][img.Nbcol - 1] = max(max(img.pixel[img.Nblig - 1][img.Nbcol - 1], img.pixel[img.Nblig - 2][img.Nbcol - 2]), max(img.pixel[img.Nblig - 1][img.Nbcol - 2], img.pixel[img.Nblig - 2][img.Nbcol - 1]));

		//BORD HAUT
		for (int j = 1; j < img.Nbcol - 1; j++)
		{
			imgDilate.pixel[0][j] = max(max(img.pixel[1][j - 1], img.pixel[1][j + 1]), max(max(img.pixel[0][j], img.pixel[0][j - 1]), max(img.pixel[1][j], img.pixel[0][j + 1])));
		}
		//BORD BAS
		for (int j = 1; j < img.Nbcol - 1; j++)
		{
			imgDilate.pixel[img.Nblig - 1][j] = max(max(img.pixel[img.Nblig - 1][j - 1], img.pixel[img.Nblig - 1][j + 1]), max(max(img.pixel[img.Nblig - 1][j], img.pixel[img.Nblig - 1][j - 1]), max(img.pixel[img.Nblig - 2][j], img.pixel[img.Nblig - 1][j + 1])));
		}
		//BORD GAUCHE
		for (int i = 1; i < img.Nblig - 1; i++)
		{
			imgDilate.pixel[i][0] = max(max(img.pixel[i + 1][1], img.pixel[i - 1][1]), max(max(img.pixel[i][0], img.pixel[i - 1][0]), max(img.pixel[i + 1][0], img.pixel[i][1])));
		}
		//BORD DROIT
		for (int i = 1; i < img.Nblig - 1; i++)
		{
			imgDilate.pixel[i][img.Nbcol - 1] = max(max(img.pixel[i + 1][img.Nbcol - 2], img.pixel[i - 1][img.Nbcol - 2]), max(max(img.pixel[i][img.Nbcol - 1], img.pixel[i - 1][img.Nbcol - 1]), max(img.pixel[i + 1][img.Nbcol - 1], img.pixel[i][img.Nbcol - 2])));
		}

		//Milieu image
		for (int i = 1; i < img.Nblig - 1; i++)
		{
			for (int j = 1; j < img.Nbcol - 1; j++)
			{
				/*imgDilate.pixel[i][j] = max(img.pixel[i][j], img.pixel[i][j]) + max(img.pixel[i - 1][j], img.pixel[i + 1][j]) + max(img.pixel[i][j - 1], img.pixel[i][j + 1]) + max(img.pixel[i - 1][j - 1], img.pixel[i - 1][j + 1]) + max(img.pixel[i + 1][j - 1], img.pixel[i + 1][j + 1]);*/

				imgDilate.pixel[i][j] = max(max(max(img.pixel[i][j], img.pixel[i][j]), max(img.pixel[i - 1][j], img.pixel[i + 1][j])), max(max(max(img.pixel[i][j - 1], img.pixel[i][j + 1]), max(img.pixel[i - 1][j - 1], img.pixel[i - 1][j + 1])), max(img.pixel[i + 1][j - 1], img.pixel[i + 1][j + 1])));
			}
		}
	}

	return imgDilate;
}

IMAGE ouvertureImage(IMAGE img, int voisinage)
{
	IMAGE imgOpen = allocationImage(img.Nblig, img.Nbcol);
	IMAGE imgErode = erosionImage(img, voisinage);
	imgOpen = dilatationImage(imgErode, voisinage);

	return imgOpen;
}

IMAGE fermetureImage(IMAGE img, int voisinage)
{
	IMAGE imgClose = allocationImage(img.Nblig, img.Nbcol);
	IMAGE imgDilate = dilatationImage(img, voisinage);
	imgClose = erosionImage(img, voisinage);

	return imgClose;
}

IMAGE contourImage(IMAGE img, int voisinage)
{
	IMAGE contour = allocationImage(img.Nblig, img.Nbcol);
	IMAGE imgErode = erosionImage(img, voisinage);
	int temp;
	for (int i = 0; i < img.Nbcol * img.Nblig; i++)
	{
		temp = img.data[i] - imgErode.data[i];

		if (temp < 0)
		{
			temp = 0;
		}
		if (temp > 255)
		{
			temp = 255;
		}

		contour.data[i] = temp;
	}


	return contour;
}

IMAGE whiteTopHat(IMAGE img, int voisinage, int n_iteration)
{

	IMAGE WhiteTopHat = allocationImage(img.Nblig, img.Nbcol);
	IMAGE imgTemp = allocationImage(img.Nblig, img.Nbcol);
	imgTemp = erosionImage(img, voisinage);
	for (int i = 0; i < n_iteration - 1; i++)
	{
		imgTemp = erosionImage(imgTemp, voisinage);
	}
	for (int i = 0; i < n_iteration; i++)
	{
		imgTemp = dilatationImage(imgTemp, voisinage);
	}


	int temp;
	for (int i = 0; i < img.Nbcol * img.Nblig; i++)
	{
		temp = img.data[i] - imgTemp.data[i];

		if (temp < 0)
		{
			temp = 0;
		}
		if (temp > 255)
		{
			temp = 255;
		}

		WhiteTopHat.data[i] = temp;
	}

	return WhiteTopHat;
}

IMAGE blackTopHat(IMAGE img, int voisinage, int n_iteration)
{
	IMAGE BlackTopHat = allocationImage(img.Nblig, img.Nbcol);
	IMAGE imgTemp = allocationImage(img.Nblig, img.Nbcol);
	imgTemp = dilatationImage(img, voisinage);
	for (int i = 0; i < n_iteration - 1; i++)
	{
		imgTemp = dilatationImage(imgTemp, voisinage);
	}
	for (int i = 0; i < n_iteration; i++)
	{
		imgTemp = erosionImage(imgTemp, voisinage);
	}

	int temp;
	for (int i = 0; i < img.Nbcol * img.Nblig; i++)
	{
		temp = imgTemp.data[i] - img.data[i];

		if (temp < 0)
		{
			temp = 0;
		}
		if (temp > 255)
		{
			temp = 255;
		}

		BlackTopHat.data[i] = temp;
	}

	return BlackTopHat;
}

IMAGE SoustractionImage(IMAGE img1, IMAGE img2)
{
	IMAGE Soustrait = allocationImage(img1.Nblig, img1.Nbcol);
	if (img1.Nblig != img2.Nblig && img1.Nbcol != img1.Nbcol)
	{
		return Soustrait;
	}

	int tempo = 0;
	for (int i = 0; i < img1.Nblig * img1.Nbcol; i++)
	{
		tempo = img1.data[i] - img2.data[i];
		if (tempo > 255 || tempo < 0)
		{
			tempo = 255;
		}

		Soustrait.data[i] = tempo;
	}

	return Soustrait;
}

int IntersectionImage(IMAGE img1, IMAGE img2)
{
	int nbpixel = 0;
	int tempo = 0;

	//Effectue un ET logique afin d'avoir l'union entre les images
	for (int i = 0; i < img1.Nblig * img1.Nbcol; i++)
	{
		tempo = img1.data[i] && img2.data[i];

		if (tempo != 0)
		{
			int test;
			test = 0;
		}

		if (tempo == 1)
		{
			nbpixel++;
		}
	}

	//Retourne le nombre de pixel de l'intersection
	return nbpixel;
}

int UnionImage(IMAGE img1, IMAGE img2)
{
	int nbpixel = 0;
	int tempo = 0;

	//Effectue un OU logique afin d'avoir l'union entre les images
	for (int i = 0; i < img1.Nblig * img1.Nbcol; i++)
	{
		tempo = img1.data[i] || img2.data[i];

		if (tempo == 1)
		{
			nbpixel++;
		}
	}
	
	//Retourne le nombre de pixel de l'union
	return nbpixel;
}

#pragma region PROJET
void IHMprojet(void)
{
	//VARIABLES DES CHOIX
	int choixMenu = 0;
	char choixQuitter;
	int choixTypeImage;
	int choixImage;
	int choixMultipleImage;
	int minIntervalle;
	int maxIntervalle;

	//VARIABLES DU SCORE
	float* scoreImage = (float*)calloc(6, sizeof(float));;

	//IHM DU PROJET
	while (choixMenu != -1)
	{
		printf("Menu principal \n");
		printf("- 0 : Traiter toutes les images \n");
		printf("- 1 : Traiter une seule image \n");
		printf("- 2 : Traiter un lot d'images \n");
		printf("- 3 : Quitter \n");
		printf("\n");
		scanf("%d", &choixMenu);
		printf("\n");

		switch (choixMenu)
		{
			// Case pour Traiter toutes les images
		case 0:
			printf("Menu Traiter toutes les images \n");
			printf(" - 0 : Toutes les images In \n");
			printf(" - 1 : Toutes les images Sc \n");
			printf(" - 2 : Toutes les images In & Sc \n");
			printf(" - 3 : Retour \n");
			printf("  \n");
			scanf("%d", &choixMultipleImage);
			printf("  \n");
			while (choixMultipleImage != 0 && choixMultipleImage != 1 && choixMultipleImage != 2 && choixMultipleImage != 3)
			{
				printf("Erreur de saisis \n");
				printf(" - 0 : Toutes les images In \n");
				printf(" - 1 : Toutes les images Sc \n");
				printf(" - 2 : Toutes les images In & Sc \n");
				printf(" - 3 : Retour \n");
				printf("  \n");
				scanf("%d", &choixMultipleImage);
				printf("  \n");
			}




			switch (choixMultipleImage)
			{
				//Case pour toutes les images In
			case 0:
				
				scoreImage = LancementProcess("allIn", 0, 0, 0);
				printf("\n");
				printf("Statistiques du dataset In :\n");
				printf("Le score moyen est de %.2f%% \n", scoreImage[0]);
				printf("L'ecart-type est de %.2f%% \n", scoreImage[1]);
				printf("Le score median est de %.2f%% \n", scoreImage[2]);
				printf("Le score minimum est de %.2f%% \n", scoreImage[3]);
				printf("Le score maximum est de %.2f%% \n", scoreImage[4]);
				printf("Un fichier .csv a ete enregistre avec le detail des scores pour chaque image In \n");
				printf("Un fichier .csv a ete enregistre avec les statistiques du dataset In\n");
				printf("\n");
				break;

				//Case pour toutes les images Sc
			case 1:

				scoreImage = LancementProcess("allSc", 0, 0, 0);
				printf("\n");
				printf("Statistiques du dataset Sc :\n");
				printf("Le score moyen est de %.2f%% \n", scoreImage[0]);
				printf("L'ecart-type est de %.2f%% \n", scoreImage[1]);
				printf("Le score median est de %.2f%% \n", scoreImage[2]);
				printf("Le score minimum est de %.2f%% \n", scoreImage[3]);
				printf("Le score maximum est de %.2f%% \n", scoreImage[4]);
				printf("Un fichier .csv a ete enregistre avec le detail des scores pour chaque image Sc \n");
				printf("Un fichier .csv a ete enregistre avec les statistiques du dataset Sc \n");
				printf("\n");
				break;

				//Case pour toutes les images In & Sc
			case 2:

				scoreImage = LancementProcess("all", 0, 0, 0);
				printf("\n");
				printf("Statistiques du dataset complet :\n");
				printf("Le score moyen est de %.2f%% \n", scoreImage[0]);
				printf("L'ecart-type est de %.2f%% \n", scoreImage[1]);
				printf("Le score median est de %.2f%% \n", scoreImage[2]);
				printf("Le score minimum est de %.2f%% \n", scoreImage[3]);
				printf("Le score maximum est de %.2f%% \n", scoreImage[4]);
				printf("Un fichier .csv a ete enregistre avec le detail des scores pour chaque image \n");
				printf("Un fichier .csv a ete enregistre avec les statistiques du dataset \n");
				printf("\n");
				break;

			case 3:
				break;

			default:
				printf("ERREUR");
				choixMenu = -1;
				break;
			}
			break;

			//Case pour Traiter une seule image
		case 1:
			printf("Menu Traiter une seule image \n");
			printf(" - 0 : Une image In \n");
			printf(" - 1 : Une image Sc \n");
			printf(" - 2 : Retour \n");
			printf("  \n");
			scanf("%d", &choixTypeImage);
			printf("\n");
			while (choixTypeImage != 0 && choixTypeImage != 1 && choixTypeImage != 2)
			{
				printf("Erreur de saisis \n");
				printf(" - 0 : Une image In \n");
				printf(" - 1 : Une image Sc \n");
				printf(" - 2 : Retour \n");
				printf("  \n");
				scanf("%d", &choixTypeImage);
				printf("\n");
			}

			if (choixTypeImage != 2)
			{
				printf("Quelle image ? (1-300) \n");
				scanf("%d", &choixImage);
				printf("\n");
				while (choixImage < 1 || choixImage > 300)
				{
					printf("Erreur de saisis \n");
					printf("Quelle image ? (1-300) \n");
					scanf("%d", &choixImage);
					printf("\n");
				}
			}

			//Traitement + Afficher résultat
			switch (choixTypeImage)
			{
				//Case pour une image In
			case 0:

				scoreImage = LancementProcess("In", 0, 0, choixImage);
				printf("\n");
				printf("L'image In_%d a un score de %.2f%%\n", choixImage, scoreImage[0]);
				printf("\n");
				break;

				//Case pour une image Sc
			case 1:

				scoreImage = LancementProcess("Sc", 0, 0, choixImage);
				printf("\n");
				printf("L'image Sc_%d a un score de %.2f%%\n", choixImage, scoreImage[0]);
				printf("\n");
				break;

			case 2:
				break;

			default:
				printf("ERREUR");
				choixMenu = -1;
				break;
			}
			break;

			//Case pour  Traiter un lot d'images
		case 2:
			printf("Menu : Traiter un lot d'images \n");
			printf(" - 0 : Un lot d'images In \n");
			printf(" - 1 : Un lot d'images Sc \n");
			printf(" - 2 : Retour \n");
			printf("  \n");
			scanf("%d", &choixTypeImage);
			printf("\n");
			while (choixTypeImage != 0 && choixTypeImage != 1 && choixTypeImage != 2)
			{
				printf("Erreur de saisis \n");
				printf(" - 0 : Un lot d'images In \n");
				printf(" - 1 : Un lot d'images Sc \n");
				printf(" - 2 : Retour \n");
				printf("  \n");
				scanf("%d", &choixTypeImage);
				printf("\n");
			}

			if (choixTypeImage != 2)
			{
				printf("Donner votre intervalle x y ([x;y] avec x,y de 1 a 300)  \n");
				scanf("%d %d", &minIntervalle, &maxIntervalle);
				printf("\n");
				while ((minIntervalle < 1 || minIntervalle > 300) || (maxIntervalle < 1 || maxIntervalle > 300) || (maxIntervalle == minIntervalle))
				{
					printf("Erreur de saisis \n");
					printf("Donner votre intervalle x y ([x;y] avec x,y de 1 a 300)  \n");
					scanf("%d %d", &minIntervalle, &maxIntervalle);
					printf("\n");
				}
				if (minIntervalle > maxIntervalle)
				{
					int temp = maxIntervalle;
					maxIntervalle = minIntervalle;
					minIntervalle = temp;
				}
			}



			//Traitement + Afficher résultat
			switch (choixTypeImage)
			{
				//Case pour un lot d'image In
			case 0:

				scoreImage = LancementProcess("lotIn", minIntervalle, maxIntervalle, 0);
				printf("\n");
				printf("Statistiques du lot d'images In [%d;%d]:\n", minIntervalle, maxIntervalle);
				printf("Le score moyen est de %.2f%% \n", scoreImage[0]);
				printf("L'ecart-type est de %.2f%% \n", scoreImage[1]);
				printf("Le score median est de %.2f%% \n", scoreImage[2]);
				printf("Le score minimum est de %.2f%% \n", scoreImage[3]);
				printf("Le score maximum est de %.2f%% \n", scoreImage[4]);
				printf("Un fichier .csv a ete enregistre avec le detail des scores pour chaque image In du lot \n");
				printf("Un fichier .csv a ete enregistre avec les statistiques du lot d'image In \n");
				printf("\n");
				break;

				//Case pour un lot d'image Sc
			case 1:

				scoreImage = LancementProcess("lotSc", minIntervalle, maxIntervalle, 0);
				printf("\n");
				printf("Statistiques du lot d'images In [%d;%d]:\n", minIntervalle, maxIntervalle);
				printf("Le score moyen est de %.2f%% \n", scoreImage[0]);
				printf("L'ecart-type est de %.2f%% \n", scoreImage[1]);
				printf("Le score median est de %.2f%% \n", scoreImage[2]);
				printf("Le score minimum est de %.2f%% \n", scoreImage[3]);
				printf("Le score maximum est de %.2f%% \n", scoreImage[4]);
				printf("Un fichier .csv a ete enregistre avec le detail des scores pour chaque image Sc du lot \n");
				printf("Un fichier .csv a ete enregistre avec les statistiques du lot d'image Sc \n");
				printf("\n");
				break;

			case 2:
				break;

			default:
				printf("ERREUR");
				choixMenu = -1;
				break;
			}
			break;

			//Case pour Quitter
		case 3:
			printf("Etes-vous sur ? (y/n) \n");
			scanf(" %c", &choixQuitter);
			printf("\n");

			if (choixQuitter == 'y')
			{
				choixMenu = -1;
			}
			break;

		default:
			printf("Erreur de saisis  \n");
			break;
		}
	}
}

float* LancementProcess(const char* img2process, int minIntervalle, int maxIntervalle, int numImg)
{
	float* score = NULL;
	float* scoreStats = NULL;
	float scoreAVG = 0;
	float ecartType = 0;

	int nb_image;
	char* type;
	char num[20] = { 0 };
	char* nomImg;
	char* extension = ".pgm";
	int tempo = 0;

	//Oriente le processus en fonction du type d'image selectionné
	if (img2process == "allIn") // Toutes les images In
	{
		nb_image = 300;
		score = (float*)calloc(nb_image, sizeof(float));
		scoreStats = (float*)calloc(5, sizeof(float));

		type = "In_";

		for (int i = 0; i < nb_image; i++) // Traitement de chaque image une à une et retourne le score de l'image
		{
			_itoa(i + 1, num, 10);
			nomImg = (char*)malloc(1 + strlen(type) + strlen(num) + strlen(extension));
			strcpy(nomImg, type);
			strcat(nomImg, num);
			strcat(nomImg, extension);

			score[i] = Traitement(nomImg, 1);
			printf("image In_%d traitee \n", i + 1);

			scoreAVG += score[i]; // Fait la somme des scores des images
			ecartType += score[i] * score[i]; 
		}
		EnregistrementScore("ScoreAll_In.csv", img2process, 0, 0, score, nb_image); //Enregistre les scores dans un .csv

		//Calcul des statistiques
		trieScoreCroissant(score, nb_image);
		scoreStats = StatistiquesScores(score, scoreAVG, ecartType, nb_image);

		EnregistrementStats("StatsAll_In.csv", img2process, scoreStats); //Enregistre les stats dans un .csv

		return scoreStats; //Retourne les statistiques du jeu d'image

	}
	else if (img2process == "allSc") //Toutes les images Sc
	{
		nb_image = 300;
		score = (float*)calloc(nb_image, sizeof(float));
		scoreStats = (float*)calloc(5, sizeof(float));

		type = "Sc_";

		for (int i = 0; i < nb_image; i++) // Traitement de chaque image une à une et retourne le score de l'image
		{
			_itoa(i + 1, num, 10);
			nomImg = (char*)malloc(1 + strlen(type) + strlen(num) + strlen(extension));
			strcpy(nomImg, type);
			strcat(nomImg, num);
			strcat(nomImg, extension);

			score[i] = Traitement(nomImg, 0);
			printf("image Sc_%d traitee \n", i + 1);
			scoreAVG += score[i]; // Fait la somme des scores des images
			ecartType += score[i] * score[i];
		}

		EnregistrementScore("ScoreAll_Sc.csv", img2process, 0, 0, score, nb_image); //Enregistre les scores dans un .csv

		//Calcul des statistiques
		trieScoreCroissant(score, nb_image);
		scoreStats = StatistiquesScores(score, scoreAVG, ecartType, nb_image);

		EnregistrementStats("StatsAll_Sc.csv", img2process, scoreStats); //Enregistre les stats dans un .csv

		return scoreStats;//Retourne les statistiques du jeu d'image
	}
	else if (img2process == "all") // Toutes les images In+Sc
	{
		nb_image = 600;
		score = (float*)calloc(nb_image, sizeof(float));
		scoreStats = (float*)calloc(5, sizeof(float));

		type = "In_";

		for (int i = 0; i < nb_image / 2; i++) // Traitement de chaque image In une à une et retourne le score de l'image
		{
			_itoa(i + 1, num, 10);
			nomImg = (char*)malloc(1 + strlen(type) + strlen(num) + strlen(extension));
			strcpy(nomImg, type);
			strcat(nomImg, num);
			strcat(nomImg, extension);

			score[i] = Traitement(nomImg, 1);
			scoreAVG += score[i]; // Fait la somme des score des images
			ecartType += score[i] * score[i];

			printf("image In_%d traitee \n", i + 1);
			tempo++;
		}

		type = "Sc_";

		for (int i = 0; i < nb_image / 2; i++) // Traitement de chaque image Sc une à une et retourne le score de l'image
		{
			_itoa(i + 1, num, 10);
			nomImg = (char*)malloc(1 + strlen(type) + strlen(num) + strlen(extension));
			strcpy(nomImg, type);
			strcat(nomImg, num);
			strcat(nomImg, extension);

			score[tempo] = Traitement(nomImg, 0);
			scoreAVG += score[tempo]; // Fait la somme des score des images 
			ecartType += score[tempo] * score[tempo];

			printf("image Sc_%d traitee \n", i + 1);
			tempo++;
		}
		EnregistrementScore("ScoreAll.csv", img2process, 0, 0, score, nb_image); //Enregistre les scores dans un .csv

		//Calcul des statistiques
		trieScoreCroissant(score, nb_image);
		scoreStats = StatistiquesScores(score, scoreAVG, ecartType, nb_image);

		EnregistrementStats("StatsAll.csv", img2process, scoreStats); //Enregistre les stats dans un .csv

		return scoreStats;//Retourne les statistiques du jeu d'image
	}
	else if (img2process == "lotIn") //Lot d'image In
	{
		nb_image = maxIntervalle - minIntervalle + 1;
		score = (float*)calloc(nb_image, sizeof(float));
		scoreStats = (float*)calloc(5, sizeof(float));

		type = "In_";
		tempo = minIntervalle;

		for (int i = 0; i < nb_image; i++)// Traitement de chaque image une à une et retourne le score de l'image
		{
			_itoa(tempo, num, 10);
			nomImg = (char*)malloc(1 + strlen(type) + strlen(num) + strlen(extension));
			strcpy(nomImg, type);
			strcat(nomImg, num);
			strcat(nomImg, extension);

			score[i] = Traitement(nomImg, 1);
			printf("image In_%d traitee \n", tempo);
			tempo++;

			scoreAVG += score[i]; // Fait la somme des scores des images
			ecartType += score[i] * score[i];
		}

		EnregistrementScore("ScoreLot_In.csv", img2process, minIntervalle, maxIntervalle, score, nb_image); //Enregistre les scores dans un .csv
		
		//Calcul des statistiques
		trieScoreCroissant(score, nb_image);
		scoreStats = StatistiquesScores(score, scoreAVG, ecartType, nb_image);

		EnregistrementStats("StatsLot_In.csv", img2process, scoreStats); //Enregistre les stats dans un .csv

		return scoreStats;//Retourne les statistiques du jeu d'image
	}
	else if (img2process == "lotSc") //Lot d'image Sc
	{
		nb_image = maxIntervalle - minIntervalle + 1;
		score = (float*)calloc(nb_image, sizeof(float));
		scoreStats = (float*)calloc(5, sizeof(float));

		type = "Sc_";
		tempo = minIntervalle;

		for (int i = 0; i < nb_image; i++) // Traitement de chaque image une à une et retourne le score de l'image
		{
			_itoa(tempo, num, 10);
			nomImg = (char*)malloc(1 + strlen(type) + strlen(num) + strlen(extension));
			strcpy(nomImg, type);
			strcat(nomImg, num);
			strcat(nomImg, extension);

			score[i] = Traitement(nomImg, 0);
			printf("image Sc_%d traitee \n", tempo);
			tempo++;

			scoreAVG += score[i]; // Fait la somme des scores des images
			ecartType += score[i] * score[i];
		}

		EnregistrementScore("ScoreLot_Sc.csv", img2process, minIntervalle, maxIntervalle, score, nb_image); //Enregistre les scores dans un .csv

		//Calcul des statistiques
		trieScoreCroissant(score, nb_image);
		scoreStats = StatistiquesScores(score, scoreAVG, ecartType, nb_image);

		EnregistrementStats("StatsLot_Sc.csv", img2process, scoreStats); //Enregistre les stats dans un .csv

		return scoreStats; //Retourne les statistiques du jeu d'image
	}
	else if (img2process == "In")
	{
		score = (float*)calloc(1, sizeof(float));
		scoreStats = (float*)calloc(1, sizeof(float));

		type = "In_";
		_itoa(numImg, num, 10);
		nomImg = (char*)malloc(1 + strlen(type) + strlen(num) + strlen(extension));
		strcpy(nomImg, type);
		strcat(nomImg, num);
		strcat(nomImg, extension);

		score[0] = Traitement(nomImg, 1);
		printf("image In_%d traitee \n", numImg);

		scoreAVG = score[0];
		scoreStats[0] = scoreAVG;

		return scoreStats; //Retourne le score de l'image
	}
	else if (img2process == "Sc")
	{
		score = (float*)calloc(1, sizeof(float));
		scoreStats = (float*)calloc(1, sizeof(float));

		type = "Sc_";
		_itoa(numImg, num, 10);
		nomImg = (char*)malloc(1 + strlen(type) + strlen(num) + strlen(extension));
		strcpy(nomImg, type);
		strcat(nomImg, num);
		strcat(nomImg, extension);

		score[0] = Traitement(nomImg, 0);
		printf("image Sc_%d traitee \n", numImg);

		scoreAVG = score[0];
		scoreStats[0] = scoreAVG;

		return scoreStats; //Retourne le score de l'image
	}
}

void EnregistrementScore(const char* nomFichier, const char* img2process, int minIntervalle, int maxIntervalle, float* score, int nb_image)
{
	//Créer le chemin du fichier .csv
	char* repo = "res/";
	char* nomFichier2 = (char*)malloc(1 + strlen(nomFichier));
	strcpy(nomFichier2, nomFichier);
	char* chemin = (char*)malloc(1 + strlen(repo) + strlen(nomFichier));
	strcpy(chemin, repo);
	strcat(chemin, nomFichier2);

	FILE* F;
	F = fopen(chemin, "w");

	//Enregistrement des scores en fonction du type d'image traité
	if (img2process == "allIn") // Toutes les images In
	{
		for (int i = 0; i < nb_image; i++)
		{
			fprintf(F, "In_%d ; %.2f\n", i + 1, score[i]);
		}

	}
	else if (img2process == "allSc") // Toutes les images Sc
	{
		for (int i = 0; i < nb_image; i++)
		{
			fprintf(F, "Sc_%d ; %.2f\n", i + 1, score[i]);
		}
	}
	else if (img2process == "all") // Toutes les images In+Sc
	{
		int cmpt = 0;

		for (int i = 0; i < nb_image / 2; i++)
		{
			fprintf(F, "In_%d ; %.2f\n", i + 1, score[i]);
			cmpt++;
		}

		for (int i = 0; i < nb_image / 2; i++)
		{
			fprintf(F, "Sc_%d ; %.2f\n", i + 1, score[cmpt]);
			cmpt++;
		}
	}
	else if (img2process == "lotIn") // Le lot d'image In selectionné
	{
		int temp = minIntervalle;
		for (int i = 0; i < maxIntervalle - minIntervalle + 1; i++)
		{
			fprintf(F, "In_%d ; %.2f\n", temp, score[i]);
			temp++;
		}
	}
	else if (img2process == "lotSc") // Le lot d'image Sc selectionné
	{
		int temp = minIntervalle;
		for (int i = 0; i < maxIntervalle - minIntervalle + 1; i++)
		{
			fprintf(F, "Sc_%d ; %.2f\n", temp, score[i]);
			temp++;
		}
	}

	fclose(F);

	free(nomFichier2);
	free(chemin);
}

float Traitement(const char* nomImg, int inversion)
{
	float score = 0;
	int* histo;

	//Récupère la vérité terrrain
	char* repo = "GT/";
	char* nomImg2 = (char*)malloc(1 + strlen(nomImg));
	strcpy(nomImg2, nomImg);
	char* chemin = (char*)malloc(1 + strlen(repo) + strlen(nomImg2));
	strcpy(chemin, repo);
	strcat(chemin, nomImg2);
	IMAGE terrain = lectureImage(chemin);

	//Récupère l'image à traiter
	repo = "imgProjet/";
	char* cheminIMG = (char*)malloc(1 + strlen(repo) + strlen(nomImg2));
	strcpy(cheminIMG, repo);
	strcat(cheminIMG, nomImg2);
	IMAGE imgTraitement = lectureImage(cheminIMG);

	//Début du traitement
	//PARTIE 1 : Morphologie
	ElementStructurant SE_disk_20 = allocation_SE("disk", 20);
	ElementStructurant SE_disk_2 = allocation_SE("disk", 2);
	ElementStructurant SE_disk_3 = allocation_SE("disk", 3);

	if (inversion == 1) // Traitement morphologique des images In
	{
		imgTraitement = inverseImage(imgTraitement);

		imgTraitement = whiteTopHatSE(imgTraitement, SE_disk_20);
		imgTraitement = seuillageOtsu(imgTraitement);

		ElementStructurant SE_disk_2 = allocation_SE("disk", 2);
		imgTraitement = erosionImageSE(imgTraitement, SE_disk_2);

		ElementStructurant SE_disk_3 = allocation_SE("disk", 3);
		imgTraitement = dilatationImageSE(imgTraitement, SE_disk_3);
	}
	else // Traitement morphologique des images Sc
	{
		imgTraitement = whiteTopHatSE(imgTraitement, SE_disk_20);
		imgTraitement = seuillageOtsu(imgTraitement);

		ElementStructurant SE_disk_1 = allocation_SE("disk", 1);
		imgTraitement = erosionImageSE(imgTraitement, SE_disk_1);

		ElementStructurant SE_disk_2 = allocation_SE("disk", 2);
		imgTraitement = dilatationImageSE(imgTraitement, SE_disk_2);
	}

	//sauvegardeImage(imgTraitement, "P5", "res/ImageApresTraitement.pgm");

	//PARTIE 2 : Suppression des "Bruits"
	//Récupère les informations des composantes connexes de la vérité terrain
	int nbcompoGT;
	IMAGE GTlabel = labelImage(terrain, &nbcompoGT);
	SIGNATURE_COMPOSANTE_CONNEXE* compoGT = (SIGNATURE_COMPOSANTE_CONNEXE*)malloc((nbcompoGT + 1) * sizeof(SIGNATURE_COMPOSANTE_CONNEXE));
	compoGT = signaturesImage(GTlabel, nbcompoGT);

	//Récupère les informations des composantes connexes de l'image à traiter
	int nbcompoImg;
	IMAGE Imglabel = labelImage(imgTraitement, &nbcompoImg);
	SIGNATURE_COMPOSANTE_CONNEXE* compoImg = (SIGNATURE_COMPOSANTE_CONNEXE*)malloc((nbcompoImg + 1) * sizeof(SIGNATURE_COMPOSANTE_CONNEXE));
	compoImg = signaturesImage(Imglabel, nbcompoImg);

	//Récupère la surface de la plus petite composante connexe dans la vérité terrain
	int minSurface = compoGT[0].surface;
	for (int i = 1; i < nbcompoGT + 1; i++)
	{
		if (compoGT[i].surface < minSurface)
		{
			minSurface = compoGT[i].surface;
		}
	}

	//Indique les composantes à supprimer dans l'image à traiter en fonction de la surface minimum issue de la vérité terrain
	for (int i = 1; i < nbcompoImg + 1; i++)
	{
		if (compoImg[i].surface > ((float)minSurface / 5))
		{
			compoImg[i].suppr = 0;
		}
	}

	//Suppression des bruits dans l'image traiter
	IMAGE imgSangBruit = SupprimerComposante(Imglabel, nbcompoImg, compoImg);

	//sauvegardeImage(imgSangBruit, "P5", "res/ImageSansBruit.pgm"); 

	//PARTIE 3 : Association de composante

	//Récupération des informations des composantes connexes dans l'image débruité
	imgSangBruit = labelImage(imgSangBruit, &nbcompoImg);
	compoImg = signaturesImage(imgSangBruit, nbcompoImg);

	//Associe une composante de la vérité terrain à une composante dans l'image à traiter 
	float distance = 0, minDistance = 35;
	for (int i = 1; i < nbcompoGT + 1; i++)
	{
		for (int j = 1; j < nbcompoImg + 1; j++)
		{

			if (terrain.pixel[(int)compoImg[j].CG.ordonnee][(int)compoImg[j].CG.abscisse] == 255 && compoImg[j].suppr != 0)
			{
				compoImg[j].suppr = 0;
			}
		}
	}

	//Supprimer les composantes connexes ayant aucune association 
	IMAGE imgFinale = SupprimerComposante(imgSangBruit, nbcompoImg, compoImg);

	//sauvegardeImage(imgFinale, "P5", "res/ImageFinale.pgm");


	//PARTIE 4 : Calcul des scores
	histo = histogrammeImage(imgFinale, 0, 256);
	int Int;
	int Uni;

	//Si l'image finale est vide (sans composante) on utilise l'image débruité pour le calcul du score
	if (histo[255] != 0)
	{
		//Calcul de l'intersection et de l'union entre la vérité terrain et l'image finale
		Int = IntersectionImage(terrain, imgFinale);
		Uni = UnionImage(terrain, imgFinale);
	}
	else
	{
		//Calcul de l'intersection et de l'union entre la vérité terrain et l'image débruité
		Int = IntersectionImage(terrain, imgSangBruit);
		Uni = UnionImage(terrain, imgSangBruit);
	}

	//Si l'union est nulle alors on met le score à zéro pour éviter une division par 0
	if (Uni != 0)
	{
		//Calcul de l'IOU
		score = (float)Int / (float)Uni * 100;
	}
	else
	{
		score = 0;
	}

	return score;
}

void trieScoreCroissant(float* score, int nb_image)
{
	float temporaire;
	int indice;

	for (int j = 0; j < nb_image - 1; j++)
	{
		indice = j;
		for (int i = j + 1; i < nb_image; i++)
		{
			if (score[i] < score[indice])
			{
				indice = i;
			}
		}
		if (indice != j)
		{
			temporaire = score[j];
			score[j] = score[indice];
			score[indice] = temporaire;
		}
	}
}


float* StatistiquesScores(float* scoreTrie, float infoMoyenne, float infoEcartType, int nb_image)
{
	float* scoreStats;
	scoreStats = (float*)calloc(5, sizeof(float));
	float score_median;
	float score_min;
	float score_max;

	score_min = scoreTrie[0];
	score_max = scoreTrie[nb_image - 1];
	if (nb_image % 2 != 0)
	{
		score_median = scoreTrie[(nb_image-1) / 2];
	}
	else
	{
		score_median = (float)((scoreTrie[(int)((nb_image - 2) / 2)] + scoreTrie[(int)(nb_image / 2)]) / 2);
	}


	scoreStats[0] = (float)(infoMoyenne / nb_image);
	scoreStats[1] = (float)(sqrt((float)(infoEcartType / nb_image) - (scoreStats[0] * scoreStats[0])));
	scoreStats[2] = score_median;
	scoreStats[3] = score_min;
	scoreStats[4] = score_max;

	return scoreStats;
}

void EnregistrementStats(const char* nomFichier, const char* img2process, float* scoreStats)
{
	//Créer le chemin du fichier .csv
	char* repo = "res/";
	char* nomFichier2 = (char*)malloc(1 + strlen(nomFichier));
	strcpy(nomFichier2, nomFichier);
	char* chemin = (char*)malloc(1 + strlen(repo) + strlen(nomFichier));
	strcpy(chemin, repo);
	strcat(chemin, nomFichier2);

	FILE* F;
	F = fopen(chemin, "w");

	//Enregistrement des scores en fonction du type d'image traité
	if (img2process == "allIn") // Toutes les images In
	{
		fprintf(F, "Score moyen ; %.2f\n", scoreStats[0]);
		fprintf(F, "Score median ; %.2f\n", scoreStats[2]);
		fprintf(F, "Score minimum ; %.2f\n", scoreStats[3]);
		fprintf(F, "Score maximum ; %.2f\n", scoreStats[4]);
		fprintf(F, "Ecart-Type ; %.2f\n", scoreStats[1]);

	}
	else if (img2process == "allSc") // Toutes les images Sc
	{
		fprintf(F, "Score moyen ; %.2f\n", scoreStats[0]);
		fprintf(F, "Score median ; %.2f\n", scoreStats[2]);
		fprintf(F, "Score minimum ; %.2f\n", scoreStats[3]);
		fprintf(F, "Score maximum ; %.2f\n", scoreStats[4]);
		fprintf(F, "Ecart-Type ; %.2f\n", scoreStats[1]);
	}
	else if (img2process == "all") // Toutes les images In+Sc
	{
		fprintf(F, "Score moyen ; %.2f\n", scoreStats[0]);
		fprintf(F, "Score median ; %.2f\n", scoreStats[2]);
		fprintf(F, "Score minimum ; %.2f\n", scoreStats[3]);
		fprintf(F, "Score maximum ; %.2f\n", scoreStats[4]);
		fprintf(F, "Ecart-Type ; %.2f\n", scoreStats[1]);
	}
	else if (img2process == "lotIn") // Le lot d'image In selectionné
	{
		fprintf(F, "Score moyen ; %.2f\n", scoreStats[0]);
		fprintf(F, "Score median ; %.2f\n", scoreStats[2]);
		fprintf(F, "Score minimum ; %.2f\n", scoreStats[3]);
		fprintf(F, "Score maximum ; %.2f\n", scoreStats[4]);
		fprintf(F, "Ecart-Type ; %.2f\n", scoreStats[1]);
	}
	else if (img2process == "lotSc") // Le lot d'image Sc selectionné
	{
		fprintf(F, "Score moyen ; %.2f\n", scoreStats[0]);
		fprintf(F, "Score median ; %.2f\n", scoreStats[2]);
		fprintf(F, "Score minimum ; %.2f\n", scoreStats[3]);
		fprintf(F, "Score maximum ; %.2f\n", scoreStats[4]);
		fprintf(F, "Ecart-Type ; %.2f\n", scoreStats[1]);
	}

	fclose(F);

	free(nomFichier2);
	free(chemin);
}


#pragma endregion 


IMAGE filtreMoyen(IMAGE img, int voisinage)
{
	IMAGE imgFiltre = allocationImage(img.Nblig, img.Nbcol);
	int moyenne;
	int somme = 0;

	// Parcours de l'image pixel par pixel
	for (int i = 0; i < img.Nblig; i++)
	{
		for (int j = 0; j < img.Nbcol; j++)
		{
			// Parcours de la sous-image recouverte par le voisinage centré sur le pixel (i,j)
			for (int k = -(floor(voisinage / 2)); k <= (ceil(voisinage / 2)); k++)
			{
				for (int l = -(floor(voisinage / 2)); l <= (ceil(voisinage / 2)); l++)
				{
					int x = i + k;
					int y = j + l;

					// Vérification que le pixel (x,y) est bien dans l'image sinon on fait rien
					if ((x >= 0 && x < img.Nblig) && (y >= 0 && y < img.Nbcol))
					{
						somme += img.pixel[x][y];
					}
				}
			}

			moyenne = somme / (voisinage * voisinage);

			// Mise à jour de la valeur du pixel dans l'image filtrée
			imgFiltre.pixel[i][j] = moyenne;
			somme = 0;
			moyenne = 0;
		}
	}

	return imgFiltre;
}



IMAGERGB filtreMoyenRGB(IMAGERGB img, int voisinage)
{
	IMAGERGB imgFiltre = allocationImageRGB(img.Nblig, img.Nbcol);

	int sommeR = 0;
	int sommeG = 0;
	int sommeB = 0;

	// Parcours de l'image pixel par pixel
	for (int i = 0; i < img.Nblig; i++)
	{
		for (int j = 0; j < img.Nbcol; j++)
		{
			// Parcours de la sous-image recouverte par le voisinage centré sur le pixel (i,j)
			for (int k = -(floor(voisinage / 2)); k <= (ceil(voisinage / 2)); k++)
			{
				for (int l = -(floor(voisinage / 2)); l <= (ceil(voisinage / 2)); l++)
				{
					int x = i + k;
					int y = j + l;

					// Vérification que le pixel (x,y) est bien dans l'image sinon on fait rien
					if ((x >= 0 && x < img.Nblig) && (y >= 0 && y < img.Nbcol))
					{
						sommeR += img.pixel[x][y].R;
						sommeG += img.pixel[x][y].G;
						sommeB += img.pixel[x][y].B;
					}
				}
			}

			// Mise à jour de la valeur du pixel dans l'image filtrée
			imgFiltre.pixel[i][j].R = sommeR / (voisinage * voisinage);
			imgFiltre.pixel[i][j].G = sommeG / (voisinage * voisinage);
			imgFiltre.pixel[i][j].B = sommeB / (voisinage * voisinage);

			sommeR = 0;
			sommeG = 0;
			sommeB = 0;
		}
	}

	return imgFiltre;
}