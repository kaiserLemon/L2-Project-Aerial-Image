////////////////////////////////////////////////////////////////////////////////
/// This file is part of the Aerial Image Project (AIP).
///
/// Copyright (c) ...
///
/// The sources of AIP are distributed WITHOUT ANY WARRANTY.
////////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <ctime>
#include <sstream>
#include "FireSimulator.h"
#include <Analyst.h>

using namespace std;

int main(void)
{
  srand(time(nullptr));
  /*
  Image image(105,105);

  Image img(makeRandomImage(135,115));
  img.writeAIP("img1");
*/

  Image img(Image::readAIP("amazonie_0"));

  FireSimulator fireSim(img,1,1);
  fireSim.writeFramesToSVG("forest",10);

  return 0;
}
