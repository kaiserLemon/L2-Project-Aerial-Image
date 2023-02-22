////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Image.h"


void Image::writeSVG(const std::string& filename, int pixelSize) const
{
  assert(pixelSize > 0);

  std::ofstream file;
  file.open(filename + ".svg");

  if (!file) throw std::runtime_error("error open file (write SVG)");

  file << "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
       << std::endl
       << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\""
       << pixelSize*width()
       << "\" height=\""
       << pixelSize*height()
       << "\">"
       << std::endl;

  for (int i = 1; i <= height(); ++i)
    for (int j = 1; j <= width(); ++j)
      file << "<rect width=\""
           << pixelSize
           << "\" height=\""
           << pixelSize
           << "\" x=\""
           << pixelSize*(j-1)
           << "\" y=\""
           << pixelSize*(i-1)
           << "\" fill=\""
           << getPixel(i, j)
           << "\" />"
           << std::endl;

  file << "</svg>"
       << std::endl;

  file.close();
}


  Image::Image(int w, int h){
    imageHeight = h;
    imageWidth = w;
    imageMatrice = new Color[imageWidth * imageHeight];

    for(int i = 0; i < width() * height(); i++){
       imageMatrice[i] = Color::Black;
    }

  }

  Image::Image(const Image& img){
    imageHeight = img.height();
    imageWidth  = img.width();

    for(int i = 1; i <= height(); i++){
      for(int j = 1; j <=  width(); j++){
        imageMatrice[toIndex(i,j)] = img.getPixel(i,j);
      }
    }

  }

  Image::~Image(){
    delete[] imageMatrice;
  }

  int Image::width() const {
    return imageWidth;
  }

  int Image::height() const{
    return imageHeight;
  }

  int Image::size() const{
    return imageHeight * imageWidth;
  }

  Color Image::getPixel(int i, int j) const{
    assert((i >= 1 && i <= height()) && (j >= 1 && j <= width()));
    return imageMatrice[toIndex(i,j)];
  }

  void Image::setPixel(int i, int j, Color col){
    assert((i >= 1 && i <= height()) && (j >= 1 && j <= width()));
    imageMatrice[toIndex(i,j)] = col;
  }

  int Image::toIndex(int i, int j) const {
    return (i-1)*imageWidth+(j-1);
  }

  std::pair<int, int> Image::toCoordinate(int k) const {
    int i,j;
    i = k / width();
    j = k % width();

    return std::make_pair(i + 1,j + 1);

  }


  void Image::fill(Color c) {
    for(int i = 0; i < width() * height(); i++){
      imageMatrice[i] = c;
    }
  }

  void Image::fillRectangle(int i1, int j1, int i2, int j2, Color c){
    assert(i2 >= i1 && j2 >= j1);

      for(int i = i1; i <= i2; i++){
        for(int j = j1; j <= j2; j++){
          setPixel(i,j,c);
        }
      }
}

void Image::writeAIP(const std::string& filename) const{
  std::ofstream file;
  file.open(filename + ".aip");

  if (!file) throw std::runtime_error("error open file (write AIP)");
  file << width()
       << " "
       << height()
       << std::endl;

  for(int i = 1; i < height()-1; i++){
    for(int j = 1; j < width()-1; j++){
      file << imageMatrice[toIndex(i,j)].toInt();
    }
      file << std::endl;
  }

  file.close();

}

Image Image::readAIP(const std::string& filename){
  std::ifstream file;
  file.open(filename + ".aip");

  if (!file) throw std::runtime_error("error open file (read AIP)");

  std::string str;
  std::getline(file, str);

  int w , h;

  std::istringstream istr(str);
  istr >> w >> h;

  int i = 1;

    std::cout << "w = " << w << " h= " << h << std::endl;

  Image img(w,h);
  if (!file) throw std::runtime_error("error open file (read AIP)");

  while ( getline (file,str) )
    {

    for(int j=0; j < str.length(); j++){
    //  std::cout << str[i];
      int colorCode = (int)str[j] - (int)'0';
      std::cout<< colorCode;
      img.setPixel(i,j+1, Color::makeColor(colorCode));

     }
     i++;
      std::cout << std::endl;
    }


  return img;
}


bool Image::operator==(const Image& img) const {
  if(img.width() != imageWidth || img.height() != imageHeight) return false;

  for(int k = 0; k < imageWidth * imageHeight; k++){
    if(imageMatrice[k] != img.imageMatrice[k]) return false;
  }
  return true;
}

bool Image::operator!=(const Image& img) const {
  return !operator==(img);
}

bool Image::areConsecutivePixels(int i1, int j1, int i2, int j2){
  assert((i1 >= 1 && i1 <= height()) && (j1 >= 1 && j1 <= width()) && (i2 >= 1 && i2 <= height()) && (j2 >= 1 && j2 <= width()));
  return (i2 == i1+1 && j2 == j1) || (i2 == i1 && j2 == j1+1) || (i2 == i1-1 && j2 == j1) || (i2 == i1 && j2 == j1-1);
}

Image makeRandomImage(int w, int h){
  Image img(w,h);

  for(int i = 1; i <= h; i++){
    for(int j = 1; j <= w; j++){
      Color c = Color::makeColor(rand() % Color::nbColors());
      img.setPixel(i,j, c);
    }
  }

  return img;

}
