#include "simulationnetwork.h"
#include "good.h"

using namespace Econ;

int main(int argc, char** argv)
{
  // Init goods
  typedef enum{WHEAT=0, FLOUR=1, BREAD=2} good_s;

  s_goodName[WHEAT] = "Wheat";
  s_goodName[FLOUR] = "Flour";
  s_goodName[BREAD] = "Bread";

  SimulationNetwork net;
  Market marketWheat;
  Market marketFlour;
  Market marketBread;
  IndustrialNode indusFarming;
  IndustrialNode indusMilling;
  IndustrialNode indusBakery;



  return 0;
}
