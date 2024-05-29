#pragma once

class intImage
{
	public:
		intImage(); 
		intImage(int Nblig, int Nbcol); 
		~intImage();

		void liberationIntImage(intImage* img);
		intImage allocationIntImage(int Nblig, int Nbcol);

		int getNblig() const;
		int getNbcol() const;
		int* getData() const;
		int getPixel(int i, int j) const;
		void setPixel(int i, int j, unsigned char value);

	private:
		int Nblig;
		int Nbcol;
		int* data;
		int** pixel;
};