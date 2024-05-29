#include "elementStructurant.h"

#include <cstring> // Pour utiliser strcpy et strdup
#include <iostream> // Pour utiliser les flux de sortie

#include <stdlib.h>
#include <stdio.h>
#include "image.h"

// Constructeur par défaut
ElementStructurant::ElementStructurant() : type(nullptr), rayon(0), hauteur(0), largeur(0), centreX(0), centreY(0), data(nullptr), pixel(nullptr) {}

// Constructeur avec initialisation
ElementStructurant::ElementStructurant(char* _type, int _rayon, int _hauteur, int _largeur, int _centreX, int _centreY, unsigned char* _data, unsigned char** _pixel) 
{
    type = strdup(_type); // strdup alloue la mémoire nécessaire et copie la chaîne
    rayon = _rayon;
    hauteur = _hauteur;
    largeur = _largeur;
    centreX = _centreX;
    centreY = _centreY;
    data = _data;
    pixel = _pixel;
}

// Destructeur
ElementStructurant::~ElementStructurant() 
{
    if (type != nullptr) 
    {
        delete[] type;
    }
    if (data != nullptr) 
    {
        delete[] data;
    }
    if (pixel != nullptr) 
    {
        delete[] pixel;
    }
}

// Méthodes d'accès aux membres
/*const char* ElementStructurant::getType() const 
{
    return type;
}*/

int ElementStructurant::getRayon() const 
{
    return rayon;
}

int ElementStructurant::getHauteur() const 
{
    return hauteur;
}

int ElementStructurant::getLargeur() const 
{
    return largeur;
}

int ElementStructurant::getCentreX() const 
{
    return centreX;
}

int ElementStructurant::getCentreY() const 
{
    return centreY;
}

unsigned char* ElementStructurant::getData() const 
{
    return data;
}

unsigned char** ElementStructurant::getPixel() const 
{
    return pixel;
}

image ElementStructurant::erosionImageSE(image img, const ElementStructurant& SE)
{
    image imgErode = image(img.getNblig(), img.getNbCol());
	unsigned char min_val;
	unsigned char produit;

	// Parcours de l'image pixel par pixel
	for (int i = 0; i < img.getNblig(); i++)
	{
		for (int j = 0; j < img.getNbCol(); j++)
		{
			// Initialisation de la valeur minimale à la valeur maximale possible
			min_val = UCHAR_MAX;

			// Parcours de la sous-image recouverte par l'élément structurant centré sur le pixel (i,j)
			for (int k = -SE.getRayon(); k <= SE.getRayon(); k++)
			{
				for (int l = -SE.getRayon(); l <= SE.getRayon(); l++)
				{
					int x = i + k;
					int y = j + l;

					// Vérification que le pixel (x,y) est bien dans l'image sinon on fait rien
					if ((x >= 0 && x < img.getNblig()) && (y >= 0 && y < img.getNbCol()))
					{
						// Calcul du produit pixel à pixel entre la sous-image et l'élément structurant si le pixel de l'élément structurant = 1 sinon rien
						if (SE.getPixel()[k + SE.getRayon()][l + SE.getRayon()] != 0)
						{
							produit = SE.getPixel()[k + SE.getRayon()][l + SE.getRayon()] * img.getPixel(x,y);

							// Mise à jour de la valeur minimale
							if (produit < min_val)
							{
								min_val = produit;
							}
						}
					}
				}
			}
            // Mise à jour de la valeur du pixel dans l'image érodée
            imgErode.setPixel(i, j, min_val);
		}
	}

	return imgErode;
}

image ElementStructurant::dilatationImageSE(image img, const ElementStructurant& SE)
{
    image imgDilate = image(img.getNblig(), img.getNbCol());
    unsigned char max_val;
    unsigned char produit;

    // Parcours de l'image pixel par pixel
    for (int i = 0; i < img.getNblig(); i++) {
        for (int j = 0; j < img.getNbCol(); j++) {
            // Initialisation de la valeur maximale à la valeur minimal possible
            max_val = 0;

            // Parcours de la sous-image recouverte par l'élément structurant centré sur le pixel (i,j)
            for (int k = -SE.getRayon(); k <= SE.getRayon(); k++) {
                for (int l = -SE.getRayon(); l <= SE.getRayon(); l++) {
                    int x = i + k;
                    int y = j + l;

                    // Vérification que le pixel (x,y) est bien dans l'image sinon on fait rien
                    if ((x >= 0 && x < img.getNblig()) && (y >= 0 && y < img.getNbCol())) {
                        // Calcul du produit pixel à pixel entre la sous-image et l'élément structurant si le pixel de l'élément structurant = 1 sinon rien
                        if (SE.getPixel()[k + SE.getRayon()][l + SE.getRayon()] != 0) {
                            produit = SE.getPixel()[k + SE.getRayon()][l + SE.getRayon()] * img.getPixel(x, y);

                            // Mise à jour de la valeur maximale
                            if (produit > max_val) {
                                max_val = produit;
                            }
                        }
                    }
                }
            }

            // Mise à jour de la valeur du pixel dans l'image dilatée
            imgDilate.setPixel(i, j, max_val);
        }
    }

    return imgDilate;
}

image ElementStructurant::ouvertureImageSE(image img, const ElementStructurant& SE)
{
    image imgErode = erosionImageSE(img, SE);
    image imgOpen = dilatationImageSE(imgErode, SE);
    return imgOpen;
}

image ElementStructurant::fermetureImageSE(image img, const ElementStructurant& SE)
{
    image imgOpen = dilatationImageSE(img, SE);
    image imgErode = erosionImageSE(imgOpen, SE);
    return imgOpen;
}

image ElementStructurant::whiteTopHatSE(image img, const ElementStructurant& SE)
{
    // Appliquer d'abord l'érosion à l'image
    image imgTemp = erosionImageSE(img, SE);

    // Ensuite, appliquer la dilatation à l'image érodée
    imgTemp = dilatationImageSE(imgTemp, SE);

    // Créer une image pour stocker le résultat du White Top Hat
    image WhiteTopHat = image(img.getNblig(), img.getNbCol());

    // Parcourir chaque pixel de l'image et calculer le White Top Hat
    for (int i = 0; i < img.getNblig(); i++)
    {
        for (int j = 0; j < img.getNbCol(); j++)
        {
            int temp = img.getPixel(i, j) - imgTemp.getPixel(i, j);

            // Assurer que la valeur résultante est dans la plage [0, 255]
            if (temp < 0) {
                temp = 0;
            }
            if (temp > 255) {
                temp = 255;
            }

            // Affecter la valeur au pixel correspondant dans l'image White Top Hat
            WhiteTopHat.setPixel(i, j, temp);
        }
    }

    return WhiteTopHat;
}

image ElementStructurant::blackTopHatSE(image img, const ElementStructurant& SE)
{
    // Appliquer d'abord la dilatation à l'image
    image imgTemp = dilatationImageSE(img, SE);

    // Ensuite, appliquer l'érosion à l'image dilatée
    imgTemp = erosionImageSE(imgTemp, SE);

    // Créer une image pour stocker le résultat du Black Top Hat
    image BlackTopHat = image(img.getNblig(), img.getNbCol());

    // Parcourir chaque pixel de l'image et calculer le Black Top Hat
    for (int i = 0; i < img.getNblig(); i++) 
    {
        for (int j = 0; j < img.getNbCol(); j++) {

            unsigned char temp = imgTemp.getPixel(i, j) - img.getPixel(i, j);

            // Assurer que la valeur résultante est dans la plage [0, 255]
            if (temp < 0) 
            {
                temp = 0;
            }
            if (temp > 255) 
            {
                temp = 255;
            }

            // Affecter la valeur au pixel correspondant dans l'image Black Top Hat
            BlackTopHat.setPixel(i, j, temp);
        }
    }

    return BlackTopHat;
}

void remplissage4(unsigned char** pixel, int x, int y, int colcible, int colrep)
{
    //Permet de remplir une forme avec voisinnage V4
    if (pixel[x][y] == colcible)
    {
        pixel[x][y] = colrep;

        remplissage4(pixel, x - 1, y, colcible, colrep);
        remplissage4(pixel, x + 1, y, colcible, colrep);
        remplissage4(pixel, x, y + 1, colcible, colrep);
        remplissage4(pixel, x, y - 1, colcible, colrep);
    }
}

ElementStructurant ElementStructurant::allocation_SE(const char* type, int rayon) 
{
    ElementStructurant SE;

    // Initialise les membres de l'élément structurant
    SE.type = type;
    SE.rayon = rayon;
    SE.hauteur = SE.rayon * 2 + 1;
    SE.largeur = SE.rayon * 2 + 1;

    if (std::strcmp(type, "disk") == 0) { // Création d'un ES de type disque
        int taille_SE = SE.hauteur * SE.largeur;
        SE.data = new unsigned char[taille_SE](); // Initialise tous les éléments à zéro
        SE.pixel = new unsigned char* [SE.largeur];

        for (int i = 0; i < SE.largeur; i++) 
        {
            SE.pixel[i] = &SE.data[i * SE.hauteur];
        }

        // Définis le centre
        int centerX = SE.rayon;
        int centerY = SE.rayon;

        int x = 0;
        int y = SE.rayon;
        int m = 5 - 4 * SE.rayon;

        // Permet de créer le contour d'un disque du rayon choisi
        while (x <= y) {
            SE.pixel[centerX + x][centerY + y] = 1;
            SE.pixel[centerX + x][centerY - y] = 1;
            SE.pixel[centerX - x][centerY + y] = 1;
            SE.pixel[centerX - x][centerY - y] = 1;
            SE.pixel[centerX + y][centerY + x] = 1;
            SE.pixel[centerX + y][centerY - x] = 1;
            SE.pixel[centerX - y][centerY + x] = 1;
            SE.pixel[centerX - y][centerY - x] = 1;

            if (m > 0) {
                y--;
                m -= 8 * y;
            }

            x++;
            m += 8 * x + 4;
        }

        remplissage4(SE.pixel, SE.rayon, SE.rayon, 0, 1); // Remplit le disque
    }

    // Retourne l'élément structurant
    return SE;
}
