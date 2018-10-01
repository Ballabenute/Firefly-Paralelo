#ifndef HSVIMG_H
#define HSVIMG_H

#include "Image.h"
#include <cmath>
#include <iostream>
#include <opencv2/calib3d/calib3d.hpp>
//#include <opencv2/contrib/contrib.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/core_c.h>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/flann/miniflann.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/video/video.hpp>

class HSVimg {
public:
  HSVimg();
  void setImg(IplImage *);
  IplImage *getImg();
  void setDist(int);
  void setName(char *);
  void setClasse(int);
  void setId(int);
  void setLetra(char);
  void setInoutdoor(int);
  void setPath(char *);

  void setHistogram1(double *);
  double *getHistogram1();
  void setHistogram2(double *);
  double *getHistogram2();
  void setHistogram3(double *);
  double *getHistogram3();
  void setHistogram4(double *);
  double *getHistogram4();
  void setHistogram5(double *);
  double *getHistogram5();

  char *getName();
  float getDist();
  double *HistogramCalc(IplImage *);
  int getClasse();
  int getId();
  char getLetra();
  int getInoutdoor();
  void MathingGlobal(HSVimg query);
  void Matching(HSVimg query);
  char *getPath();

  void setfeatures1(double, double, double, double, double);
  void setfeatures2(double, double, double, double, double);
  void setfeatures3(double, double, double, double, double);
  void setfeatures4(double, double, double, double, double);
  void setfeatures5(double, double, double, double, double);

  double *getfeatures1();
  double *getfeatures2();
  double *getfeatures3();
  double *getfeatures4();
  double *getfeatures5();

  bool operator>(HSVimg Test);
  bool operator<(HSVimg Test);

private:
  float Dist;

  double *Histogram1;
  double *Histogram2;
  double *Histogram3;
  double *Histogram4;
  double *Histogram5;

  char name[256];
  int classe;

  char Path[256];
  int id;
  char letra;
  int inoutdoor;
  IplImage *Img;

  double features1[5];
  double features2[5];
  double features3[5];
  double features4[5];
  double features5[5];
};
#endif
