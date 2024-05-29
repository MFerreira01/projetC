#include "image.h"

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <cstdio>

image::image() : Nblig(0), Nbcol(0), data(nullptr), pixel(nullptr) {}

image::image(int Nblig, int Nbcol, unsigned char* data, unsigned char** pixel)
	: Nblig(Nblig), Nbcol(Nbcol), data(data), pixel(pixel) {}

image::image(int Nblig, int Nbcol)
{
	allocationImage(Nblig, Nbcol);
}

image::~image()
{
	delete[] data;
	delete[] pixel;
}

image image::allocationImage(int Nblig, int Nbcol)
{
	image mat = image();
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

void image::initialisationAleatoireImage(image img, int ngMin, int ngMax)
{
	int i, j;
	printf("Dans initialisation : img -> %p img.data -> %p img.pixel -> %p\n", &img, img.data, img.pixel);

	for (i = 0; i < img.Nblig; i++)
		for (j = 0; j < img.Nbcol; j++)
			img.pixel[i][j] = (unsigned char)(ngMin + rand() % (ngMax + 1 - ngMin));
}

int* image::histogrammeImage(image img, int choix, int n)
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

void image::sauvegardeImage(image img, const char* type, const char* out)
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

void image::liberationImage(image* img)
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

image image::lectureImage(const char* nom)
{
	FILE* F = NULL;
	image img = image(0,0);
	int dynamique = 0;

	if ((F = fopen(nom, "r")) == NULL)
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

			F = fopen(nom, "r");

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

				F = fopen(nom, "rb");

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

int image::getNblig()
{
	return Nblig;
}

int image::getNbCol()
{
	return Nbcol;
}

unsigned char& image::getData(int i) 
{
	return data[i];
}

unsigned char image::getPixel(int i, int j)
{
	if (i >= 0 && i < Nblig && j >= 0 && j < Nbcol) {
		return pixel[i][j];
	}
	else {
		throw std::out_of_range("Index out of range");
	}
}

void image::setPixel(int i, int j, unsigned char value)
{
	if (i >= 0 && i < Nblig && j >= 0 && j < Nbcol)
	{
		pixel[i][j] = value;
	}
	else
	{
		//std::cerr << "Erreur : Indices de pixel hors limites." << std::endl;
		throw std::out_of_range("Index out of range");
	}
}