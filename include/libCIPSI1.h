#pragma once


/* librairie IPSI1 */

typedef struct point
{
	float abscisse;
	float ordonnee;

} POINT;

POINT lecturePoint(void);
void affichePoint(POINT point);
float distancePoints(POINT point1, POINT point2);
POINT milieuPoints(POINT point1, POINT point2);
void generationAleatoirePoints(POINT t[], int n, float min, float max);
POINT centreGravitePoints(POINT t[], int n);
void rechercheAbscissesExtremes(POINT tab[], int n, float* absMin, float* absMax);
void recherchePointsExtremes(POINT tab[], int n, POINT* ptDistMin, POINT* ptDistMax);


image planImage(ImageRGB img, int plan);
image luminanceImage(ImageRGB img, float r, float g, float b);
image expansionImage(image img, int outMin, int outMax);
image egalisationImage(image img);
image seuillageOtsu(image img);
image inverseImage(image img);
image seuillageImage(image img, int sInf, int sSup);
//ImageRGB colorisationImage(ImageRGB img, char* table);
image labelImage(image img, int* nbComp);
image SupprimerComposanteBord(image img, int nbComp);
image ChangerLUT(image img, int* LUT);

double distanceHistogrammeImage(int* h1, int* h2, int taille);

image erosionImage(image img, int voisinage);
image dilatationImage(image img, int voisinage);
image ouvertureImage(image img, int voisinage);
image fermetureImage(image img, int voisinage);
image contourImage(image img, int voisinage);
image whiteTopHat(image img, int voisinage, int n_iteration);
image blackTopHat(image img, int voisinage, int n_iteration);
image SoustractionImage(image img1, image img2);

//int st(IMAGE img1, IMAGE img2);
int UnionImage(image img1, image img2);

void IHMprojet(void);
float* LancementProcess(const char* img2process, int minIntervalle, int maxIntervalle, int numImg);
float Traitement(const char* nomImg, int inversion);
void EnregistrementScore(const char* nomFichier, const char* img2process, int minIntervalle, int maxIntervalle, float* score, int nb_image);
void trieScoreCroissant(float* score, int nb_image);
float* StatistiquesScores(float* scoreTrie, float infoMoyenne, float infoEcartType, int nb_image);
void EnregistrementStats(const char* nomFichier, const char* img2process, float* scoreStats);

image filtreMoyen(image img, int voisinage);
ImageRGB filtreMoyenRGB(ImageRGB img, int voisinage);