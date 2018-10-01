#include "Image.h"

void Image::setImg(IplImage *Img) {
  this->Img = Img;
}

void Image::setPath(char *Path) {
  strcpy(this->Path, Path);
}

IplImage *Image::getImg() {
  return Img;
}

char *Image::getPath() {
  return Path;
}
