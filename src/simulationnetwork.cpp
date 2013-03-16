#include "simulationnetwork.h"
#include "bot.h"

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

    // TODO : move this into industrialNode
    for(auto it = markets.begin(); it!=markets.end(); it++)
    {
      Market * mark = *it;
      list<order> accepted;
      mark->solve();
      for(auto ito = accepted.begin();ito!=accepted.end();ito++)
      {
        order o = *ito;
        Bot *b = (*Bot::s_idTable())[o.author];
        if(o.type == BUY)
        {
          b->cash -= o.price * o.volume;
          b->stock[o.good] += o.volume;
        }
        else if(o.type == SELL)
        {
          b->cash += o.price * o.volume;
          b->stock[o.good] -= o.volume;
        }
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
