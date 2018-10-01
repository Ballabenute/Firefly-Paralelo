#include "Cluster.h"
#include "bests.h"
#include "incl.h"
#include "multilimiarizacao.h"
#include <iostream>

#ifndef GRAYSEG
#define GRAYSEG

using namespace std;

Mat grayseg(Mat m, Cluster &c) {

  IplImage copy = m;
  IplImage *img = &copy;
  if (!img) {
    cout << "Imagem Invalida!" << endl;
    exit(0);
  } // check if image is valid

  vector<int> lims =
      bests(img, 4, (c.size() - 1) * 200, 100,
            c); // use firefly to get the best thresholds possible

  IplImage *resp;

  resp = MultiLim(img, lims, notbackwards); // segments the image with the
                                            // thresholds found with firefly

  Mat resMat;

  resMat = cvarrToMat(resp);

  return resMat;
}
#endif // GRAYSEG
