#include <iostream>
#include <cstdlib>
using namespace std;


typedef void (*traceCallback)(int, int);

void traceLine(int x1, int y1, int x2, int y2, traceCallback drawPixel) {
	int dx = x2 - x1;
	cout << "dx = " << dx << endl;
	int dy;

	if (dx != 0) {
		if (dx > 0) {
			dy = y2 - y1;
			cout << "dx>0 dy = " << dy << endl;
			if (dy != 0) {
				if (dy > 0) {
					// vecteur oblique dans le 1er quadran
					if (dx >= dy) {
						// vecteur diagonal ou oblique proche de l’horizontale, dans le 1er octant
						int e = dx;
						dx = e * 2;
						dy = dy * 2;
						// e est positif
						for (;;) {
							drawPixel(x1, y1);
							++x1;
							if (x1 == x2) {
								break;
							}
							e -= dy;
							if (e < 0) {
								++y1; // déplacement diagonal
								e += dx;
							}
						}
					}
					else {
						// vecteur oblique proche de la verticale, dans le 2d octant
						int e = dy;
						dy = e * 2;
						dx = dx * 2;
						// e est positif
						for (;;) {  // déplacements verticaux
							drawPixel(x1, y1);
							++y1;
							if (y1 == y2) {
								break;
							}
							e -= dx;
							if (e < 0) {
								++x1;  // déplacement diagonal
								e += dy;
							}
						}
					}
				}
				else {// dy < 0 (et dx > 0)
					cout << "dy<0" << endl;
					// vecteur oblique dans le 4e cadran
					if (dx >= -dy) {
						// vecteur diagonal ou oblique proche de l’horizontale, dans le 8e octant
						int e = dx;
						dx = e * 2;
						dy = dy * 2;
						// e est positif
						for (;;) {  // déplacements horizontaux
							drawPixel(x1, y1);
							++x1;
							if (x1 == x2) {
								break;
							}
							e = e + dy;

							if (e < 0) {
								--y1;  // déplacement diagonal
								e = e + dx;
							}
						}
					}
					else {
						cout << "dx<-dy" << endl;
						// vecteur oblique proche de la verticale, dans le 7e octant
						int e = dy;
						dy = e * 2;
						dx = dx * 2;  // e est négatif
						for (;;) {  // déplacements verticaux
							drawPixel(x1, y1);
							--y1;
							if (y1 == y2) {
								break;
							}
							e += dx;
							if (e > 0) {
								++x1;  // déplacement diagonal
								e += dy;
							}
						}
					}
				}
			}
			else {  // dy = 0 (et dx > 0)
			   // vecteur horizontal vers la droite
				cout << "droite" << endl;
				do {
					drawPixel(x1, y1);
					++x1;
				} while (x1 != x2);
			}
		}
		else { // dx < 0
			dy = y2 - y1;
			if (dy != 0) {
				if (dy > 0) {
					// vecteur oblique dans le 2d quadran
					if (-dx >= dy) {
						// vecteur diagonal ou oblique proche de l’horizontale, dans le 4e octant
						int e = dx;
						dx = e * 2;
						dy = dy * 2;
						// e est négatif
						for (;;) { // déplacements horizontaux
							drawPixel(x1, y1);
							--x1;
							if (x1 == x2) {
								break;
							}
							e += dy;
							if (e >= 0) {
								++y1;  // déplacement diagonal
								e += dx;
							}
						}
					}
					else {
						// vecteur oblique proche de la verticale, dans le 3e octant
						int e = dy;
						dy = e * 2;
						dx = dx * 2;
						// e est positif
						for (;;) {  // déplacements verticaux
							drawPixel(x1, y1);
							++y1;
							if (y1 == y2) {
								break;
							}
							e += dx;
							if (e <= 0) {
								--x1;  // déplacement diagonal
								e += dy;
							}
						}
					}
				}
				else {  // dy < 0 (et dx < 0)
				   // vecteur oblique dans le 3e cadran
					if (dx <= dy) {
						// vecteur diagonal ou oblique proche de l’horizontale, dans le 5e octant
						int e = dx;
						dx = e * 2;
						dy = dy * 2;
						// e est négatif
						for (;;) {  // déplacements horizontaux
							drawPixel(x1, y1);
							--x1;
							if (x1 == x2) {
								break;
							}
							e -= dy;
							if (e >= 0) {
								--y1;  // déplacement diagonal
								e += dx;
							}
						}
					}
					else {  // vecteur oblique proche de la verticale, dans le 6e octant
						int e = dy;
						dy = e * 2;
						dx = dx * 2;
						// e est négatif
						for (;;) { // déplacements verticaux
							drawPixel(x1, y1);
							--y1;
							if (y1 == y2) {
								break;
							}
							e -= dx;
							if (e >= 0) {
								--x1;  // déplacement diagonal
								e += dy;
							}
						}
					}
				}
			}
			else {  // dy = 0 (et dx < 0)
			   // vecteur horizontal vers la gauche
				do {
					drawPixel(x1, y1);
					--x1;
				} while (x1 != x2);
			}
		}
	}
	else {
		// dx = 0
		dy = y2 - y1;
		cout << "dx=0 dy=" << dy << endl;
		if (dy != 0) {
			if (dy > 0) {
				// vecteur vertical croissant
				do {
					drawPixel(x1, y1);
					++y1;
				} while (y1 != y2);
			}
			else { // dy < 0 (et dx = 0)
				cout << "haut" << endl;
				// vecteur vertical décroissant
				do {
					drawPixel(x1, y1);
					--y1;
				} while (y1 != y2);
			}
		}
	}
	// le pixel final (x2, y2) n’est pas tracé.
}

const int sizeX(21);
const int sizeY(21);

char tab[sizeX][sizeY];

void draw(int x, int y) {
	tab[x][y] = '#';
}

int main(void) {


	int x1 = 0;
	int y1 = 20;
	int x2 = 30;
	int y2 = 30;

	for (int x(0); x < sizeX; ++x) {
		for (int y(0); y < sizeY; ++y) {
			tab[x][y] = '.';
		}
	}

	traceLine(x1, y1, x2, y2, draw);

	for (int y(0); y < sizeY; ++y) {
		for (int x(0); x < sizeX; ++x) {
			cout << tab[x][y];
		}
		cout << endl;
	}
	return 0;
};