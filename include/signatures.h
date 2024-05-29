#pragma once
#include "image.h"

class signatures {
public:
    // Constructeur par défaut
    signatures() : min(0), max(0), moyenne(0.0), ecartType(0.0), mediane(0) {}

    // Constructeur avec paramètres
    signatures(int min, int max, double moyenne, double ecartType, int mediane) :
        min(min), max(max), moyenne(moyenne), ecartType(ecartType), mediane(mediane) {}

    signatures statistiquesImage(image img);

    // Méthodes pour obtenir et définir les membres
    int getMin() const { return min; }
    void setMin(int value) { min = value; }

    int getMax() const { return max; }
    void setMax(int value) { max = value; }

    double getMoyenne() const { return moyenne; }
    void setMoyenne(double value) { moyenne = value; }

    double getEcartType() const { return ecartType; }
    void setEcartType(double value) { ecartType = value; }

    int getMediane() const { return mediane; }
    void setMediane(int value) { mediane = value; }

//private:
    int min;
    int max;
    double moyenne;
    double ecartType;
    int mediane;
};
