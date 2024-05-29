#include "imageRGB.h"

#include <stdlib.h>
#include <iostream>
#include <cstring>

ImageRGB::ImageRGB() : Nblig(0), Nbcol(0), data(nullptr), pixel(nullptr){}

ImageRGB::ImageRGB(int nblig, int nbcol) : Nblig(nblig), Nbcol(nbcol), data(nullptr), pixel(nullptr)
{
	// Allocation de mémoire pour les données
	data = new RGB[Nblig * Nbcol];
	pixel = new RGB * [Nblig];
	for (int i = 0; i < Nblig; ++i)
	{
		pixel[i] = &data[i * Nbcol];
	}
}

ImageRGB ImageRGB::allocationImageRGB(int Nblig, int Nbcol)
{
	ImageRGB mat = { 0,0,NULL,NULL };
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

void ImageRGB::initialisationAleatoireImageRGB(ImageRGB img, int ngMin, int ngMax)
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

int* ImageRGB::histogrammeImageRGB(ImageRGB img, int choix, int n)
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

void ImageRGB::liberationImageRGB(ImageRGB* m)
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

ImageRGB ImageRGB::lectureImageRGB(const char* in)
{
	FILE* F = NULL;
	ImageRGB img = { 0,0,NULL };
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

void sauvegardeImageRGB(ImageRGB img, const char* type, const char* out)
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


int ImageRGB::getNblig()
{
    return Nblig;
}

int ImageRGB::getNbCol()
{
    return Nbcol;
}

unsigned char ImageRGB::getData(int i)
{
    if (i >= 0 && i < Nblig * Nbcol)
    {
        return data[i].R;
    }
    else
    {
        throw std::out_of_range("Index out of range");
    }
}

unsigned char ImageRGB::getPixel(int i, int j)
{
    if (i >= 0 && i < Nblig && j >= 0 && j < Nbcol)
    {
        return pixel[i][j].R;
    }
    else
    {
        throw std::out_of_range("Index out of range");
    }
}

void ImageRGB::setPixel(int i, int j, unsigned char value)
{
    if (i >= 0 && i < Nblig && j >= 0 && j < Nbcol)
    {
        pixel[i][j].R = value; 
        pixel[i][j].G = value; 
        pixel[i][j].B = value; 
    }
    else
    {
        throw std::out_of_range("Index out of range");
    }
}