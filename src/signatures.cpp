#include "signatures.h"
#include "image.h"
#include <math.h>

signatures signatures::statistiquesImage(image img)
{
	signatures sig;
	int i;
	double som = 0, som2 = 0;
	int somme, moitPop = (img.getNbCol() * img.getNblig()) / 2;
	int* h = image::histogrammeImage(img, 0, 256);

	for (i = 0; i < img.getNbCol() * img.getNblig(); i++) {
		som += (double)img.data[i];
		som2 += (double)img.data[i] * (double)img.data[i];
	}

	som /= (double)(img.getNblig() * img.getNbCol());
	som2 = sqrt(som2 / (double)(img.getNblig() * img.getNbCol()) - som * som);

	sig.moyenne = som;
	sig.ecartType = som2;

	i = 0;
	while (h[i] == 0)
		i += 1;
	sig.min = i;

	i = 255;
	while (h[i] == 0)
		i -= 1;
	sig.max = i;

	i = 0;
	somme = h[i];
	while (somme < moitPop) {
		i += 1;
		if (i < 256)
			somme += h[i];
	}
	sig.mediane = i;

	delete h;
	h = NULL;

	return sig;
}