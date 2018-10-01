#include "Cluster.h"
#include "Slave.h"
#include "grayseg.h"
#include "incl.h"
#include <boost/filesystem.hpp>
#include <mpi.h>
#include <string>
#include <vector>

using namespace std;
using namespace cv;
using namespace boost::filesystem;
void mainRoot(Cluster &c) {
  path p(string("./../../Imagens_Teste"));
  for (auto f : directory_iterator{p}) {
    cout << f << endl;

    Mat im = imread(f.path().c_str(), 0); // load image
    namedWindow("Original Mat", CV_WINDOW_KEEPRATIO);
    imshow("Original Mat", im);

    Mat resp = grayseg(im, c); // segment image in gray scale
    namedWindow("Segmented Mat", CV_WINDOW_KEEPRATIO);
    imshow("Segmented Mat", resp);
    // imshow("Segmented Mat", im);
  }
  int has_more = false;
  c.broadcast(has_more, 0);
}

void mainSlave(Cluster &c) {
  slave(c);
}

int main(int argc, char *argv[]) {

  Cluster c(&argc, &argv);

  if (c.rank() == 0) {
    mainRoot(c);
  } else {
    mainSlave(c);
  }

  return 0;
}
