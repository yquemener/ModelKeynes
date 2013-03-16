#include "botrandomgaussian.h"
#include "industrialnode.h"
#include <random>

using std::pair;
using std::list;

namespace Econ
{

BotRandomGaussian::BotRandomGaussian(IndustrialNode* home, float sigma=0.1f)
  : Bot(home)
{
  m_sigma = sigma;
}

void BotRandomGaussian::updateInfo()
{
}

list<order> BotRandomGaussian::makeTradingDecisions()
{
  list<order> ret;
  // Buy orders
  // ppu = price per unit
  float total_ppu = 0.0f;
  std::normal_distribution<double> distribution(1.0, m_sigma);
  std::map<good_t, float> price_to_pay;
  for(auto it = m_home->m_unitInput.begin();
      it != m_home->m_unitInput.end();
      it++)
  {
    pair<good_t, float> ui = *it;
    float uprice = ui.second * m_home->m_InputMarkets[ui.first]->currentPrice();
    float rand_var = distribution(s_rng());
    uprice *= rand_var;
    price_to_pay[ui.first] = uprice;
    total_ppu += uprice;
  }

  float budget = this->cash/2;
  float units_to_buy = budget/total_ppu;
  for(auto it = m_home->m_unitInput.begin();
      it != m_home->m_unitInput.end();
      it++)
  {
    order o;
    pair<good_t, float> ui = *it;
    o.author = m_id;
    o.type = BUY;
    o.price = price_to_pay[ui.first];
    o.volume = ui.second * units_to_buy;
    ret.push_back(o);;
  }

  for(auto it = m_home->m_OutputMarkets.begin();
      it!=m_home->m_OutputMarkets.end();
      it++)
  {
    good_t g = it->first;
    Market *m = it->second;
    float rand_var = distribution(s_rng());
    order o;
    o.price = m->currentPrice() * rand_var;
    o.volume = this->stock[g];
    o.author = this->m_id;
    o.type = SELL;
  }

  return ret;
}

float BotRandomGaussian::makeProcessingDecisions()
{
  // Computes how many "units" can be processed given the current stock
  float units_to_process = -1;
  for(auto it = m_home->m_unitInput.begin();
      it!=m_home->m_unitInput.end();
      it++)
  {
    pair<good_t, float> ui;
    if(this->stock.find(ui.first)!=this->stock.end())
    {
      float curp = this->stock[ui.first]/ui.second;
      if((units_to_process<0)||(units_to_process>curp))
      {
        units_to_process = curp;
      }
    }
  }
  return std::max(0.0f, units_to_process);
}

std::default_random_engine& BotRandomGaussian::s_rng()
{
  static std::default_random_engine rng;
  return rng;
}

}
