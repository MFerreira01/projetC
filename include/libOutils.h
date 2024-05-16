#pragma once

#include <libCIPSI1.h>

typedef struct couleur 
{
	char couleur[20];
	int R;
	int G;
	int B;

}COULEUR;

typedef struct complexe
{
	double Re;
	double Im;

}COMPLEXE;

typedef struct temps
{
	int Heure;
	int Minutes;
	int Secondes;
}TEMPS;

typedef struct tableauint
{
	int* tabDyn;
	int size;

}TABLEAU_INT;

typedef struct mot {
	int longueur;
	char* data;
} MOT;

typedef struct matrice {
	int hauteur;
	int largeur;
	int** valeurs;
} MATRICE;

typedef struct iMatrice
{
	int hauteur;
	int largeur;
	int* valeurs;
	int** ptLignes;
} iMATRICE;

typedef struct resistance
{
	int nombre;
	float* data;
}TAB_RESISTANCE;

#pragma region IMAGE

int calcul1(int N, int M);

int factorielle(int n);

int arrangements(int n, int k);

int combinaisons(int n, int k);

void affichageCombinatoire(int n, int k);

void miseTableauAuCarre(const int tabIn[], int tabOut[], int n);

void affichageTableauInt(int t[], int n);

void initialisationAleatoireTableauInt(int t[], int n, int valMin, int valMax);

void copieTableauInt(int t1[], int t2[], int n);

int minTableauInt(int t[], int n);

int maxTableauInt(int t[], int n);

void triEchangeTableauInt(int t[], int n);

int trieOuNonCroissantTableauInt(int t[], int n);

void inversionTableauInt(int t[], int n);

int chercheElementTableauInt(int t[], int n, int v);

void histogramme(int const tab[], int histo[], int n);

int OTSU(int const histo[], int min_ndg, int max_ndg, int nb_pixel);

int OTSU_opti(int const histo[], int min_ndg, int max_ndg, int nb_pixel);

#pragma endregion

#pragma region COULEUR
//COULEUR
void affichage(COULEUR color);

double distanceEuclidienne(COULEUR color1, COULEUR color2);

#pragma endregion

#pragma region POINT
//POINT
POINT lecturePoint(void);

void affichePoint(POINT point);

float distancePoints(POINT point1, POINT point2);

POINT milieuPoints(POINT point1, POINT point2);

void generationAleatoirePoints(POINT t[], int n, float min, float max);

POINT centreGravitePoints(POINT t[], int n);

void rechercheAbscissesExtremes(POINT tab[], int n, float* absMin, float* absMax);

void recherchePointsExtremes(POINT tab[], int n, POINT* ptDistMin, POINT* ptDistMax);

#pragma endregion

#pragma region COMPLEXE
//COMPLEXE
void afficheComplexe(COMPLEXE complexe);

COMPLEXE lectureComplexe(void);

COMPLEXE conjugueComplexe(COMPLEXE complexe);

double moduleComplexe(COMPLEXE complexe);

COMPLEXE additionComplexe(COMPLEXE complexe1, COMPLEXE complexe2);

COMPLEXE multiplicationComplexe(COMPLEXE complexe1, COMPLEXE complexe2);

#pragma endregion

#pragma region POINTEURS

void echangeInt(int* pa, int* pb);

#pragma endregion

#pragma region TEMPS

TEMPS decomposition_TEMPS(int tps);

void decomposition(int tps, int* h, int* m, int* s);

void lectureTemps(int* tps);

#pragma endregion

#pragma region TABLEAU_INT
void* AllocTableauInt(TABLEAU_INT tDyn);

#pragma endregion

#pragma region MOTS

//PART1
char tirageLettre(void);

char* tirageMot(int taille);

char* copieMot(char* mot1, int taille);

void transformMotMajuscule(char* mot);

void transformMotMinuscule(char* mot);

void multiplicationVoyellesMot(char* mot1, int taille1, int coef, char* mot2, int* taille2);

//PART2
MOT generationMot(int n);

void libereMot(MOT mot);

MOT* tiragePhrase(int nbMots);

//A FINIR

#pragma endregion

#pragma region MATRICE

//MATRICE initialisationMatrice(hauteur, largeur, valeur_Min, valeur_Max);
void liberationMatrice(MATRICE *matrice);
void affichageMatrice(MATRICE matrice);
int traceMatrice(MATRICE matrice);
MATRICE additionMatrice(MATRICE matrice1, MATRICE matrice2);
MATRICE allocationMatrice(int hauteur, int largeur);
MATRICE multiplicationMatrice(MATRICE matrice1, MATRICE matrice2);

#pragma endregion

#pragma region MATRICE

iMATRICE allocation_iMatrice(int hauteur, int largeur);
void remplissageAleatoire_iMatrice(iMATRICE matrice, int valeur_Min, int valeur_Max);
void affichage_iMatrice(iMATRICE matrice);
void liberation_iMatrice(iMATRICE* matrice);
#pragma endregion

#pragma region CONTROLE

int carre(int x);
int fonction1(int T[], int n);
int minTableauIntViaHisto(int T[], int n);
int maxTableauIntViaHisto(int T[], int n);
int trace(int T[], int N);
int puissance(int x, int n);
int evalPolynome(int P[], int n, int x);
int evalPolynomeV2(int P[], int n, int x);

#pragma endregion

#pragma region CONTROLE_DEV_IMAGE

//EX3
TAB_RESISTANCE allocTabResistance(int nb);
float resistanceEquivalente(TAB_RESISTANCE tabres, int type);
TAB_RESISTANCE lectureData(const char* nom);
void enregistreDATA(const char* nom, TAB_RESISTANCE tabres);

//EX4
void regression(POINT* tab, int n, float* a, float* b);
void sortieRegression(const char* nom, POINT* pts, int n);
POINT* ImageVersPoints(IMAGE img, int* n, char axe);
IMAGE imageSortieRegression(IMAGE img, char axe);

#pragma endregion