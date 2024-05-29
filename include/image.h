#pragma once

class image
{
	public:
		image();
		image(int Nblig, int Nbcol, unsigned char* data, unsigned char** pixel);
		image(int Nblig, int Nbcol);
		image::~image();

		image allocationImage(int Nblig, int Nbcol);
		void initialisationAleatoireImage(image img, int ngMin, int ngMax);
		static int* histogrammeImage(image img, int choix, int n);
		void sauvegardeImage(image img, const char* type, const char* out);
		void liberationImage(image* img); // Destructeur
		static image lectureImage(const char* nom);
		
		int getNblig();
		int getNbCol();
		unsigned char& getData(int i);
		unsigned char getPixel(int i, int j);
		void setPixel(int i, int j, unsigned char value);

	//private:
		int   Nblig;
		int   Nbcol;
		unsigned char* data;
		unsigned char** pixel;
};

