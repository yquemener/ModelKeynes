#ifndef BOT_H
#define BOT_H

#include <list>
#include <map>
#include "types.h"
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

  virtual bool isBankrupt() {return cash<0; }

  agent_id getId() {return m_id;}

  // These are public : industrialNode needs to write to them and other actors
  // can read them
  float                    cash;
  std::map<good_t, float>  stock;

  // This allows to automatically attribute a unique id to a bot and to easily
  // find a bot from its id
  static std::map<agent_id, Bot*>* s_idTable()
  {
    static map<agent_id, Bot*> idTable;
    return &idTable;
  }

  static agent_id s_newId()
  {
    static agent_id currentId=0;
    return currentId++;
  }

private:
  agent_id        m_id;
  IndustrialNode* m_home;

};

}

#endif // BOT_H
