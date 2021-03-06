#include "incl.h"

#ifndef CALCHISTGRAY
#define CALCHISTGRAY

void histCalc(IplImage* img, vector<double>* H){ // ok
   int linhas = img->height;
   int colunas =img->width;

   for(int i=0; i<256; i++)  H[i] = 0;

   int L;

   for(int y =0; y<linhas; y++){
       for(int x =0; x<colunas; x++){
           L = ((uchar*)(img->imageData + img->widthStep*y))[x];

           H[L] = H[L] +1;
       }
   }

   for(int i=0; i<256; i++){
       H[i] = H[i]/(linhas*colunas);
//       cout<<i+1<< "-  "<<H[i]<<endl;
   }


//   cout<<"l "<<linhas<<endl;
//   cout<<"c "<<colunas<<endl;

}

void arqHist(){

    vector<vector<double>(256, 0)> histBuffer (16870);
    vector<string> caminhos(16870);
        for(int i=0; i<16870; i++){
            IplImage* img = cvLoadImage("string");
            histCalc (img, histBuffer[i]);
        }
}

#endif // CALCHISTGRAY

