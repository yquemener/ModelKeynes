#include "botrandomgaussian.h"
#include "industrialnode.h"
#include <random>

using std::pair;
using std::list;

namespace Econ
{

BotRandomGaussian::BotRandomGaussian(IndustrialNode* home, float sigma=1.0)
  : Bot(home)
{
  m_sigma = sigma;
}

void BotRandomGaussian::updateInfo()
{
}

list<order> BotRandomGaussian::makeTradingDecisions()
{
  // ppu = price per unit
  float total_ppu = 0.0f;
  std::normal_distribution<double> distribution(0.0, m_sigma);

  for(auto it = m_home->m_unitInput.begin();
      it != m_home->m_unitInput.end();
      it++)
  {
    pair<good_t, float> ui = *it;
    float uprice = ui.second * m_home->m_InputMarkets[ui.first]->currentPrice();
    total_ppu += uprice;
  }

  float budget = this->cash/2;
  float units_to_buy = budget/total_ppu;
  for(auto it = m_home->m_unitInput.begin();
      it != m_home->m_unitInput.end();
      it++)
  {
    sd
  }
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

static std::default_random_engine& s_rng()
{
  static std::default_random_engine rng;
  return rng;
}

}
