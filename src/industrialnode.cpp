#include "industrialnode.h"
#include "bot.h"
#include "market.h"
#include <list>

namespace Econ
{

IndustrialNode::IndustrialNode()
{
}

void IndustrialNode::iterateTransactions()
{
  for(auto it = m_bots.begin(); it!=m_bots.end(); it++)
  {
    Bot* b = *it;
    list<order>raw_orders = b->makeTradingDecisions();

    list<order> orders;
    for(auto ito = raw_orders.begin(); ito!=raw_orders.end(); ito++)
    {
      // TODO : validate that orders are valid (enough cash and enough stock)
      order newo = *ito;
      newo.author = b->getId();
      orders.push_back(newo);
    }
    for(auto ito = orders.begin(); ito!=orders.end();ito++)
    {
      order o = *ito;
      if(m_InputMarkets.find(o.good)!=m_InputMarkets.end())
      {
        m_InputMarkets[o.good]->orders.push_back(o);
      }

      if(m_OutputMarkets.find(o.good)!=m_OutputMarkets.end())
      {
        m_OutputMarkets[o.good]->orders.push_back(o);
      }
    }
  }
}

void IndustrialNode::iterateIndustry()
{
  for(auto it = m_bots.begin(); it!=m_bots.end(); it++)
  {
    Bot* b = *it;
    float raw_order = b->makeProcessingDecisions();
    // TODO : validate that the order is valid (enough enough stock)

    for(auto iti = m_unitInput.begin(); iti!=m_unitInput.end(); iti++)
    {
      std::pair<good_t, float> ui = *iti;
      b->stock[ui.first] -= ui.second * raw_order;
    }
    for(auto ito = m_unitOutput.begin(); ito!=m_unitOutput.end(); ito++)
    {
      std::pair<good_t, float> uo = *ito;
      b->stock[uo.first] += uo.second * raw_order;
    }
  }
}

}
