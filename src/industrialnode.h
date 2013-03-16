#ifndef INDUSTRIALNODE_H
#define INDUSTRIALNODE_H

#include <list>
#include <map>
#include "market.h"
#include "good.h"

using std::list;
using std::map;
using std::pair;

namespace Econ
{

class Bot;

/// This class describes a node of the economical graph.
///
/// These nodes are the environment where bots live. At the core of each node
/// is an industrial transformation that require 0..n different types of raw
/// materials and produce 0..n goods. It gives acces to markets in order to
/// buy raw materials and to sell processed goods. It manages the communication
/// between bots and markets, checks the validity of orders and transactions and
/// attribute processed goods to bots on each iterations.
class IndustrialNode
{
public:
  IndustrialNode();

  /// Gives every bot a round to buy and sell goods
  void iterateTransactions();

  /// Processes, for every bot, input goods into output goods
  void iterateIndustry();

  /// Removes bankrupted bots from the competition
  void cleanUpBots();

  map<good_t, Market*> m_InputMarkets;
  map<good_t, Market*> m_OutputMarkets;
  list<Bot*> m_bots;

  /// Describes the number of raw goods necessary to create "one unit" of output
  list< pair<good_t, float> > m_unitInput;

  /// Describes what "one unit" of output is
  list< pair<good_t, float> > m_unitOutput;
};


}
#endif // INDUSTRIALNODE_H
