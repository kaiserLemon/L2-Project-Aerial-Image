////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include "Analyst.h"
#include "FireSimulator.h"
#include <iostream>

FireSimulator::FireSimulator(const Image& img, int x, int y){

    // Add the initial frame to all images
    frames.push_back(img);
    //Image test(img);
    Image *test = new Image(img)
   if(img.getPixel(x,y) == Color::Green){
  // Image imgT1 (img);
    //  imgT1.setPixel(x,y,Color::Red);
      //frames.push_back(imgT1);
    }

    delete test;
    std::pair<int,int> firstPixel = std::make_pair(x,y);
    std::vector<std::pair<int,int>> burningAtT0;
    burningAtT0.push_back(firstPixel);

    pixels.push_back(burningAtT0);

}


FireSimulator::~FireSimulator(){

}
