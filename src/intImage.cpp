#include "intImage.h"

#include <stdlib.h>
#include <iostream>
#include <cstring>

intImage::intImage::intImage() : Nblig(0), Nbcol(0), data(nullptr), pixel(nullptr) {}

intImage::intImage::intImage(int Nblig, int Nbcol) 
{
	this->Nblig = Nblig;
	this->Nbcol = Nbcol;

	data = new int[Nblig * Nbcol];
	pixel = new int* [Nblig];

	for (int i = 0; i < Nblig; ++i) {
		pixel[i] = &data[i * Nbcol];
	}
}

intImage::~intImage()
{
	delete[] data;
	delete[] pixel;
}

intImage intImage::allocationIntImage(int Nblig, int Nbcol)
{
	intImage mat = allocationIntImage(0,0);
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

void intImage::liberationIntImage(intImage* img)
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

int intImage::getNblig() const
{
	return Nblig;
}

int intImage::getNbcol() const
{
	return Nbcol;
}

int* intImage::getData() const
{
	return data;
}

int intImage::getPixel(int i, int j) const
{
	if (i >= 0 && i < Nblig && j >= 0 && j < Nbcol) {
		return pixel[i][j];
	}
	else {
		throw std::out_of_range("Index out of range");
	}
}

void intImage::setPixel(int i, int j, unsigned char value)
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