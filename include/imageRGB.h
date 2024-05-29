#pragma once
#include "RGB.h"

class ImageRGB
{
    public:
        ImageRGB(); 
        ImageRGB(int nblig, int nbcol);

        ImageRGB allocationImageRGB(int Nblig, int Nbcol);
        void initialisationAleatoireImageRGB(ImageRGB img, int ngMin, int ngMax);
        int* histogrammeImageRGB(ImageRGB img, int choix, int n);
        ImageRGB lectureImageRGB(const char* nom);
        void sauvegardeImageRGB(ImageRGB img, const char* type, const char* out);
        void liberationImageRGB(ImageRGB* im);

        int getNblig();
        int getNbCol();
        unsigned char getData(int i);
        unsigned char getPixel(int i, int j);
        void setPixel(int i, int j, unsigned char value);

    //private:
        int Nblig;
        int Nbcol;
        RGB* data;
        RGB** pixel;
};

