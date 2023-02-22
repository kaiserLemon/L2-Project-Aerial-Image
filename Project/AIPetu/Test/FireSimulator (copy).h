////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#ifndef FIRE_SIMULATOR_H
#define FIRE_SIMULATOR_H

#include <vector>
#include "Image.h"

////////////////////////////////////////////////////////////////////////////////
/// This is a fire simulator.
///
/// Given a pixel of forest in an image, it simulates a fire in the zone
/// of forest of the given pixel.
////////////////////////////////////////////////////////////////////////////////
class FireSimulator {
public:
// Creates a fire starting at position x and y of img
  FireSimulator(const Image& img, int x, int y);

// timeFrame increases by 1
//  void incrementTime();

// Simulate a fire's spread during one frame
//  Image simulateFirePeriod();

// Simulate a fire's spread during a period

//  std::vector<Image> simulateFirePeriod(int period);

// Write all the current simulated frames to SVG
//  void writeFramesToSVG(const std::string& filename, int pixelSize);




  // Destructor
  ~FireSimulator();


private:


  int timeFrame;
  std::vector<Image> frames;
  std::vector<std::vector<std::pair<int,int>>> pixels;

};

#endif
