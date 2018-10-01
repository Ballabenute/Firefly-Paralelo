#ifndef IMAGE_H
#define iMAGE_H

#include <cstring>
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

class Image {
public:
  void setImg(IplImage *);
  void setPath(char *);
  IplImage *getImg();
  char *getPath();

private:
  IplImage *Img;
  char Path[256];
};

#endif
