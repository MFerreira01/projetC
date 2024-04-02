#pragma once


/* librairie IPSI1 */

typedef struct point
{
	float abscisse;
	float ordonnee;

}POINT;

typedef struct image {
	int   Nblig;
	int   Nbcol;
	unsigned char*  data;
	unsigned char** pixel;
} IMAGE;

typedef struct rgb {
	unsigned char R;
	unsigned char G;
	unsigned char B;
} RGB;

typedef struct imageRGB {
	int   Nblig;
	int   Nbcol;
	RGB*  data;
	RGB** pixel;
} IMAGERGB;

typedef struct signatures {
	int		min;
	int		max;
	double	moyenne;
	double	ecartType;
	int		mediane;
} SIGNATURES;

typedef struct signature_composantes_connexes {
	int surface;
	float perimetre;
	float compacite;
	int bord;
	POINT CG;
	float rayon;

	int suppr;
} SIGNATURE_COMPOSANTE_CONNEXE;

typedef struct element_structurant {
	char* type;
	int rayon;
	int hauteur;
	int largeur;
	int centreX;
	int centreY;
	unsigned char* data;
	unsigned char** pixel;
} ELEMENT_STRUCTURANT;


#pragma region POINT
/// <summary>
/// Demande a l'utilisateur les coordonnées d'un point
/// </summary>
/// <param name=""></param>
/// <returns>le point en question</returns>
POINT lecturePoint(void);
/// <summary>
/// Permet d'afficher un point
/// </summary>
/// <param name="point"></param>
void affichePoint(POINT point);
/// <summary>
/// Calcul la distance euclienne entre deux points
/// </summary>
/// <param name="point1"></param>
/// <param name="point2"></param>
/// <returns>la distance euclidienne</returns>
float distancePoints(POINT point1, POINT point2);
/// <summary>
/// Calcul le point au milieu de deux points
/// </summary>
/// <param name="point1"></param>
/// <param name="point2"></param>
/// <returns>point central</returns>
POINT milieuPoints(POINT point1, POINT point2);
/// <summary>
/// Générer un point aléatoire
/// </summary>
/// <param name="t : Tableau de point"></param>
/// <param name="n : Taille du tableau"></param>
/// <param name="min : Coordonné minimum"></param>
/// <param name="max : Coordonné maximum"></param>
void generationAleatoirePoints(POINT t[], int n, float min, float max);
/// <summary>
/// Calcul le centre de gravite d'une liste de point
/// </summary>
/// <param name="t : tableau de point"></param>
/// <param name="n : taille du tableau"></param>
/// <returns>centre de gravité</returns>
POINT centreGravitePoints(POINT t[], int n);
/// <summary>
/// Recherche l'abiscsse minimum et maximum dans une liste de point
/// </summary>
/// <param name="tab : tableau de point"></param>
/// <param name="n : taille du tableau"></param>
/// <param name="absMin : abscisse minimum à trouver"></param>
/// <param name="absMax : abscisse maximum à trouver"></param>
void rechercheAbscissesExtremes(POINT tab[], int n, float* absMin, float* absMax);
/// <summary>
/// Recherche le point le moins loin du CG et le point le plus loin du CG d'une liste de point
/// </summary>
/// <param name="tab : tableau de point"></param>
/// <param name="n : taille du tableau"></param>
/// <param name="ptDistMin : point moins loin"></param>
/// <param name="ptDistMax : point plus loin"></param>
void recherchePointsExtremes(POINT tab[], int n, POINT* ptDistMin, POINT* ptDistMax);
#pragma endregion

#pragma region IMAGE
/// <summary>
/// Permet d'alloué une image
/// </summary>
/// <param name="Nblig : Nombre de ligne"></param>
/// <param name="Nbcol : Nombre de colonne"></param>
/// <returns>img alloué</returns>
IMAGE allocationImage(int Nblig, int Nbcol);
/// <summary>
/// Permet d'initialiser aléatoirement une image
/// </summary>
/// <param name="img"></param>
/// <param name="ngMin : NDG minimum"></param>
/// <param name="ngMax : NDG maximum"></param>
void initialisationAleatoireImage(IMAGE img, int ngMin, int ngMax);
/// <summary>
/// Histogramme de l'image
/// </summary>
/// <param name="img"></param>
/// <param name="choix : 0 --> Pas enregistrer fichier CSV 1 --> Enregister fichier CSV"></param>
/// <param name="n : Nombre de niveau de gris"></param>
/// <returns>histrogamme de l'image</returns>
int* histogrammeImage(IMAGE img, int choix, int n);
/// <summary>
/// Permet de sauvegarder une image
/// </summary>
/// <param name="img"></param>
/// <param name="type : P5 : binaire & P2 : ASCII "></param>
/// <param name="out : nomimage.pgm"></param>
void sauvegardeImage(IMAGE img, const char *type, const char *out);
/// <summary>
/// Permet de libérer la mémoire utilisé par une image
/// </summary>
/// <param name="im"></param>
void liberationImage(IMAGE *im);
/// <summary>
/// Permet de lire une image
/// </summary>
/// <param name="nom : nomimage.pgm"></param>
/// <returns>img en question</returns>
IMAGE lectureImage(const char *nom);
#pragma endregion

#pragma region IMAGE_RGB
/// <summary>
/// Permet d'allouer une imgRGB
/// </summary>
/// <param name="Nblig : Nombre de ligne"></param>
/// <param name="Nbcol : Nombre de colonne"></param>
/// <returns>img alloué</returns>
IMAGERGB allocationImageRGB(int Nblig, int Nbcol);
/// <summary>
/// Permet d'initialiser aléatoirement une imgRGB
/// </summary>
/// <param name="img"></param>
/// <param name="ngMin : NDG minimum"></param>
/// <param name="ngMax : NDG maximum "></param>
void initialisationAleatoireImageRGB(IMAGERGB img, int ngMin, int ngMax);
/// <summary>
/// Histrogramme d'une imageRGB
/// </summary>
/// <param name="img"></param>
/// <param name="choix : 0 --> Pas enregistrer fichier CSV 1 --> Enregister fichier CSV"></param>
/// <param name="n : Nombre de niveau de gris"></param>
/// <returns></returns>
int* histogrammeImageRGB(IMAGERGB img, int choix, int n);
/// <summary>
/// Permet de lire une imageRGB
/// </summary>
/// <param name="nom : nomimage.ppm"></param>
/// <returns>imgRGB en question</returns>
IMAGERGB lectureImageRGB(const char *nom);
/// <summary>
/// Sauvegarder une imageRGB
/// </summary>
/// <param name="img"></param>
/// <param name="type : P6 : binaire ou P3 : ASCII"></param>
/// <param name="out : nomimg.ppm"></param>
void sauvegardeImageRGB(IMAGERGB img, const char *type, const char *out);
/// <summary>
/// Permet de libérer la mémoire utilisé par une imgRGB
/// </summary>
/// <param name="im"></param>
void liberationImageRGB(IMAGERGB *im);
#pragma endregion

#pragma region TRAITEMENT
/// <summary>
/// AUCUNE IDEE
/// </summary>
/// <param name="img"></param>
/// <param name="plan"></param>
/// <returns></returns>
IMAGE planImage(IMAGERGB img, int plan);
/// <summary>
/// AUCUNE IDEE
/// </summary>
/// <param name="img"></param>
/// <param name="r"></param>
/// <param name="g"></param>
/// <param name="b"></param>
/// <returns></returns>
IMAGE luminanceImage(IMAGERGB img, float r, float g, float b);
/// <summary>
/// Effectue une expansion
/// </summary>
/// <param name="img"></param>
/// <param name="outMin : valeur min ndg voulu"></param>
/// <param name="outMax : valeur max ng voulu"></param>
/// <returns>img avec une nouvelle dynamique</returns>
IMAGE expansionImage(IMAGE img, int outMin, int outMax);
/// <summary>
/// Effectue une égalisation
/// </summary>
/// <param name="img"></param>
/// <returns>img égalisé</returns>
IMAGE egalisationImage(IMAGE img);
/// <summary>
/// Seuillage OTSU
/// </summary>
/// <param name="img"></param>
/// <returns>img seuillé</returns>
IMAGE seuillageOtsu(IMAGE img);
/// <summary>
/// Inversé l'image
/// </summary>
/// <param name="img"></param>
/// <returns>img inversé</returns>
IMAGE inverseImage(IMAGE img);
/// <summary>
/// Seuillé une image
/// </summary>
/// <param name="img"></param>
/// <param name="sInf : seuil 1"></param>
/// <param name="sSup : seuil 2"></param>
/// <returns>Img seuillé</returns>
IMAGE seuillageImage(IMAGE img, int sInf, int sSup);
/// <summary>
/// Colorise l'image passé en paramètre avec la lut souhaité
/// </summary>
/// <param name="img"></param>
/// <param name="table : nom du fichier correpondant à la LUT voulu"></param>
/// <returns>imgRGB l'image colorisé</returns>
IMAGERGB colorisationImage(IMAGE img, char* table);
/// <summary>
/// Labelisation de l'image
/// </summary>
/// <param name="img : img binaire"></param>
/// <param name="nbComp : Variable qui va contenir le nombre de composante"></param>
/// <returns>img labelisé</returns>
IMAGE labelImage(IMAGE img, int* nbComp);
/// <summary>
/// Permet de supprimer les composantes touchant les bords
/// </summary>
/// <param name="img : Image labelisé"></param>
/// <param name="nbComp : Nombre de composante"></param>
/// <returns>img sans les composantes touchant les bords</returns>
IMAGE SupprimerComposanteBord(IMAGE img, int nbComp);
/// <summary>
/// Appliquer une LUT sur l'image
/// </summary>
/// <param name="img"></param>
/// <param name="LUT"></param>
/// <returns>img avec LUT appliqué</returns>
IMAGE ChangerLUT(IMAGE img, int* LUT);
#pragma endregion

#pragma region STATISTIQUES_SIGNATURES
/// <summary>
/// Calcul la distance entre 2 histogrammes
/// </summary>
/// <param name="h1 : Histogramme 1"></param>
/// <param name="h2 : Histogramme 2"></param>
/// <param name="taille : Taille histogramme"></param>
/// <returns></returns>
double distanceHistogrammeImage(int* h1, int* h2, int taille);
/// <summary>
/// Obtenir les statistiques de l'image
/// </summary>
/// <param name="img"></param>
/// <returns>structure contenant les stats de l'image</returns>
SIGNATURES statistiquesImage(IMAGE img);
/// <summary>
/// Obtenir les signatures des composantes
/// </summary>
/// <param name="img : Image labelisé"></param>
/// <param name="nbComp : Nombre de composante"></param>
/// <returns>Tableau de signature pour chaque composante</returns>
SIGNATURE_COMPOSANTE_CONNEXE* signaturesImage(IMAGE img, int nbComp);
#pragma endregion

#pragma region MORPHOLOGIE V4/V8
/// <summary>
/// Fait une erosion
/// </summary>
/// <param name="img"></param>
/// <param name="voisinage -> 4 pour V4 -> 8 pour V8"></param>
/// <returns>img érodé</returns>
IMAGE erosionImage(IMAGE img, int voisinage);
/// <summary>
/// Fait une erosion avec un element structurant
/// </summary>
/// <param name="img"></param>
/// <param name="SE">Notre structure element</param>
/// <returns></returns>
IMAGE erosionImageSE(IMAGE img, ELEMENT_STRUCTURANT SE);
/// <summary>
/// Fait une dilatation
/// </summary>
/// <param name="img"></param>
/// <param name="voisinage -> 4 pour V4 -> 8 pour V8"></param>
/// <returns>img dilaté</returns>
IMAGE dilatationImage(IMAGE img, int voisinage);
/// <summary>
/// Fait une dilatation avec un element structurant
/// </summary>
/// <param name="img"></param>
/// <param name="SE">Notre element structurant</param>
/// <returns></returns>
IMAGE dilatationImageSE(IMAGE img, ELEMENT_STRUCTURANT SE);
/// <summary>
/// Fait une Ouverture
/// </summary>
/// <param name="img"></param>
/// <param name="voisinage -> 4 pour V4 -> 8 pour V8"></param>
/// <returns>img ouverte</returns>
IMAGE ouvertureImage(IMAGE img, int voisinage);
/// <summary>
/// Fait une Ouverture avec notre element structurant
/// </summary>
/// <param name="img"></param>
/// <param name="SE">notre element structurant</param>
/// <returns></returns>
IMAGE ouvertureImageSE(IMAGE img, ELEMENT_STRUCTURANT SE);
/// <summary>
/// Fait une Fermeture
/// </summary>
/// <param name="img"></param>
/// <param name="voisinage -> 4 pour V4 -> 8 pour V8"></param>
/// <returns>img fermé</returns>
IMAGE fermetureImage(IMAGE img, int voisinage);
/// <summary>
///  Fait une Fermeture avec notre element structurant
/// </summary>
/// <param name="img"></param>
/// <param name="SE">notre element structurant</param>
/// <returns></returns>
IMAGE fermetureImageSE(IMAGE img, ELEMENT_STRUCTURANT SE);
/// <summary>
///Fait le contour des composantes
/// </summary>
/// <param name="img"></param>
/// <param name="voisinage -> 4 pour V4 -> 8 pour V8"></param>
/// <returns>img des contours</returns>
IMAGE contourImage(IMAGE img, int voisinage);
/// <summary>
/// white tophat (supprime le fond)
/// </summary>
/// <param name="img">Image</param>
/// <param name="voisinage">voisinage -> 4 pour V4 -> 8 pour V8</param>
/// <returns>image whitetophat</returns>
IMAGE whiteTopHat(IMAGE img, int voisinage, int n_iteration);
/// <summary>
///  white tophat avec notre element structurant (supprime le fond)
/// </summary>
/// <param name="img"></param>
/// <param name="SE">notre element structurant</param>
/// <returns></returns>
IMAGE whiteTopHatSE(IMAGE img, ELEMENT_STRUCTURANT SE);
/// <summary>
/// black tophat
/// </summary>
/// <param name="img">Image</param>
/// <param name="voisinage">voisinage -> 4 pour V4 -> 8 pour V8</param>
/// <returns>image blacktophat</returns>
IMAGE blackTopHat(IMAGE img, int voisinage, int n_iteration);
/// <summary>
/// black tophat avec notre element structurant
/// </summary>
/// <param name="img"></param>
/// <param name="SE">notre element structurant</param>
/// <returns></returns>
IMAGE blackTopHatSE(IMAGE img, ELEMENT_STRUCTURANT SE);
/// <summary>
/// Soustrait 2 images
/// </summary>
/// <param name="img1">L'image 1</param>
/// <param name="img2">L'image 2</param>
/// <returns>L'image soustrait</returns>
IMAGE SoustractionImage(IMAGE img1, IMAGE img2);

/// <summary>
/// Calcul l'intersection entre 2 images
/// </summary>
/// <param name="img1"></param>
/// <param name="img2"></param>
/// <returns>le noombre de pixel dans l'intersection</returns>
int st(IMAGE img1, IMAGE img2);

/// <summary>
/// Calcul l'union entre 2 images
/// </summary>
/// <param name="img1"></param>
/// <param name="img2"></param>
/// <returns>le nombre de pixel dans l'union</returns>
int UnionImage(IMAGE img1, IMAGE img2);
#pragma endregion

#pragma region ELEMENT STRUCTURANT
/// <summary>
/// Crée un SE
/// </summary>
/// <param name="type">Type de SE 'disk'</param>
/// <param name="rayon">rayon pour le SE</param>
/// <returns>Le SE</returns>
ELEMENT_STRUCTURANT allocation_SE(const char* type, int rayon);
#pragma endregion

#pragma region PROJET
/// <summary>
/// IHM du projet
/// </summary>
/// <param name=""></param>
void IHMprojet(void);
/// <summary>
/// Lance le process
/// </summary>
/// <param name="img2process">Savoir sur quelle type d'image on bosse 'In' 'Sc' 'lotIn' 'lotSc' 'allIn' 'allSc' 'all'</param>
/// <param name="minIntervalle">le min du lot (pour 'lotIn' ou 'lotSc')</param>
/// <param name="maxIntervalle">le max du lot (pour 'lotIn' ou 'lotSc')</param>
/// <param name="numImg">le num de l'image (pour 'In' ou 'Sc')</param>
/// <returns>score global</returns>
float* LancementProcess(const char* img2process, int minIntervalle, int maxIntervalle, int numImg);
/// <summary>
/// Lance le traitement sur les images
/// </summary>
/// <param name="nomImg">L'image a traiter</param>
/// <param name="inversion">Si il faut inverser l'image avant ou pas selon In ou Sc</param>
/// <returns>Le score de l'image</returns>
float Traitement(const char* nomImg, int inversion);
/// <summary>
/// Enregistrer les scores détaillés des images
/// </summary>
/// <param name="nomFichier">Nom du fichier CSV</param>
/// <param name="img2process">Savoir quelle type on enregistre 'lotIn' 'lotSc' 'allIn' 'allSc' 'all'</param>
/// <param name="minIntervalle">le min du lot (pour 'lotIn' ou 'lotSc')</param>
/// <param name="maxIntervalle">le max du lot (pour 'lotIn' ou 'lotSc')</param>
/// <param name="score">Ensemble des scores de l'image</param>
/// <param name="nb_image">Nombre d'images des datasets</param>
void EnregistrementScore(const char* nomFichier, const char* img2process, int minIntervalle, int maxIntervalle, float* score, int nb_image);
/// <summary>
/// Permet de trier les scores dans l'ordre croissant
/// </summary>
/// <param name="tableau"> score</param>
/// <param name="taille"> nb de score</param>
/// <returns>score trié</returns>
void trieScoreCroissant(float* score, int nb_image);
/// <summary>
/// Calcul statistiques des scores 
/// </summary>
/// <param name="score">score trier dans l'ordre croissant</param>
/// <param name="infoMoyenne">info pour calculer moyenne</param>
/// <param name="infoEcartType">info pour calculer l'ecart type</param>
/// <param name="nb_image"></param>
/// <returns>Statistiques scores</returns>
float* StatistiquesScores(float* scoreTrie, float infoMoyenne, float infoEcartType, int nb_image);
/// <summary>
/// Enregistre les stats des scores
/// </summary>
/// <param name="nomFichier">Nom fichier csv</param>
/// <param name="img2process">Savoir quelle type on enregistre 'lotIn' 'lotSc' 'allIn' 'allSc' 'all'</param>
/// <param name="scoreStats">Ensemble des stats</param>
void EnregistrementStats(const char* nomFichier, const char* img2process, float* scoreStats);
#pragma endregion

#pragma region FILTRES

/// <summary>
/// Filtre moyen sur image NDG
/// </summary>
/// <param name="img"></param>
/// <param name="voisinage">Voisin N*N</param>
/// <returns></returns>
IMAGE filtreMoyen(IMAGE img, int voisinage);
/// <summary>
/// Filtre moyen sur image RGB (canaux par canaux)
/// </summary>
/// <param name="img"></param>
/// <param name="voisinage">Voisin N*N</param>
/// <returns></returns>
IMAGERGB filtreMoyenRGB(IMAGERGB img, int voisinage);

#pragma endregion