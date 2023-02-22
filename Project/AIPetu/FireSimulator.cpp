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
    // When we simulate fire, our original image is frame 0
    timeFrame = 0;

    // Add the initial frame to all images
    frames.push_back(img);

    // If the Pixel at x,y is foresty, we can start a fire

    if(img.getPixel(x,y) == Color::Green){
      Image imgT1 (img);
      imgT1.setPixel(x,y,Color::Red);
      frames.push_back(imgT1);
      incrementTime();

      // Turn the x,y into a pair and add it to the list of burning pixels
      std::pair<int,int> firstPixel = std::make_pair(x,y);
      std::vector<std::pair<int,int>> burningAtT0;
      burningAtT0.push_back(firstPixel);
    }

}


FireSimulator::~FireSimulator(){

}

void FireSimulator::incrementTime(){
  timeFrame++; // Increases the frame
}

void FireSimulator::writeFramesToSVG(const std::string& filename, int pixelSize){
  for(int i = 0; i <= timeFrame; i++){
    std::string fname = filename + std::to_string(i);
    frames[i].writeSVG(fname, pixelSize);
  }
}
