#ifndef BOT_H
#define BOT_H

#include <list>
#include <map>
#include "market.h"
#include "good.h"

namespace Econ{

class IndustrialNode;

/// Bot simulates an economical agent. It "lives" in an IndustrialNode and has
/// access to the markets the industrial node is linked to. There are usually
/// numerous agents in competition inside an industrial node. If an agent's cash
/// is below zero, it is considered bankrupted and removed from the simulation

class Bot
{
public:
  Bot(IndustrialNode* home);

  /// Reads new information from the IndustrialNode
  virtual void updateInfo();

  /// generates buying/selling orders
  virtual std::list<order> makeTradingDecisions();

  /// generates processing orders. Only a float is necessary : only one kind
  /// of goods can be processed
  virtual float makeProcessingDecisions();

  bool isBankrupt();

  // These are public : industrialNode needs to write to them and other actors
  // can read them
  float                    cash;
  std::map<good_t, float>  stock;
};

}

#endif // BOT_H
