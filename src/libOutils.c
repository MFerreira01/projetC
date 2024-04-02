#pragma once
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "libOutils.h"

#pragma region IMAGE
int calcul1(int N, int M)
{
	int S = 0;

	/* calcul, coeur du programme */
	/* variables intermédiaires utiles mais "transparentes" pour l'utilisateur du main */
	int tempN = N, tempM = M;

	while (tempN != 1)
	{
		if (tempN % 2 == 1)
			S += tempM;
		tempN /= 2;
		tempM *= 2;
	}
	S = S + tempM;
	/* fin du calcul */

	return S;
}

int factorielle(int n)
{
	int res = 1;

	while (n != 0)
	{
		res = res * n;
		n--;
	}

	return res;
}


int arrangements(int n, int k)
{
	return (factorielle(n) / factorielle(n - k));
}

int combinaisons(int n, int k)
{
	return (arrangements(n, k) / factorielle(k));
}

void affichageCombinatoire(int n, int k)
{
	printf("Entrer n et k : %d %d\n", n, k);
	printf("A(%d,%d) = %d\n", n, k, arrangements(n, k));
	printf("C(%d,%d) = %d\n", n, k, combinaisons(n, k));
}

void miseTableauAuCarre(const int tabIn[], int tabOut[], int n)
{
	for (int i = 0; i < n; i++)
		tabOut[i] = tabIn[i] * tabIn[i];
}

void affichageTableauInt(int t[], int n)
{

	for (int i = 0; i < n; i++)
		printf("%d ", t[i]);
	printf("\n");
}

void initialisationAleatoireTableauInt(int t[], int n, int valMin, int valMax)
{
	for (int i = 0; i < n; i++)
		t[i] = valMin + rand() % (valMax + 1 - valMin);
}

void copieTableauInt(int t1[], int t2[], int n)
{
	for (int i = 0; i < n; i++)
	{
		t2[i] = t1[i];
	}
}

int minTableauInt(int t[], int n)
{
	int min = t[0];

	for (int i = 1; i < n; i++)
	{
		if (t[i] < min)
		{
			min = t[i];
		}
	}

	return min;
}


int maxTableauInt(int t[], int n)
{
	int max = t[0];

	for (int i = 1; i < n; i++)
	{
		if (t[i] > max)
		{
			max = t[i];
		}
	}

	return max;
}

void triEchangeTableauInt(int t[], int n)
{
	int j = 0, temp, i = 0, indice = 0, min, etape = 0;

	for (j = 0; j < n; j++)
	{
		min = t[j];
		for (int i = 1 + etape; i < n; i++)
		{
			if (t[i] < min)
			{
				min = t[i];
				indice = i;
			}
		}
		temp = t[j];
		t[j] = min;
		t[indice] = temp;
		etape++;
	}
}

int trieOuNonCroissantTableauInt(int t[], int n)
{

	for (int i = 0; i < n - 1; i++)
	{
		if (t[i + 1] != t[i] + 1)
		{
			return 0;
		}
	}
	return 1;
}

void inversionTableauInt(int t[], int n)
{
	int temp, temp_n = n;

	for (int i = 0; i < n / 2; i++)
	{
		temp = t[i];
		t[i] = t[temp_n - 1];
		t[temp_n - 1] = temp;
		temp_n--;
	}
}

int chercheElementTableauInt(int t[], int n, int v)
{

	for (int i = 0; i < n; i++)
	{
		if (t[i] == v)
		{
			return i;
		}
	}

	return -1;

}

void histogramme(int const tab[], int histo[], int n)
{
	int indice = 0;

	for (int i = 0; i < n; i++)
	{
		indice = tab[i];
		histo[indice]++;
	}
}

int OTSU(int const histo[], int min_ndg, int max_ndg, int nb_pixel)
{
	float V[256] = { 0 };

	float W1, W2, M1, M2;
	int nbPix = nb_pixel, Otsu = min_ndg;

	for (int s = min_ndg; s <= max_ndg - 1; s++)
	{
		W1 = W2 = M1 = M2 = 0;

		for (int s1 = min_ndg; s1 <= s; s1++)
		{
			W1 += histo[s1];
			M1 += s1 * histo[s1];
		}
		for (int s2 = s + 1; s2 <= max_ndg; s2++)
		{
			W2 += histo[s2];
			M2 += s2 * histo[s2];
		}

		M1 /= W1;
		M2 /= W2;
		W1 /= nbPix;
		W2 /= nbPix;

		V[s] = W1 * W2 * (M1 - M2) * (M1 - M2);
		if (V[s] > V[Otsu])
			Otsu = s;
	}

	return Otsu;
}

int OTSU_opti(int const histo[], int min_ndg, int max_ndg, int nb_pixel)
{
	float V[256] = { 0 };
	float W1, W2, M1, M2;
	int nbPix = nb_pixel, Otsu = min_ndg;

	int HC[256] = { 0 };
	/* histo cumul� -> outil � ajouter � lib ??? */
	HC[min_ndg] = histo[min_ndg];
	for (int i = min_ndg + 1; i <= max_ndg; i++)
		HC[i] = HC[i - 1] + histo[i];

	/* initialisation */
	M1 = min_ndg;
	W1 = (float)histo[min_ndg] / (float)(nbPix);
	M2 = 0;
	for (int i = min_ndg + 1; i <= max_ndg; i++)
		M2 += (float)histo[i] * i;
	M2 /= (double)(nbPix - histo[min_ndg]);
	V[min_ndg] = W1 * (1 - W1) * (M1 - M2) * (M1 - M2);

	// parcours
	for (int s = min_ndg + 1; s < max_ndg; s++) {
		M1 = ((float)HC[s - 1] * M1 + (float)histo[s] * s) / HC[s];
		M2 = ((float)(nbPix - HC[s - 1]) * M2 - (float)(histo[s] * s)) / (float)(nbPix - HC[s]);
		W1 = (float)HC[s] / (double)(nbPix);
		V[s] = W1 * (1 - W1) * (M1 - M2) * (M1 - M2);
		if (V[s] > V[Otsu])
			Otsu = s;
	}

	return Otsu;
}

#pragma endregion


#pragma region COULEUR
//COULEUR
void affichage(COULEUR color)
{
	printf("%s -> (%d,%d,%d)\n", color.couleur, color.R, color.G, color.B);
}

double distanceEuclidienne(COULEUR color1, COULEUR color2)
{
	double ecart = (double)(color1.R - color2.R) * (color1.R - color2.R);
	double distEucl = ecart;

	ecart = (double)(color1.G - color2.G) * (color1.G - color2.G);
	distEucl += ecart;

	ecart = (double)(color1.B - color2.B) * (color1.B - color2.B);
	distEucl += ecart;

	distEucl = sqrt(distEucl);

	return distEucl;
}

#pragma endregion





#pragma region COMPLEXE
//COMPLEXE

void afficheComplexe(COMPLEXE complexe)
{
	char op = '+';
	if (complexe.Im < 0)
	{
		op = NULL;
	}
	printf("%lf %c%lfi \n", complexe.Re, op, complexe.Im);
}

COMPLEXE lectureComplexe(void)
{
	COMPLEXE complexe;

	printf("Entrer une partie reelle \n");
	scanf("%lf", &complexe.Re);
	printf("Entrer une imaginaire \n");
	scanf("%lf", &complexe.Im);

	return complexe;
}

COMPLEXE conjugueComplexe(COMPLEXE complexe)
{
	COMPLEXE conjuge;
	conjuge.Re = complexe.Re;
	conjuge.Im = -complexe.Im;
	return conjuge;
}

double moduleComplexe(COMPLEXE complexe)
{
	return sqrt(pow(complexe.Re, 2) + pow(complexe.Im, 2));
}

COMPLEXE additionComplexe(COMPLEXE complexe1, COMPLEXE complexe2)
{
	COMPLEXE complexeAdd;
	complexeAdd.Re = complexe1.Re + complexe2.Re;
	complexeAdd.Im = complexe1.Im + complexe2.Im;

	return complexeAdd;
}

COMPLEXE multiplicationComplexe(COMPLEXE complexe1, COMPLEXE complexe2)
{
	COMPLEXE complexeMul;
	complexeMul.Re = (complexe1.Re * complexe2.Re - complexe1.Im * complexe2.Im);
	complexeMul.Im = (complexe1.Re * complexe2.Im + complexe1.Im * complexe2.Re);

	return complexeMul;
}

#pragma endregion

#pragma region POINTEURS

void echangeInt(int* pa, int* pb)
{
	int temp = *pa;
	*pa = *pb;
	*pb = temp;
}

#pragma endregion

#pragma region TEMPS


TEMPS decomposition_TEMPS(int tps)
{
	TEMPS temps;

	temps.Heure = tps / 3600;
	temps.Minutes = (tps % 3600) / 60;
	temps.Secondes = (((tps % 3600) / 60) % 60);

	return temps;
}

void decomposition(int tps, int* h, int* m, int* s)
{
	*h = tps / 3600;
	*m = (tps % 3600) / 60;
	*s = (((tps % 3600) / 60) % 60);
}

void lectureTemps(int* tps)
{

	printf("Entrer votre temps en secondes : \n");
	scanf("%d", &*tps);
}

#pragma endregion

#pragma region TABLEAU_INT
void* AllocTableauInt(TABLEAU_INT tDyn)
{
	tDyn.tabDyn = (int*)calloc(tDyn.size, sizeof(int));
}
#pragma endregion


#pragma region MOTS
//PART 1
char tirageLettre(void)
{
	char letter;
	letter = 'a' + rand() % ('z' + 1 - 'a');

	return letter;
}

char* tirageMot(int taille)
{
	char* mot = NULL;
	mot = (char*)calloc(taille + 1, sizeof(char));

	for (int i = 0; i < taille; i++)
	{
		mot[i] = tirageLettre();
	}

	return mot;
}

char* copieMot(char* mot1, int taille)
{
	char* Motcopie = NULL;
	Motcopie = (char*)calloc(taille + 1, sizeof(char));

	for (int i = 0; i < taille; i++)
	{
		Motcopie[i] = mot1[i];
	}

	return Motcopie;
}

void transformMotMajuscule(char* mot)
{
	mot[0] = mot[0] - 'a' + 'A';
}

void transformMotMinuscule(char* mot)
{
	mot[0] = mot[0] + 'a' - 'A';
}

void multiplicationVoyellesMot(char* mot1, int taille1, int coef, char* mot2, int* taille2)
{
	int nb_voy = 0;
	for (int i = 0; i < taille1; i++)
	{
		if (mot1[i] == 'a' || mot1[i] == 'o' || mot1[i] == 'e' || mot1[i] == 'i' || mot1[i] == 'u' || mot1[i] == 'y')
		{
			nb_voy++;
		}
	}

	*taille2 = taille1 - nb_voy + coef * nb_voy;
	*mot2 = (char*)calloc(taille2 + 1, sizeof(char));

	int w = 0, temp = 0;

	for (int i = 0; i < taille1; i++)
	{
		if (mot1[i] == 'a' || mot1[i] == 'o' || mot1[i] == 'e' || mot1[i] == 'i' || mot1[i] == 'u' || mot1[i] == 'y')
		{
			w = i;
			for (int j = 0; j < coef; j++)
			{
				mot2[w] = mot1[i];
				w++;
			}

		}
		else
		{
			mot2[temp] = mot1[i];
		}
		temp++;
	}
}

//PART 2
MOT generationMot(int n)
{
	MOT mot;
	mot.longueur = n;
	mot.data = (char*)calloc(mot.longueur + 1, sizeof(char));

	for (int i = 0; i < mot.longueur; i++)
	{
		mot.data[i] = tirageLettre();
	}

	return mot;
}

void libereMot(MOT mot)
{
	free(mot.data);
}

MOT* tiragePhrase(int nbMots)
{
	MOT* phrase;


	for (int i = 0; i < nbMots; i++)
	{
		int nb_rand = 1 + rand() % (10 + 1 - 1);

	}
}

//A FINIR

#pragma endregion

#pragma region MATRICE

MATRICE initialisationMatrice(hauteur, largeur, valeur_Min, valeur_Max)
{
	MATRICE matrice;
	matrice.hauteur = hauteur;
	matrice.largeur = largeur;
	matrice.valeurs = NULL;

	matrice.valeurs = (int**)malloc(hauteur * sizeof(int*));

	if (matrice.valeurs == NULL)
		printf("Pb allocation matrice.\n");
	else
	{
		int i;
		for (i = 0; i < hauteur; i++)
			matrice.valeurs[i] = (int*)malloc(largeur * sizeof(int));
		if (matrice.valeurs[i] == NULL)
			printf("Pb allocation ligne %d.", i);
	}

	for (int i = 0; i < hauteur; i++)
	{
		for (int j = 0; j < largeur; j++)
		{
			matrice.valeurs[i][j] = valeur_Min + rand() % (valeur_Max + 1 - valeur_Min);
		}
	}

	return matrice;
}

void liberationMatrice(MATRICE* matrice)
{
	for (int i = 0; i < matrice->hauteur; i++)
		free(matrice->valeurs[i]);
	free(matrice->valeurs);
	matrice->valeurs = NULL;
}

void affichageMatrice(MATRICE matrice)
{
	for (int i = 0; i < matrice.hauteur; i++)
	{
		affichageTableauInt(matrice.valeurs[i], matrice.largeur);
	}
}

int traceMatrice(MATRICE matrice)
{
	int trace = 0;

	if (matrice.hauteur != matrice.largeur)
	{
		return 9999999999999999999;
	}
	else
	{
		for (int i = 0; i < matrice.hauteur; i++)
		{
			trace = trace + matrice.valeurs[i][i];
		}
	}

	return trace;
}

MATRICE additionMatrice(MATRICE matrice1, MATRICE matrice2)
{
	MATRICE matriceAdd = allocationMatrice(matrice1.hauteur, matrice1.largeur);

	if ((matrice1.hauteur != matrice2.hauteur) || (matrice1.largeur != matrice2.largeur))
	{
		return matriceAdd;
	}
	else
	{
		for (int i = 0; i < matrice1.hauteur; i++)
		{
			for (int j = 0; j < matrice1.largeur; j++)
			{
				matriceAdd.valeurs[i][j] = matrice1.valeurs[i][j] + matrice2.valeurs[i][j];
			}
		}
	}

	return matriceAdd;
}

MATRICE allocationMatrice(int hauteur, int largeur)
{
	MATRICE matrice = { hauteur, largeur, NULL };

	matrice.valeurs = (int**)malloc(hauteur * sizeof(int*));

	if (matrice.valeurs == NULL)
		printf("Pb allocation matrice.\n");
	else
	{
		int i;
		for (i = 0; i < hauteur; i++)
			matrice.valeurs[i] = (int*)malloc(largeur * sizeof(int));
		if (matrice.valeurs[i] == NULL)
			printf("Pb allocation ligne %d.", i);
	}

	return matrice;
}

MATRICE multiplicationMatrice(MATRICE matrice1, MATRICE matrice2)
{
	MATRICE matriceMult = allocationMatrice(matrice1.hauteur, matrice1.largeur);

	if (matrice1.largeur != matrice2.hauteur)
	{
		return matriceMult;
	}
	else
	{
		for (int i = 0; i < matrice1.hauteur; i++)
		{
			for (int j = 0; j < matrice1.largeur; j++)
			{
				matriceMult.valeurs[i][j] = 0;
				for (int k = 0; k < matrice1.largeur; k++)
				{
					matriceMult.valeurs[i][j] = matriceMult.valeurs[i][j] + (matrice1.valeurs[i][k] * matrice2.valeurs[k][j]);
				}
			}
		}
	}

	return matriceMult;
}

#pragma endregion


#pragma region iMATRICE
iMATRICE allocation_iMatrice(int hauteur, int largeur)
{
	iMATRICE matrice = { hauteur, largeur, NULL, NULL };
	matrice.valeurs = (int*)malloc(hauteur * largeur * sizeof(int));
	matrice.ptLignes = (int**)malloc(hauteur * sizeof(int*));

	if (matrice.valeurs == NULL)
	{
		printf("Pb allocation valeurs");
	}
	else if (matrice.ptLignes == NULL)
	{
		printf("Pb allocation ptlignes");
	}
	else
	{
		int j = 0;
		for (int i = 0; i < matrice.hauteur; i++)
		{
			matrice.ptLignes[i] = &matrice.valeurs[j];
			j = j + matrice.largeur;
		}
	}

	return matrice;
}

void remplissageAleatoire_iMatrice(iMATRICE matrice, int valeur_Min, int valeur_Max)
{

	for (int i = 0; i < matrice.hauteur * matrice.largeur; i++)
	{
		matrice.valeurs[i] = valeur_Min + rand() % (valeur_Max + 1 - valeur_Min);
	}
}

void affichage_iMatrice(iMATRICE matrice)
{
	for (int i = 0; i < matrice.hauteur; i++)
	{
		for (int j = 0; j < matrice.largeur; j++)
		{

			printf("%d \t ", matrice.valeurs[i * matrice.largeur + j]);
		}
		printf("\n");
	}
}

void liberation_iMatrice(iMATRICE* matrice)
{

	if (matrice->ptLignes != NULL) {
		free(matrice->ptLignes);
		matrice->ptLignes = NULL;
	}
	if (matrice->valeurs != NULL) {
		free(matrice->valeurs);
		matrice->valeurs = NULL;
	}

}
#pragma endregion

#pragma region CONTROLE

int carre(int x)
{
	return(x * x);
}

int fonction1(int T[], int n)
{
	int compteur = 0, j = 0;
	for (int i = 0; i < n; i++)
	{
		if (T[i] != 3)
		{
			T[j] = T[i];
			j = j + 1;
		}
		else
			compteur += 1;
	}
	n -= compteur;

	return n;
}

int minTableauIntViaHisto(int T[], int n)
{
	int indice = 0;

	for (int i = 0; i < n; i++)
	{
		if (T[i] != 0)
		{
			indice = i;
			break;
		}
	}

	return indice;
}
int maxTableauIntViaHisto(int T[], int n)
{
	int indice = 0;

	for (int i = 255; i > 0; i--)
	{
		if (T[i] != 0)
		{
			indice = i;
			break;
		}
	}

	return indice;
}

int trace(int T[], int N)
{
	int trace = 0;
	int indice = 0;

	for (int i = 0; i < N; i++)
	{
		trace = trace + T[indice + i * N];
		indice++;
	}

	return trace;
}

int puissance(int x, int n)
{
	return (pow(x, n));
}

int evalPolynome(int P[], int n, int x)
{
	int res = 0;
	for (int i = n; i >= 0; i--)
	{
		res = res + P[i] * puissance(x, n);
		n--;
	}

	return res;
}

int evalPolynomeV2(int P[], int n, int x)
{
	int res = P[n] * x;

	for (int i = n - 1; i > 0; i--)
	{
		res = res * x + P[i - 1];
	}

	return res;
}

#pragma endregion

#pragma region CONTROLE_DEV_IMAGE

//EX3
TAB_RESISTANCE allocTabResistance(int nb)
{
	TAB_RESISTANCE resistance;
	resistance.nombre = nb;
	resistance.data = (float*)calloc(resistance.nombre, sizeof(float));

	return resistance;
}

float resistanceEquivalente(TAB_RESISTANCE tabres, int type)
{
	float resultat = 0;

	if (type >= 0)
	{
		for (int i = 0; i < tabres.nombre; i++)
		{
			resultat = resultat + tabres.data[i];
		}
	}
	else
	{
		for (int i = 0; i < tabres.nombre; i++)
		{
			resultat = resultat + (1.0 / tabres.data[i]);
		}

		resultat = 1.0 / resultat;
	}

	return resultat;
}

TAB_RESISTANCE lectureData(const char* nom)
{
	TAB_RESISTANCE resistanceDATA;

	FILE* F = NULL;
	F = fopen(nom, "r");
	fscanf(F, "%d", &resistanceDATA.nombre);
	resistanceDATA = allocTabResistance(resistanceDATA.nombre);
	for (int i = 0; i < resistanceDATA.nombre; i++)
	{
		fscanf(F, "%f", &resistanceDATA.data[i]);
	}
	fclose(F);

	return resistanceDATA;
}

void enregistreDATA(const char* nom, TAB_RESISTANCE tabres)
{
	FILE* F = NULL;

	F = fopen(nom, "w");
	for (int i = 0; i < tabres.nombre; i++)
	{
		fprintf(F, "%f ", tabres.data[i]);
	}
	fprintf(F, "\n");
	fprintf(F, "Serie : %f \n", resistanceEquivalente(tabres, 1));
	fprintf(F, "Parallele : %f \n", resistanceEquivalente(tabres, -1));

	fclose(F);
}

// EX4

void regression(POINT* tab, int n, float* a, float* b)
{
	float somme_x, somme_y, somme_x2, somme_xy;
	int i;

	somme_x = 0.;
	somme_y = 0.;
	somme_x2 = 0.;
	somme_xy = 0.;

	for (i = 0; i < n; i++) {
		somme_x += tab[i].abscisse;
		somme_y += tab[i].ordonnee;
		somme_x2 += tab[i].abscisse * tab[i].abscisse;
		somme_xy += (tab[i].abscisse * tab[i].ordonnee);
	}

	*a = (somme_xy - ((somme_x * somme_y) / (float)n)) / (somme_x2 - ((somme_x * somme_x) / (float)n));
	*b = (somme_y - ((*a) * somme_x)) / (float)n;
}

void sortieRegression(const char* nom, POINT* pts, int n)
{
	float a, b;
	regression(pts, n, &a, &b);

	FILE* F;
	F = fopen(nom, "w");
	int i;
	for (i = 0; i < n; i++)
	{
		fprintf(F, "%f ; %f ; %f \n", pts[i].abscisse, pts[i].ordonnee, (a * pts[i].abscisse + b));
	}

	fclose(F);
}

POINT* ImageVersPoints(IMAGE img, int* n, char axe)
{
	POINT* pts = (POINT*)calloc(img.Nbcol * img.Nblig, sizeof(POINT));
	int cmpt = 0;

	if (axe == 'i')
	{
		for (int i = 0; i < img.Nblig; i++)
		{
			for (int j = 0; j < img.Nbcol; j++)
			{
				if (img.pixel[i][j] == 1)
				{
					pts[cmpt].abscisse = i;
					pts[cmpt].ordonnee = j;

					cmpt++;
				}
			}
		}


	}

	if (axe == 'j')
	{
		for (int i = 0; i < img.Nblig; i++)
		{
			for (int j = 0; j < img.Nbcol; j++)
			{
				if (img.pixel[i][j] == 1)
				{
					pts[cmpt].abscisse = j;
					pts[cmpt].ordonnee = i;

					cmpt++;
				}
			}
		}
	}

	*n = cmpt;
	return pts;
}

IMAGE imageSortieRegression(IMAGE img, char axe)
{
	IMAGE imgSortie = img;
	float a, b;
	int n;

	if (axe == 'i')
	{
		POINT* PointI = ImageVersPoints(img, &n, 'i');
		regression(PointI, n, &a, &b);

		for (int i = 0; i < img.Nblig; i++)
		{
			if ((a * i + b) > img.Nbcol)
			{
				break;
			}
			imgSortie.pixel[i][(int)(a * i + b)] = 2;
		}
	}

	if (axe == 'j')
	{

		POINT* PointJ = ImageVersPoints(img, &n, 'j');
		regression(PointJ, n, &a, &b);

		for (int j = 0; j < img.Nbcol; j++)
		{
			if ((a * j + b) > img.Nblig)
			{
				break;
			}
			imgSortie.pixel[(int)(a * j + b)][j] = 2;
		}
	}

	return imgSortie;
}



#pragma endregion