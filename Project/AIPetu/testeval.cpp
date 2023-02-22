#include <chrono>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "Analyst.h"

using namespace std;

int main(void)
{
  srand(time(nullptr));

  try
  {
    int pixelSize = 10;

    vector<string> filenames = { "amazonie_0" };

    for (auto name : filenames)
    {
      auto start = chrono::system_clock::now();

      Image img = Image::readAIP(name);
      img.writeSVG("tester",10);
      Analyst analyst(img);

      cout << analyst.nbZones()
           << ", "
           << analyst.nbZonesOfColor(Color::Green)
           << ", "
           << analyst.nbPixelsOfColor(Color::Green)
           << endl;

      auto end = chrono::system_clock::now();

      chrono::duration<double> elapsed_seconds = end-start;
      cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
    }
  }
  catch(exception e)
  {
    cerr << e.what() << endl;
  }

  return 0;
}
