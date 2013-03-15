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
      list<order> accepted;
      mark->solve();
      for(auto ito = accepted.begin();it!=accepted.end();it++)
      {

      }
    }
  }
  for(auto it = industries.begin(); it!=industries.end(); it++)
  {
    IndustrialNode * indus = *it;
    indus->iterateIndustry();
  }
}

}
