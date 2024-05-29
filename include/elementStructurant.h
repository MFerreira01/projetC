#pragma once

class ElementStructurant 
{
    public:
        // Constructeur par défaut
        ElementStructurant();

        // Constructeur avec initialisation
        ElementStructurant(char* _type, int _rayon, int _hauteur, int _largeur, int _centreX, int _centreY, unsigned char* _data, unsigned char** _pixel);

        // Destructeur
        ~ElementStructurant();

        // Méthodes d'accès aux membres
        char* getType() const;
        int getRayon() const;
        int getHauteur() const;
        int getLargeur() const;
        int getCentreX() const;
        int getCentreY() const;
        unsigned char* getData() const;
        unsigned char** getPixel() const;

        // Opération morphologique
        image erosionImageSE(image img, const ElementStructurant& SE);
        image dilatationImageSE(image img, const ElementStructurant& SE);
        image ouvertureImageSE(image img, const ElementStructurant& SE);
        image fermetureImageSE(image img, const ElementStructurant& SE);
        image whiteTopHatSE(image img, const ElementStructurant& SE);
        image blackTopHatSE(image img, const ElementStructurant& SE);

        ElementStructurant allocation_SE(const char* type, int rayon);

    private:
        const char* type;
        int rayon;
        int hauteur;
        int largeur;
        int centreX;
        int centreY;
        unsigned char* data;
        unsigned char** pixel;
};