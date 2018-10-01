#ifndef HSVA
#define HSVA

#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP

#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"
//include "opencv2/core/types_c.h"

#include "HSVimg.h"
#include "firefly.h"
#include "histogram.h"
#include "entropy.h"
#include "lde.hpp"

using namespace std;
using namespace cv;
using namespace fei;

class hsvL{
private:

    double* hsv;
    double features[5];
    int total;

public:

    hsvL()
    {
        this->total = 0;hsv = NULL;
    }

    double* gethsv()
    {
        return hsv;
    }

    int gettotal()
    {
        return total;
    }

    void sethsv(double* hsv)
    {
        this->hsv = hsv;
    }

    void setfeatures(double m,double m2,double m3,double r,double s)
    {
        features[0] = m;features[1] = m2;features[2] = m3;features[3] = r;features[4] = s;
    }


    double* getfeatures()
    {
        return features;
    }


    void settotal(int total)
    {
        this->total = total;
    }


    bool operator>(hsvL test)
    {
        if(this->total > test.gettotal())return true;
        else return false;
    }


    bool operator<(hsvL test)
    {
        if(this->total < test.gettotal())return true;
        else return false;
    }
};

bool dsgcalcHistogramsWithMasks(HSVimg*,int);

void dsgHistogransReader(HSVimg* DB,HSVimg* DBq);

void dsgImgmatching(HSVimg*, HSVimg);

void dsgBubbleSort(HSVimg*);

void dsgReadIds(int* inoutd,HSVimg* DB,HSVimg* DBq);

void dsgReadIds(int* inoutd,HSVimg* DB);

void dsgReadClassQ(int*);

double* pra(int*, int, int*);

void dsgReadClasses(HSVimg*,HSVimg* DBq);

void dsgPRASaver(int id,double praatual);

void dsgfeaturesSaver(HSVimg* feito482,int id);

void geraPath(char* Path,int id);

int partition(HSVimg* DB_img, int ini, int fim);

void dsgQuickSort(HSVimg* DB_img,int ini,int fim);

void validaimgs(HSVimg* db_img);

void validahistograms(HSVimg* DB);

void geraClassquant();

void dsgReadFeatures(HSVimg* DB, HSVimg* DBq);

void dsgHistogranSaver(HSVimg DB); // Salva Histograma em uma file TXT



void dsgHistogranSaver(HSVimg DB)
{
    double* h = DB.getHistogram1();
        FILE* f = fopen("/home/daniel/Projetos/FEI/ic-fei/features/hsvGlobal.txt","a");
        for(int i=0;i<162;i++){
            fprintf(f,"%f ",h[i]);
        }
        fprintf(f,"\n");
        fclose(f);
}

void geraClassquant(){
    FILE* f = fopen("/home/daniel/Projetos/FEI/ic-fei/control/classesabsolutas.txt","r");
    int cq[1076];
    int aux=0;
    for(int j=0;j<1076;j++){
        cq[j]=0;
    }
    for(int i=0;i<16870;i++){
        fscanf(f,"%d",&aux);
        cq[aux] = cq[aux] + 1;
    }
    fclose(f);
    FILE* clq = fopen("/home/daniel/Projetos/FEI/ic-fei/control/quantclasses.txt","a");
    for(int k=1;k<1076;k++){
        fprintf(clq,"%d\n",cq[k]);
    }
}

void validahistograms(HSVimg* DB)
{
    double *h1,*h2,*h3,*h4,*h5;
    int sum =0;
    FILE* log1 = fopen("/home/daniel/Projetos/FEI/ic-fei/logs/loghistogram.txt","a");
    double s1=0,s2=0,s3=0,s4=0,s5=0;
    for(int i=0;i<16870;i++){
        h1 = DB[i].getHistogram1();
        h2 = DB[i].getHistogram2();
        h3 = DB[i].getHistogram3();
        h4 = DB[i].getHistogram4();
        h5 = DB[i].getHistogram5();
        for(int j=0;j<162;j++){
            s1 = s1 + h1[j];
            s2 = s2 + h2[j];
            s3 = s3 + h3[j];
            s4 = s4 + h4[j];
            s5 = s5 + h5[j];
        }
        if(s1 < 0.9 || s1 > 1.1){
            cout<<i<<"s1 "<<s1<<endl;
            sum++;
        }
        if(s2 < 0.9 || s2 > 1.1){
            sum++;
            cout<<i<<"s2 "<<s2<<endl;
        }
        if(s3 < 0.9 || s3 > 1.1){
            cout<<i<<"s3 "<<s3<<endl;
            sum++;
        }
        if(s4 < 0.9 || s4 > 1.1){
            cout<<i<<"s4 "<<s4<<endl;
            sum++;
        }
        if(s5 < 0.9 || s5 > 1.1){
            cout<<i<<"s5 "<<s5<<endl;
            sum++;
        }
        s1=0;
        s2=0;
        s3=0;
        s4=0;
        s5=0;
    }
    cout<<sum<<endl;
}

void geraPath(char* Path,int id)
{
    char idstr[10];
    sprintf(idstr,"%d",id);
    strcpy(Path,"/home/daniel/Projetos/FEI/ic-fei/imseg-PS-2L/imseg2L");
    strcat(Path,idstr);
    strcat(Path,".png");
}

void dsgfeaturesSaver(HSVimg* feito482,int id)
{
        FILE* histogram1 = fopen("/home/daniel/Projetos/FEI/ic-fei/features/histogram1.txt","a");
        FILE* histogram2 = fopen("/home/daniel/Projetos/FEI/ic-fei/features/histogram2.txt","a");
        FILE* histogram3 = fopen("/home/daniel/Projetos/FEI/ic-fei/features/histogram3.txt","a");
        FILE* histogram4 = fopen("/home/daniel/Projetos/FEI/ic-fei/features/histogram4.txt","a");
        FILE* histogram5 = fopen("/home/daniel/Projetos/FEI/ic-fei/features/histogram5.txt","a");
        FILE* features1 = fopen("/home/daniel/Projetos/FEI/ic-fei/features/features1.txt","a");
        FILE* features2 = fopen("/home/daniel/Projetos/FEI/ic-fei/features/features2.txt","a");
        FILE* features3 = fopen("/home/daniel/Projetos/FEI/ic-fei/features/features3.txt","a");
        FILE* features4 = fopen("/home/daniel/Projetos/FEI/ic-fei/features/features4.txt","a");
        FILE* features5 = fopen("/home/daniel/Projetos/FEI/ic-fei/features/features5.txt","a");

        double* h1;
        double* h2;
        double* h3;
        double* h4;
        double* h5;
        double* f1;
        double* f2;
        double* f3;
        double* f4;
        double* f5;

        //for(int i=0;i<482;i++){
            h1 = feito482[id].getHistogram1();
            h2 = feito482[id].getHistogram2();
            h3 = feito482[id].getHistogram3();
            h4 = feito482[id].getHistogram4();
            h5 = feito482[id].getHistogram5();
            for(int j=0;j<162;j++){
                fprintf(histogram1,"%f ",h1[j]);
                fprintf(histogram2,"%f ",h2[j]);
                fprintf(histogram3,"%f ",h3[j]);
                fprintf(histogram4,"%f ",h4[j]);
                fprintf(histogram5,"%f ",h5[j]);
            }
            fprintf(histogram1,"\n");
            fprintf(histogram2,"\n");
            fprintf(histogram3,"\n");
            fprintf(histogram4,"\n");
            fprintf(histogram5,"\n");

            f1 = feito482[id].getfeatures1();
            f2 = feito482[id].getfeatures2();
            f3 = feito482[id].getfeatures3();
            f4 = feito482[id].getfeatures4();
            f5 = feito482[id].getfeatures5();
            for(int k =0;k<5;k++){
                fprintf(features1,"%f ",f1[k]);
                fprintf(features2,"%f ",f2[k]);
                fprintf(features3,"%f ",f3[k]);
                fprintf(features4,"%f ",f4[k]);
                fprintf(features5,"%f ",f5[k]);
            }
            fprintf(features1,"\n");
            fprintf(features2,"\n");
            fprintf(features3,"\n");
            fprintf(features4,"\n");
            fprintf(features5,"\n");
    //	}
        fclose(histogram1);
        fclose(histogram2);
        fclose(histogram3);
        fclose(histogram4);
        fclose(histogram5);
        fclose(features1);
        fclose(features2);
        fclose(features3);
        fclose(features4);
        fclose(features5);
}

//Salva as PRAs
void dsgPRASaver(int id,double praatual)
{
        FILE* pras = fopen("/home/daniel/Projetos/FEI/ic-fei/results/PRAjHSV+C1.txt","a");
        //for(int i = 0;i < 482; i++){
            //fprintf(pras,"%f\n",PRAs[i]);
        //}
        fprintf(pras,"%f\n",praatual);
        fclose(pras);/*
        FILE* logs = fopen("logPraSaver45.txt","a");
        fprintf(logs,"%d %d %d\n",id,idSaver,forecast);
        fclose(logs);
        for(int i=0;i<482;i++)PRAs[i]=0;*/

}

//Calcula as PRAs
double* pra(int* classes,int cqimg,int* classesQ)
{
    int quant = classesQ[cqimg-1];//descobre a quantidade de imagens dentro de uma classe


    //zera a matriz
    double RR[2][quant];
    for(int i=0;i<2;i++){
        for(int j=0;j<quant;j++){
            RR[i][j]=0;
        }
    }

    int xi=0,yi=0;
    //descobre a posição que as imagens da classe apareceram no ranking
  for(int i=0;i<16870;i++){
    yi++;
    if(classes[i]==cqimg){
      xi++;
        RR[0][xi]= xi;
        RR[1][xi]= yi;
            cout<<xi<<" || "<<yi<<endl;
    }


    if(xi==quant){

      break;}
  }
    getchar();
  int x = 0;
    x = RR[0][quant];
    //determina precisao (sem a multiplicação)

  double *r;
    r = new double;
    *r =(1.0/quant);

  double Precisao[x+1];
  for(int i=x;i>=1;i--){
    Precisao[i] =(double) i/RR[1][i];
        //Precisao[i] = Precisao[i]*(*r);
        cout<<Precisao[i]<<endl;
    }

    double  *soma;
    soma = new double;
    *soma = 0;
    Precisao[0]=0;
    //calcula a area
    for(int i=0;i<=x;i++){
    (*soma) = (double)(*soma) + Precisao[i];
  }
    (*soma)=(*soma)*(*r);
    //delete r;
    //cout<<*soma<<endl;
  return soma;
}

void dsgReadClasses(HSVimg* DB,HSVimg* DBq)
{
        FILE* clas = fopen("C:/Users/unifgoliveira/Documents/classes.txt","r");
        int valor;
        for(int i=0;i<16870;i++){
            fscanf(clas,"%d",&valor);
            DB[i].setClasse(valor);
            DBq[i].setClasse(valor);
        }
        fclose(clas);
}

void dsgReadClassQ(int* classesQ)
{
    FILE* classq = fopen("C:/Users/unifgoliveira/Documents/classesq.txt","r");
    int valor;
    for(int i=0;i<1076;i++){
        fscanf(classq,"%d",&valor);
        classesQ[i]=valor;
    }
    fclose(classq);
}

void dsgImgmatching(HSVimg* DB_Img, HSVimg QImg)
{
    for (int i = 0; i < 16870; i++){
        DB_Img[i].Matching(QImg);
    }
}

void dsgBubbleSort(HSVimg* DB_img)
{
    int i, j;
    HSVimg aux;
    int k = 16870-1;

    for (i = 0; i < 16870; i++){
        for (j = 0; j < k; j++){
            if (DB_img[j] > DB_img[j + 1]){
                aux = DB_img[j];
                DB_img[j] = DB_img[j + 1];
                DB_img[j + 1] = aux;
            }
        }
        k--;
    }
}

int partition(HSVimg* DB_img, int ini, int fim)
{
    HSVimg x = DB_img[fim];
    int j = ini - 1;
    for (int i = ini; i < fim; i++) {

        if (x.getDist() >= DB_img[i].getDist()) {
            j = j + 1;
            HSVimg temp = DB_img[j];
            DB_img[j] = DB_img[i];
            DB_img[i] = temp;
        }
    }
    DB_img[fim] = DB_img[j + 1];
    DB_img[j + 1] = x;

    return (j + 1);
}

void dsgQuickSort(HSVimg* DB_img,int ini,int fim)// quick sort recursivo
{
    if (ini < fim) {
        int q = partition(DB_img, ini, fim);
        dsgQuickSort(DB_img, ini, q - 1);
        dsgQuickSort(DB_img, q + 1, fim);
    }
}

void dsgHistogransReader(HSVimg* DB, HSVimg* DBq)
{
  double *hAtual1,*hAtual2,*hAtual3,*hAtual4,*hAtual5;
  long double valor;
  FILE* arq1 = fopen("C:/Users/unifgoliveira/Documents/histograms1.txt","r");
  FILE* arq2 = fopen("C:/Users/unifgoliveira/Documents/histograms2.txt","r");
  FILE* arq3 = fopen("C:/Users/unifgoliveira/Documents/histograms3.txt","r");
  FILE* arq4 = fopen("C:/Users/unifgoliveira/Documents/histograms4.txt","r");
  FILE* arq5 = fopen("C:/Users/unifgoliveira/Documents/histograms5.txt","r");
  for(int i = 0;i<16870;i++){
    hAtual1 =  new double[162];
    hAtual2 =  new double[162];
    hAtual3 =  new double[162];
    hAtual4 =  new double[162];
    hAtual5 =  new double[162];
    for(int y=0;y<162;y++){
      fscanf(arq1,"%Lf",&valor);
      hAtual1[y] = valor;
    }
    for(int y=0;y<162;y++){
      fscanf(arq2,"%Lf",&valor);
      hAtual2[y] = valor;
    }
    for(int y=0;y<162;y++){
      fscanf(arq3,"%Lf",&valor);
      hAtual3[y] = valor;
    }
    for(int y=0;y<162;y++){
      fscanf(arq4,"%Lf",&valor);
      hAtual4[y] = valor;
    }
    for(int y=0;y<162;y++){
      fscanf(arq5,"%Lf",&valor);
      hAtual5[y] = valor;
    }
    DB[i].setHistogram1(hAtual1);
    DB[i].setHistogram2(hAtual2);
    DB[i].setHistogram3(hAtual3);
    DB[i].setHistogram4(hAtual4);
    DB[i].setHistogram5(hAtual5);
    DBq[i].setHistogram1(hAtual1);
    DBq[i].setHistogram2(hAtual2);
    DBq[i].setHistogram3(hAtual3);
    DBq[i].setHistogram4(hAtual4);
    DBq[i].setHistogram5(hAtual5);
  }
  fclose(arq1);
  fclose(arq2);
  fclose(arq3);
  fclose(arq4);
  fclose(arq5);
}

void dsgReadFeatures(HSVimg* DB, HSVimg* DBq)
{
    FILE* f1 = fopen("/home/daniel/Projetos/FEI/ic-fei/features/features1.txt","r");
    FILE* f2 = fopen("/home/daniel/Projetos/FEI/ic-fei/features/features2.txt","r");
    FILE* f3 = fopen("/home/daniel/Projetos/FEI/ic-fei/features/features3.txt","r");
    FILE* f4 = fopen("/home/daniel/Projetos/FEI/ic-fei/features/features4.txt","r");
    FILE* f5 = fopen("/home/daniel/Projetos/FEI/ic-fei/features/features5.txt","r");
    long double valor;
    double features[5];

    for(int i=0;i<16870;i++){

        for(int j=0;j<5;j++){
            fscanf(f1,"%Lf",&valor);
            features[j] = valor;
        }
        DB[i].setfeatures1(features[0],features[1],features[2],features[3],features[4]);
        DBq[i].setfeatures1(features[0],features[1],features[2],features[3],features[4]);

        for(int j=0;j<5;j++){
            fscanf(f2,"%Lf",&valor);
            features[j] = valor;
        }
        DB[i].setfeatures2(features[0],features[1],features[2],features[3],features[4]);
        DBq[i].setfeatures2(features[0],features[1],features[2],features[3],features[4]);

        for(int j=0;j<5;j++){
            fscanf(f3,"%Lf",&valor);
            features[j] = valor;
        }
        DB[i].setfeatures3(features[0],features[1],features[2],features[3],features[4]);
        DBq[i].setfeatures3(features[0],features[1],features[2],features[3],features[4]);

        for(int j=0;j<5;j++){
            fscanf(f4,"%Lf",&valor);
            features[j] = valor;
        }
        DB[i].setfeatures4(features[0],features[1],features[2],features[3],features[4]);
        DBq[i].setfeatures4(features[0],features[1],features[2],features[3],features[4]);

        for(int j=0;j<5;j++){
            fscanf(f5,"%Lf",&valor);
            features[j] = valor;
        }
        DB[i].setfeatures5(features[0],features[1],features[2],features[3],features[4]);
        DBq[i].setfeatures5(features[0],features[1],features[2],features[3],features[4]);

    }
}

void dsgReadIds(int* inoutd,HSVimg* DB,HSVimg* DBq)
{
    int inout,id;
    char letter;
    char Class[256];
    char name[256];
    FILE* ids = fopen("C:/Users/unifgoliveira/Documents/caminhosabsolutos.txt","r");
    for(int i=0;i<16870;i++){
        fscanf(ids,"%s",name);
        DB[i].setPath(name);
        DB[i].setInoutdoor(inout);
        DBq[i].setPath(name);
        DBq[i].setInoutdoor(inout);
        inoutd[i] = inout;
    }
}

void dsgReadIds(int* inoutd,HSVimg* DB) // Sobrecarga de dsgReadIds
{
    int inout,id;
    char letter;
    char Class[256];
    char name[256];
    FILE* ids = fopen("C:/Users/unifgoliveira/Documents/caminhosabsolutos.txt","r");
    for(int i=0;i<16870;i++){
        fscanf(ids,"%s",name);
        DB[i].setPath(name);
        DB[i].setInoutdoor(inout);
        inoutd[i] = inout;
    }
}
//começo da segmentação e recuperação de caracteristicas////////////////////////////////////

void  dsgGetRegionFromGrayImage(Mat img, Mat* dst, int Limiari,int Limiarf)
{
    int Lar = img.cols;
    int Alt = img.rows;
    int x,y,Lum;

    for (y=0; y < Alt; y++)
    for (x=0; x < Lar; x++)
    {
      Lum = img.at<uchar>(y, x);
      if (Lum == Limiari && Lum <= Limiarf){
            dst->at<uchar>(y, x) = 255;
      }
    }
}

void dsgGetFeatureMask(Mat msk, Mat imghsv, Mat imggray, int total,hsvL* hsvlt)
{
    int Lar = imghsv.cols;
    int Alt = imghsv.rows;
    int x,y, Lm,Lum,Lumi;
    double T = 0.0;
    double H = 0.0, S = 0.0, V = 0.0;
    double med = 0.0, m2 = 0.0, m3 = 0.0, r = 0.0, s = 0.0;

    double grayH[255];
    double* hsvH = new double[162];

    for(int i=0;i<162;i++) hsvH[i] = 0.0;
    for(int j=0;j<255;j++) grayH[j]= 0.0;

    for (y=0; y < Alt; y++)
    {
        for (x=0; x < Lar; x++)
        {
            Lm = msk.at<uchar>(y, x);

            if (Lm)
            {
                Lum = imggray.at<uchar>(y, x);
                grayH[Lum] = grayH[Lum] + 1;

                Vec3b hsv  = imghsv.at<Vec3b>(y,x);
                H = hsv.val[0];
                S = hsv.val[1];
                V = hsv.val[2];
                H = H / 255 * 17;
                S = S / 255 * 2;
                V = V / 255 * 2;
                Lumi = (H*9 + S*3 + V);
                hsvH[Lumi] = hsvH[Lumi] + 1;
                T=T+1;
            }
        }
    }

    for (int i = 0; i < 255; i++){
        grayH[i] = grayH[i] /T;
    }
    for(int j=0;j<162;j++){
        hsvH[j] = hsvH[j]/T;

    }

    for(int i=0;i<255;i++)med = med + (i*grayH[i]);
    for(int i=0;i<255;i++){
        m2 = m2 + (pow((i-med),2) * grayH[i]);
        m3 = m3 + (pow((i-med),3) * grayH[i]);
    }
    for(int i=0;i<255;i++){
        if(grayH[i] != 0){
            s = s + (log2(grayH[i]) * grayH[i]);
        }
    }
    s = s *(-1);
    r = 1 - (1/(1+m2));

    hsvlt->setfeatures(med,m2,m3,r,s);
    hsvlt->sethsv(hsvH);
}

void dsgGetAllContours(Mat dst, Mat img, Lde<hsvL>* hsvList)
{
  Mat dst3C(dst.rows, dst.cols, CV_8UC3);
    Mat msks[5];
    hsvL* HSVfeatures;
    int contourt[5];

    for(int i=0;i<5;i++){
     contourt[i]=0;
     msks[i] = Mat::zeros(dst.rows, dst.cols, CV_8UC1);
    }

    vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  findContours( dst, contours, hierarchy,CV_RETR_TREE, CV_CHAIN_APPROX_NONE );

  int aux=0,x=INT_MAX;
    int idx = 0;
    int quant=0;

    Scalar color( 255,255,255 );
    if(hierarchy.size() == 0) return;
    for( ; idx >= 0; idx = hierarchy[idx][0])
    {
        if(&contours[idx] != NULL){
            quant = contours[idx].size();

            if(quant == 1) continue;
            if(aux<5){
                contourt[aux]=contours[idx].size();
                dst3C.setTo(cv::Scalar::all(0));
                drawContours( dst3C, contours, idx, color, CV_FILLED, 8, hierarchy );
                cvtColor(dst3C,msks[aux],CV_RGB2GRAY);
            }else{
                for(int i=0;i<5;i++){
                    if(contourt[i] < x) x = contourt[i];
                }
                if(x < contours[idx].size()){
                    for(int j=0;j<5;j++){
                        if(contourt[j] == x){
                            contourt[j] = contours[idx].size();
                            dst3C.setTo(cv::Scalar::all(0));
                            drawContours( dst3C, contours, idx, color, CV_FILLED, 8, hierarchy );
                            cvtColor(dst3C,msks[j],CV_RGB2GRAY);
                            break;
                        }
                    }
                }
            }
        aux++;
            x=INT_MAX;
        }
    }

    Mat imghsv(img.rows, img.cols, CV_8UC3);
    Mat imggray(img.rows, img.cols, CV_8UC1);

    cvtColor(img, imghsv, CV_BGR2HSV);
    cvtColor(img, imggray, CV_BGR2GRAY);

    for(int i=0;i<5;i++){
        if(contourt[i] != 0){
            HSVfeatures = new hsvL;
            dsgGetFeatureMask(msks[i],imghsv,imggray,contourt[i],HSVfeatures);
            HSVfeatures->settotal(contourt[i]);
            hsvList->Insert((*HSVfeatures));
        }
    }

    dst3C.release();
    for(int i=0;i<5;i++)msks[i].release();
}

void getFeatures(Mat limiarizada, Mat ori,int thresholdsAmount,Lde<hsvL>* hsvList)
{

    Mat dst(ori.rows, ori.cols, CV_8UC1);

    dst.setTo(cv::Scalar::all(0));
    dsgGetRegionFromGrayImage(limiarizada,&dst,0,0);
    dsgGetAllContours(dst,ori,hsvList);


    dst.setTo(cv::Scalar::all(0));
  dsgGetRegionFromGrayImage(limiarizada,&dst,128,128);
  dsgGetAllContours(dst,ori,hsvList);


    dst.setTo(cv::Scalar::all(0));
    dsgGetRegionFromGrayImage(limiarizada,&dst,255,255);
    dsgGetAllContours(dst,ori,hsvList);


    int tot = hsvList->getAmount();
    if(tot < 5){
        for(int j=tot;j<5;j++){
            double* hsv = new double[162];
            for(int i=0;i<162;i++)hsv[i]=0;
            hsvL novo;
            novo.sethsv(hsv);
            novo.settotal(0);
            hsvList->Insert(novo);
        }
    }
    dst.release();
}

void validaimgs(HSVimg* db_img)
{
    char PathL[100];
    int aux=0;
    Mat colorOri;
    Mat limiarizada;
    char* name;
    for(int i=0;i<16870;i++){
        geraPath(PathL,i+1);
        name = db_img[i].getPath();
        colorOri = imread(name,CV_LOAD_IMAGE_COLOR);
        limiarizada = imread(PathL,0);
        if(colorOri.rows != limiarizada.rows || colorOri.cols != limiarizada.cols) aux = aux+1;
        colorOri.release();
        limiarizada.release();
    }
    cout<<aux<<endl;
}

bool dsgcalcHistogramsWithMasks(HSVimg* QImg,int id)
{
    char PathL[100];
    geraPath(PathL,id+1);
    char* name = QImg->getPath();
    Mat colorOri = imread(name,CV_LOAD_IMAGE_COLOR);
    Mat limiarizada = imread(PathL,0);

    Lde<hsvL>* lista = new Lde<hsvL>;
    //GaussianBlur( limiarizada, limiarizada, Size( 11, 11 ), 0, 0 );

    getFeatures(limiarizada, colorOri, 2,lista);

    double* Histogram;
    double* features;
    hsvL atual;
    if(lista == NULL)cout<<"ERRO!\nLista de caracteristicas nao criada."<<endl;

    for(int h=0;h<5;h++){
        atual = lista->getFirst<hsvL>();
        Histogram = atual.gethsv();
        features = atual.getfeatures();
        if(h==0){
            QImg->setHistogram1(Histogram);
            QImg->setfeatures1(features[0],features[1],features[2],features[3],features[4]);
        }
        if(h==1){
            QImg->setHistogram2(Histogram);
            QImg->setfeatures2(features[0],features[1],features[2],features[3],features[4]);
        }
        if(h==2){
            QImg->setHistogram3(Histogram);
            QImg->setfeatures3(features[0],features[1],features[2],features[3],features[4]);
        }
        if(h==3){
            QImg->setHistogram4(Histogram);
            QImg->setfeatures4(features[0],features[1],features[2],features[3],features[4]);
        }
        if(h==4){
            QImg->setHistogram5(Histogram);
            QImg->setfeatures5(features[0],features[1],features[2],features[3],features[4]);
        }
    }
    colorOri.release();
    limiarizada.release();
    return true;
}


//int main(int argc, char** argv)
//{
//    HSVimg q; // Image que entra como query
//    HSVimg *DB = new HSVimg[16870]; // DataBase de imagens
//    HSVimg *DBq = new HSVimg[16870]; // DataBase de imagens query
//    int classes[16870];
//    int classesQ[1075];
//    int inout[16870];
//    double *somaA;
//    bool veri;
//    int fim=16870;
//    int ini=0;
//    //double a;
//    dsgReadIds(inout,DB,DBq);
//    dsgReadClasses(DB,DBq);
//    dsgReadClassQ(classesQ);
//    dsgHistogransReader(DB,DBq);
//    dsgReadFeatures(DB,DBq);

//    for(int id = ini; id < fim; id++)
//    {
//        //        IplImage* atual = cvLoadImage(DB[id].getPath()); // Image query para matching das imagens
//        //        DB[id].HistogramCalc(atual); //Calcula histograma da imagem atual
//        //        dsgHistogranSaver(DB[id]);
//        //        cvReleaseImage(&atual);
//        //        veri = dsgcalcHistogramsWithMasks(&DB[id],id);
//        //        if(veri == true){
//        //            dsgfeaturesSaver(DB,id);
//        //        }

//        q = DBq[id]; // Pega uma imagem na posicao i do vetor de imagens para fazer o matching com as outras
//        dsgImgmatching(DB,q); // Faz o matching da atual com as outras imagens do DB
//        dsgQuickSort(DB,0,16869); // Ordena da maior para a menor imagem com o Cos de theta

//        for(int i=0;i<16870;i++)
//        {
//         classes[i] = DB[i].getClasse();
//        }
//        somaA = pra(classes,q.getClasse(),classesQ);
//        dsgPRASaver(id,*somaA);
//        cout<<id<<endl;
//    }
//    return 0;
//}


#endif

#endif // HSVA

