#include "industrialnode.h"
#include "bot.h"
#include "market.h"

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
      if(m_InputMarkets.find(o.type)!=m_InputMarkets.end())
      {
        m_InputMarkets[o.type]->orders.push_back(o);
      }

      if(m_OutputMarkets.find(o.type)!=m_OutputMarkets.end())
      {
        m_OutputMarkets[o.type]->orders.push_back(o);
      }
    }
  }
}

}
