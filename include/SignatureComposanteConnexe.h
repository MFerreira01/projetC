#pragma once
#include "point.h"

class SignatureComposanteConnexe {
public:
    // Constructeur par défaut
    SignatureComposanteConnexe() : surface(0), perimetre(0.0f), compacite(0.0f), bord(0), rayon(0.0f), suppr(0) {}

    // Méthodes pour obtenir et définir les membres
    int getSurface() const { return surface; }
    void setSurface(int value) { surface = value; }

    float getPerimetre() const { return perimetre; }
    void setPerimetre(float value) { perimetre = value; }

    float getCompacite() const { return compacite; }
    void setCompacite(float value) { compacite = value; }

    int getBord() const { return bord; }
    void setBord(int value) { bord = value; }

    const point& getCG() const { return CG; }
    void setCG(const point& value) { CG = value; }

    float getRayon() const { return rayon; }
    void setRayon(float value) { rayon = value; }

    int getSuppr() const { return suppr; }
    void setSuppr(int value) { suppr = value; }

//private:
    int surface;
    float perimetre;
    float compacite;
    int bord;
    point CG;
    float rayon;
    int suppr;
};
