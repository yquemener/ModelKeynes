#include "simulationnetwork.h"

namespace Econ{

SimulationNetwork::SimulationNetwork()
{
}

void SimulationNetwork::iterate()
{
  for(int i=0;i<solveProcessRatio;i++)
  {
    for(auto it = industries.begin(); it!=industries.end(); it++)
    {
      IndustrialNode * indus = *it;
      indus->iterateTransactions();
    }

    for(auto it = markets.begin(); it!=markets.end(); it++)
    {
      Market * mark = *it;
      mark->solve();
      // TODO : processed accepted transactions !
    }
  }
  for(auto it = industries.begin(); it!=industries.end(); it++)
  {
    IndustrialNode * indus = *it;
    indus->iterateIndustry();
  }
}

}
