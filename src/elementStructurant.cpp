#include "elementStructurant.h"

#include <cstring> // Pour utiliser strcpy et strdup
#include <iostream> // Pour utiliser les flux de sortie

#include <stdlib.h>
#include <stdio.h>

#include "libCIPSI1.h"
#include "libOutils.h"


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

IMAGE ElementStructurant::erosionImageSE(IMAGE img, const ElementStructurant& SE)
{
	IMAGE imgErode = allocationImage(img.Nblig, img.Nbcol);
	unsigned char min_val;
	unsigned char produit;

	// Parcours de l'image pixel par pixel
	for (int i = 0; i < img.Nblig; i++)
	{
		for (int j = 0; j < img.Nbcol; j++)
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
					if ((x >= 0 && x < img.Nblig) && (y >= 0 && y < img.Nbcol))
					{
						// Calcul du produit pixel à pixel entre la sous-image et l'élément structurant si le pixel de l'élément structurant = 1 sinon rien
						if (SE.getPixel()[k + SE.getRayon()][l + SE.getRayon()] != 0)
						{
							produit = SE.getPixel()[k + SE.getRayon()][l + SE.getRayon()] * img.pixel[x][y];

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
			imgErode.pixel[i][j] = min_val;
		}
	}

	return imgErode;
}

IMAGE ElementStructurant::dilatationImageSE(IMAGE img, const ElementStructurant& SE) 
{
    IMAGE imgDilate = allocationImage(img.Nblig, img.Nbcol);
    unsigned char max_val;
    unsigned char produit;

    // Parcours de l'image pixel par pixel
    for (int i = 0; i < img.Nblig; i++) {
        for (int j = 0; j < img.Nbcol; j++) {
            // Initialisation de la valeur maximale à la valeur minimal possible
            max_val = 0;

            // Parcours de la sous-image recouverte par l'élément structurant centré sur le pixel (i,j)
            for (int k = -SE.getRayon(); k <= SE.getRayon(); k++) {
                for (int l = -SE.getRayon(); l <= SE.getRayon(); l++) {
                    int x = i + k;
                    int y = j + l;

                    // Vérification que le pixel (x,y) est bien dans l'image sinon on fait rien
                    if ((x >= 0 && x < img.Nblig) && (y >= 0 && y < img.Nbcol)) {
                        // Calcul du produit pixel à pixel entre la sous-image et l'élément structurant si le pixel de l'élément structurant = 1 sinon rien
                        if (SE.getPixel()[k + SE.getRayon()][l + SE.getRayon()] != 0) {
                            produit = SE.getPixel()[k + SE.getRayon()][l + SE.getRayon()] * img.pixel[x][y];

                            // Mise à jour de la valeur maximale
                            if (produit > max_val) {
                                max_val = produit;
                            }
                        }
                    }
                }
            }

            // Mise à jour de la valeur du pixel dans l'image dilatée
            imgDilate.pixel[i][j] = max_val;
        }
    }

    return imgDilate;
}

IMAGE ElementStructurant::ouvertureImageSE(IMAGE img, const ElementStructurant& SE) 
{
    IMAGE imgErode = erosionImageSE(img, SE);
    IMAGE imgOpen = dilatationImageSE(imgErode, SE);
    return imgOpen;
}

IMAGE ElementStructurant::fermetureImageSE(IMAGE img, const ElementStructurant& SE)
{
    IMAGE imgOpen = dilatationImageSE(img, SE);
    IMAGE imgErode = erosionImageSE(imgOpen, SE);
    return imgOpen;
}

IMAGE ElementStructurant::whiteTopHatSE(IMAGE img, const ElementStructurant& SE) 
{
    // Appliquer d'abord l'érosion à l'image
    IMAGE imgTemp = erosionImageSE(img, SE);

    // Ensuite, appliquer la dilatation à l'image érodée
    imgTemp = dilatationImageSE(imgTemp, SE);

    // Créer une image pour stocker le résultat du White Top Hat
    IMAGE WhiteTopHat = allocationImage(img.Nblig, img.Nbcol);

    // Parcourir chaque pixel de l'image et calculer le White Top Hat
    for (int i = 0; i < img.Nbcol * img.Nblig; i++) {
        int temp = img.data[i] - imgTemp.data[i];

        // Assurer que la valeur résultante est dans la plage [0, 255]
        if (temp < 0) {
            temp = 0;
        }
        if (temp > 255) {
            temp = 255;
        }

        // Affecter la valeur au pixel correspondant dans l'image White Top Hat
        WhiteTopHat.data[i] = temp;
    }

    return WhiteTopHat;
}

IMAGE ElementStructurant::blackTopHatSE(IMAGE img, const ElementStructurant& SE) 
{
    // Appliquer d'abord la dilatation à l'image
    IMAGE imgTemp = dilatationImageSE(img, SE);

    // Ensuite, appliquer l'érosion à l'image dilatée
    imgTemp = erosionImageSE(imgTemp, SE);

    // Créer une image pour stocker le résultat du Black Top Hat
    IMAGE BlackTopHat = allocationImage(img.Nblig, img.Nbcol);

    // Parcourir chaque pixel de l'image et calculer le Black Top Hat
    for (int i = 0; i < img.Nbcol * img.Nblig; i++) {
        int temp = imgTemp.data[i] - img.data[i];

        // Assurer que la valeur résultante est dans la plage [0, 255]
        if (temp < 0) {
            temp = 0;
        }
        if (temp > 255) {
            temp = 255;
        }

        // Affecter la valeur au pixel correspondant dans l'image Black Top Hat
        BlackTopHat.data[i] = temp;
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

        for (int i = 0; i < SE.largeur; i++) {
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


