#include "incl.h"
#include <algorithm>

#ifndef MULTILIMIARIZACAO
#define MULTILIMIARIZACAO

enum flag{

    backwards = 1,
    notbackwards = 0

};

vector<double> sortBackwards(vector<double> lim){

    int size = lim.size();

    for(int i=0; i<size; i++){
        lim[i] = -lim[i];
    }

    sort(lim.begin(),lim.end());

    for(int i=0; i<size; i++){
        lim[i] = -lim[i];
    }

    return lim;
}

IplImage* MultiLim(IplImage* im , vector<int> bests, int flag){

    vector<int> limiares;

    limiares.push_back(0);

    for(int i =0; i< bests.size(); i++){
        limiares.push_back(bests[i]);
    }

    limiares.push_back(255);

    int L = limiares.size();

    vector<double> lim;

    for(int i=0; i<L-1; i++){
        lim.push_back(i);
    }

    int quo =0 ;
    if(flag){
        lim = sortBackwards(lim);
        quo =  lim[0] - lim[lim.size()-1];
    }else{
        quo = lim[lim.size()-1] - lim[0];
    }
//    cout<<"max = " <<lim[lim.size()-1]<<endl;
//    cout<<"min = " <<lim[0]<<endl;
//    cout<<"QUO!!!! = " <<quo<<endl;


//      divide vector lim inteiro por max(lim) - min(lim)
        for(int i=0; i<lim.size(); i++){
            lim[i] = lim[i]/quo;
        }

//        puts("");
//        for(int i=0; i<lim.size(); i++){
//            cout<< lim[i]<< " e ";
//        }
//        puts("");

//    multiplica o vector inteiro por 255

        for(int i=0; i<lim.size(); i++){
            lim[i] = lim[i]*255;
        }

       //backwards ta bugando nos proximos fors
//    arredonda os valores do vector lim
        //int ja arredonda, porem tem que fazer ceil se for float
        int linhas = im->height;
        int colunas = im->width;
        int i = 0;
        int clust = 0;

        for(int y=0; y<linhas; y++){
            for(int x=0; x<colunas; x++){
                int t1 = bests[0];
                int t2 = bests[1];

                if(((uchar*)(im->imageData + im->widthStep*y))[x] >= t1 && ((uchar*)(im->imageData + im->widthStep*y))[x]<=t2){
                    ((uchar*)(im->imageData + im->widthStep*y))[x] = lim[0];
                }
                else{
                   i= 1;
                   clust =1;
                   while(clust){
                       t1 = lim[i];
                       t2 = lim[i+1];

                       if(((uchar*)(im->imageData + im->widthStep*y))[x]>= t1 && ((uchar*)(im->imageData + im->widthStep*y))[x]<=t2){
                           clust=0;
                           ((uchar*)(im->imageData + im->widthStep*y))[x] = lim[i];
                        }
                        i+=1;
                   }
                }
            }
        }

        return im;
}

#endif // MULTILIMIARIZACAO

