////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include "Analyst.h"
#include <iostream>

Analyst::Analyst(const Image& img){

  this->image = &img;

  colorOccurence = new int[Color::nbColors()-1];
  nbZonesPerColor = new int [Color::nbColors()-1];

  nbElem = image->size();
  nbPart = Color::nbColors()-1;
  nbOfZones = 0;

  for(int i = 0; i <= nbPart; i++) {
    colorOccurence[i] = 0;
    nbZonesPerColor[i] = 0;
  }

  representation = new std::pair<int,int>[nbElem];



  representation[image->toIndex(1,1)] = std::make_pair(image->toIndex(1,1),image->toIndex(1,1));
  nbZonesPerColor[image->getPixel(1,1).toInt()]++;
  colorOccurence[image->getPixel(1,1).toInt()]++;
  nbOfZones++;


  for(int j = 2; j <= image->width(); j++) {

    if(image->getPixel(1,j) == image->getPixel(1,j-1)) {
      representation[image->toIndex(1,j)] = std::make_pair(image->toIndex(1,j-1),image->toIndex(1,j-1));
    } else {
      representation[image->toIndex(1,j)] = std::make_pair(image->toIndex(1,j),image->toIndex(1,j));
      nbZonesPerColor[image->getPixel(1,j).toInt()]++;
      nbOfZones++;
    }
    colorOccurence[image->getPixel(1,j).toInt()]++;
  }


  for(int i = 2; i <= image->height(); i++) {
    colorOccurence[image->getPixel(i,1).toInt()]++;
    if(image->getPixel(i,1) == image->getPixel(i-1,1)) {
      representation[image->toIndex(i,1)] = std::make_pair(image->toIndex(i-1,1),image->toIndex(i-1,1));
    } else {
      representation[image->toIndex(i,1)] = std::make_pair(image->toIndex(i,1),image->toIndex(i,1));
      nbZonesPerColor[image->getPixel(i,1).toInt()]++;
      nbOfZones++;
    }

  }

  for(int i = 2; i <= image->height(); i++){
    for(int j = 2; j <= image->width(); j++){
      colorOccurence[image->getPixel(i,j).toInt()]++;

      if(image->getPixel(i,j) == image->getPixel(i-1,j)){
        representation[image->toIndex(i,j)] = std::make_pair(image->toIndex(i-1,j),image->toIndex(i-1,j));
      }

       if(image->getPixel(i,j) == image->getPixel(i,j-1)) {
         if(image->getPixel(i,j) == image->getPixel(i-1,j)){
           representation[image->toIndex(i,j)].second = image->toIndex(i,j-1);
         } else {
           representation[image->toIndex(i,j)] = std::make_pair(image->toIndex(i,j-1),image->toIndex(i,j-1));
         }

      } else if (!(image->getPixel(i,j) == image->getPixel(i-1,j))){
        representation[image->toIndex(i,j)] = std::make_pair(image->toIndex(i,j),image->toIndex(i,j));
        nbZonesPerColor[image->getPixel(i,j).toInt()]++;
        nbOfZones++;
      }

    }
  }


}

Analyst::~Analyst(){
  delete[] colorOccurence;
}

// Recursive Algorithm
bool Analyst::belongToTheSameZone(int i1, int j1, int i2, int j2){

  if(image->getPixel(i1,j1) != image->getPixel(i2,j2)) return false;

  if((i1 == i2) && (i2 == j2)) {
    return true;
  } else {
    std::pair<int,int> indexPair1 = representation[image->toIndex(i1,j1)];

    std::pair<int,int> p1 = image->toCoordinate(indexPair1.first);
    // First Pixel i1j2 points towards
    int i1Temp1 = p1.first;
    int j1Temp1 = p1.second;


    std::pair<int,int> p2 = image->toCoordinate(indexPair1.second);
    // Second Pixel i1j2 points towards
    int i1Temp2 = p2.first;
    int j1Temp2 = p2.second;


    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    std::pair<int,int> indexPair2 = representation[image->toIndex(i2,j2)];

    std::pair<int,int> p12 = image->toCoordinate(indexPair2.first);
    // First Pixel i1j2 points towards
    int i2Temp1 = p12.first;
    int j2Temp1 = p12.second;

    //std::cout << "BRRR"<< i2Temp1 << j2Temp1;

    std::pair<int,int> p22 = image->toCoordinate(indexPair2.second);
    // Second Pixel i1j2 points towards
    int i2Temp2 = p22.first;
    int j2Temp2 = p22.second;

    if((i1Temp1 == i1 && j1Temp1 == j1 && i1Temp2 == i1 && j1Temp2 == j1)
      && (i2Temp1 == i2 && j2Temp1 == j2 && i2Temp2 == i2 && j2Temp2 == j2)) return false;

    if(i1Temp1 == i1 && j1Temp1 == j1 && i1Temp2 == i1 && j1Temp2 == j1){
      return belongToTheSameZone(i1,j1,i2Temp1,j2Temp1) || belongToTheSameZone(i1,j1,i2Temp2,j2Temp2);
    }

    if(i2Temp1 == i2 && j2Temp1 == j2 && i2Temp2 == i2 && j2Temp2 == j2){
      return belongToTheSameZone(i1Temp1,j1Temp1,i2,j2) || belongToTheSameZone(i1Temp2,j1Temp2,i2,j2);
    }


    return belongToTheSameZone(i1Temp1,j1Temp1,i2Temp1,j2Temp1) ||
           belongToTheSameZone(i1Temp1,j1Temp1,i2Temp2,j2Temp2) ||
           belongToTheSameZone(i1Temp2,j1Temp2,i2Temp1,j2Temp1) ||
           belongToTheSameZone(i1Temp2,j1Temp2,i2Temp2,j2Temp2);

  }







}

int Analyst::nbPixelsOfColor(Color c) const {
  return colorOccurence[c.toInt()];
}

int Analyst::nbZonesOfColor(Color c) const {
  return nbZonesPerColor[c.toInt()];
}

int Analyst::nbZones() const {
  return nbOfZones;
}

Image Analyst::fillZone(int i, int j, Color c){
  Image img(image->height(), image->width());

  for(int i2 = 1; i2 <= image->height(); i2++){
    for(int j2 = 1; j2 <= image->width(); j2++){
      if(belongToTheSameZone(i,j,i2,j2)){
        img.setPixel(i2,j2,c);
      } else {
        img.setPixel(i2,j2,image->getPixel(i2,j2));
      }

    }
  }

  return img;
}

std::set<int> Analyst::zoneOfPixel(int i, int j){
  std::set<int> pixels;

  for(int i2 = 1; i2 <= image->height(); i2++){
    for(int j2 = 1; j2 <= image->width(); j2++){
      if(belongToTheSameZone(i,j,i2,j2)){
        pixels.insert(image->toIndex(i2,j2));
      }
    }
  }

  return pixels;
}
