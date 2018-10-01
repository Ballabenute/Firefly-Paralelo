#include "HSVimg.h"
#include <iostream>

using namespace std;

HSVimg::HSVimg()
{
	Histogram1 = new double[162];
	Histogram2 = new double[162];
	Histogram3 = new double[162];
	Histogram4 = new double[162];
	Histogram5 = new double[162];

	for (int i = 0; i < 162; i++) Histogram1[i] = 0;
	for (int i = 0; i < 162; i++) Histogram2[i] = 0;
	for (int i = 0; i < 162; i++) Histogram3[i] = 0;
	for (int i = 0; i < 162; i++) Histogram4[i] = 0;
	for (int i = 0; i < 162; i++) Histogram5[i] = 0;

	this->Dist = 0;
}

void HSVimg::setImg(IplImage* Img)
{
	this->Img = Img;
}

void HSVimg::setDist(int Dist)
{
	this->Dist = Dist;
}

void HSVimg::setId(int id)
{
	this->id = id;
}

void HSVimg::setLetra(char letra)
{
	this->letra = letra;
}

void HSVimg::setInoutdoor(int intoutdoor)
{
	this->inoutdoor = inoutdoor;
}

void HSVimg::setClasse(int classe)
{
	this->classe = classe;
}

void HSVimg::setName(char* Name)
{
	strcpy(this->name,Name);
}

void HSVimg::setHistogram1(double* tHistogram)
{
	Histogram1 = tHistogram;
}

double* HSVimg::getHistogram1()
{
	return Histogram1;
}

void HSVimg::setHistogram2(double* tHistogram)
{
	Histogram2 = tHistogram;
}

double* HSVimg::getHistogram2()
{
	return Histogram2;
}

void HSVimg::setHistogram3(double* tHistogram)
{
	Histogram3 = tHistogram;
}

double* HSVimg::getHistogram3()
{
	return Histogram3;
}

void HSVimg::setHistogram4(double* tHistogram)
{
	Histogram4 = tHistogram;
}

double* HSVimg::getHistogram4()
{
	return Histogram4;
}

void HSVimg::setHistogram5(double* tHistogram)
{
	Histogram5 = tHistogram;
}

double* HSVimg::getHistogram5()
{
	return Histogram5;
}

char* HSVimg::getName()
{
	return name;
}

float HSVimg::getDist()
{
	return Dist;
}

int HSVimg::getId()
{
	return id;
}

int HSVimg::getInoutdoor()
{
	return inoutdoor;
}

char HSVimg::getLetra()
{
	return letra;
}

int HSVimg::getClasse()
{
	return classe;
}

void HSVimg::setPath(char* Path)
{
	strcpy(this->Path,Path);
}

char* HSVimg::getPath()
{
	return Path;
}

//=====================================//
       //Calcula o Histograma HSV//
double* HSVimg::HistogramCalc(IplImage* img)
{
	int Larg = img->width;
	int Altu = img->height;
	int Lum,h,s,v;
	float H = 0, S = 0, V = 0;
	for (int y = 0; y < Altu; y++){
		for (int x = 0; x < Larg; x++){

            H = ((uchar*)(img->imageData + img->widthStep*y))[x * 3];
			S = ((uchar*)(img->imageData + img->widthStep*y))[x * 3 + 1];
			V = ((uchar*)(img->imageData + img->widthStep*y))[x * 3 + 2];
			H = H / 255 * 17;
			S = S / 255 * 2;
			V = V / 255 * 2;
			Lum = (H*9 + S*3 + V);
            this->Histogram1[Lum]++;
		}
	}

	for (int i = 0; i < 162; i++){
		this->Histogram1[i] = this->Histogram1[i] / (Larg*Altu);
	}

    return this->Histogram1;
}

//==========================//
      //Matching Global//
void HSVimg::MathingGlobal(HSVimg query)
{
	double *h1,*h2,*h3,*h4,*h5,*f1,*f2,*f3,*f4,*f5;
	h1 = query.getHistogram1();
	h2 = query.getHistogram2();
	h3 = query.getHistogram3();
	h4 = query.getHistogram4();
	h5 = query.getHistogram5();
	f1 = query.getfeatures1();
	f2 = query.getfeatures2();
	f3 = query.getfeatures3();
	f4 = query.getfeatures4();
	f5 = query.getfeatures5();
float SomaQuad1=0;
	for (int i = 0; i < 162; i++){
		SomaQuad1 = SomaQuad1 + pow((h1[i] - Histogram1[i]), 2);
	}
	float d1=0;
	d1=sqrt(SomaQuad1);
	this->Dist = (SomaQuad1);
}

//===========================//
        //Matching//
void HSVimg::Matching(HSVimg query)
{
	double *h1,*h2,*h3,*h4,*h5,*f1,*f2,*f3,*f4,*f5;
	h1 = query.getHistogram1();
	h2 = query.getHistogram2();
	h3 = query.getHistogram3();
	h4 = query.getHistogram4();
	h5 = query.getHistogram5();
	f1 = query.getfeatures1();
	f2 = query.getfeatures2();
	f3 = query.getfeatures3();
	f4 = query.getfeatures4();
	f5 = query.getfeatures5();

	float SomaQuad1 = 0,SomaQuad2 = 0,SomaQuad3 = 0,SomaQuad4 = 0,SomaQuad5 = 0,Sumf1 = 0,Sumf2 = 0,Sumf3 = 0,Sumf4 = 0,Sumf5 = 0;

	for (int i = 0; i < 162; i++){
		SomaQuad1 = SomaQuad1 + pow((h1[i] - Histogram1[i]), 2);
		SomaQuad2 = SomaQuad2 + pow((h2[i] - Histogram2[i]), 2);
		SomaQuad3 = SomaQuad3 + pow((h3[i] - Histogram3[i]), 2);
		SomaQuad4 = SomaQuad4 + pow((h4[i] - Histogram4[i]), 2);
		SomaQuad5 = SomaQuad5 + pow((h5[i] - Histogram5[i]), 2);
	}

	for(int j=0;j<5;j++){
		Sumf1 = Sumf1 + pow((f1[4] - features1[4]),2);
		Sumf2 = Sumf2 + pow((f2[4] - features2[4]),2);
		Sumf3 = Sumf3 + pow((f3[4] - features3[4]),2);
		Sumf4 = Sumf4 + pow((f4[4] - features4[4]),2);
		Sumf5 = Sumf5 + pow((f5[4] - features5[4]),2);
	}

	float d1=0,d2=0,d3=0,d4=0,d5=0,df1=0,df2=0,df3=0,df4=0,df5=0;

	d1=sqrt(SomaQuad1);
	d2=sqrt(SomaQuad2);
	d3=sqrt(SomaQuad3);
	d4=sqrt(SomaQuad4);
	d5=sqrt(SomaQuad5);
	df1=sqrt(Sumf1);
	df2=sqrt(Sumf2);
	df3=sqrt(Sumf3);
	df4=sqrt(Sumf4);
	df5=sqrt(Sumf5);

	this->Dist = (d1+d2+d3+d4+d5+df1+df2+df3+df4+df5);
}
//=============================//
      //Setting Features//
void HSVimg::setfeatures1(double f1,double f2,double f3,double f4,double f5)
{
	features1[0] = f1;
	features1[1] = f2;
	features1[2] = f3;
	features1[3] = f4;
	features1[4] = f5;
}

void HSVimg::setfeatures2(double f1,double f2,double f3,double f4,double f5)
{
	features2[0] = f1;
	features2[1] = f2;
	features2[2] = f3;
	features2[3] = f4;
	features2[4] = f5;
}

void HSVimg::setfeatures3(double f1,double f2,double f3,double f4,double f5)
{
	features3[0] = f1;
	features3[1] = f2;
	features3[2] = f3;
	features3[3] = f4;
	features3[4] = f5;
}

void HSVimg::setfeatures4(double f1,double f2,double f3,double f4,double f5)
{
	features4[0] = f1;
	features4[1] = f2;
	features4[2] = f3;
	features4[3] = f4;
	features4[4] = f5;
}

void HSVimg::setfeatures5(double f1,double f2,double f3,double f4,double f5)
{
	features5[0] = f1;
	features5[1] = f2;
	features5[2] = f3;
	features5[3] = f4;
	features5[4] = f5;
}
//=================================//
      //Getting Features//

double* HSVimg::getfeatures1()
{
	return features1;
}

double* HSVimg::getfeatures2()
{
	return features2;
}

double* HSVimg::getfeatures3()
{
	return features3;
}

double* HSVimg::getfeatures4()
{
	return features4;
}

double* HSVimg::getfeatures5()
{
	return features5;
}

//===============================//


bool HSVimg::operator>(HSVimg Test)
{
	if (Dist > Test.getDist())return true;
	else return false;
}

bool HSVimg::operator<(HSVimg Test)
{
	if (Dist < Test.getDist())return true;
	else return false;
}

//================================//
IplImage* HSVimg::getImg()
{
	return Img;
}
