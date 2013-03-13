#ifndef SIMULATIONNETWORK_H
#define SIMULATIONNETWORK_H

#include <list>
#include "industrialnode.h"
#include "market.h"

namespace Econ{

/// This class houses a whole economical network. Markets and industrial nodes
/// are the nodes of the network and dependencies on a market by an industrial
/// node is an edge.

class SimulationNetwork
{
public:
  SimulationNetwork();
  void iterate();
  std::list<Market *> markets;
  std::list<IndustrialNode *> industries;

  int solveProcessRatio;
};

}
#endif // SIMULATIONNETWORK_H
