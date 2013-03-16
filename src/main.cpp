#include <iostream>
#include "simulationnetwork.h"
#include "botrandomgaussian.h"

using namespace Econ;
using std::cout;
using std::endl;

int main(int argc, char** argv)
{
  // Init goods
  typedef enum{WHEAT=0, FLOUR=1, BREAD=2} good_s;

  s_goodName()[WHEAT] = "Wheat";
  s_goodName()[FLOUR] = "Flour";
  s_goodName()[BREAD] = "Bread";

  // Init network
  const int BOTS_PER_NODE = 30;
  const float BOTS_SIGMA = 0.1f;
  SimulationNetwork net;
  Market marketWheat;
  Market marketFlour;
  Market marketBread;
  IndustrialNode indusFarming;
  IndustrialNode indusMilling;
  IndustrialNode indusBakery;

  indusFarming.m_unitInput.push_back(pair<good_t,float>(BREAD, 0.5f));
  indusFarming.m_unitOutput.push_back(pair<good_t,float>(WHEAT, 1.0f));
  indusFarming.m_InputMarkets[BREAD] = &marketBread;
  indusFarming.m_OutputMarkets[WHEAT] = &marketWheat;
  for(int k=0;k<BOTS_PER_NODE;k++)
  {
    BotRandomGaussian * brg;
    brg = new BotRandomGaussian(&indusFarming, BOTS_SIGMA);
    brg->cash = 10.0;
    indusFarming.m_bots.push_back(brg);
  }
  indusFarming.m_bots.front()->stock[BREAD]=1.0;

  indusMilling.m_unitInput.push_back(pair<good_t,float>(WHEAT, 1.0f));
  indusMilling.m_unitOutput.push_back(pair<good_t,float>(FLOUR, 1.0f));
  indusMilling.m_InputMarkets[WHEAT] = &marketWheat;
  indusMilling.m_OutputMarkets[FLOUR] = &marketFlour;
  for(int k=0;k<BOTS_PER_NODE;k++)
  {
    BotRandomGaussian * brg;
    brg = new BotRandomGaussian(&indusMilling, BOTS_SIGMA);
    brg->cash = 10.0;
    indusMilling.m_bots.push_back(brg);
  }

  indusBakery.m_unitInput.push_back(pair<good_t,float>(FLOUR, 1.0f));
  indusBakery.m_unitOutput.push_back(pair<good_t,float>(BREAD, 1.0f));
  indusBakery.m_InputMarkets[FLOUR] = &marketFlour;
  indusBakery.m_OutputMarkets[BREAD] = &marketBread;
  for(int k=0;k<BOTS_PER_NODE;k++)
  {
    BotRandomGaussian * brg;
    brg = new BotRandomGaussian(&indusBakery, BOTS_SIGMA);
    brg->cash = 10.0;
    indusBakery.m_bots.push_back(brg);
  }

  net.industries.push_back(&indusFarming);
  net.industries.push_back(&indusMilling);
  net.industries.push_back(&indusBakery);
  net.markets.push_back(&marketWheat);
  net.markets.push_back(&marketFlour);
  net.markets.push_back(&marketBread);
  net.solveProcessRatio = 1;

  for(int k=0;k<100;k++)
  //while(1)
  {
    net.iterate();
    cout << "Price wheat : "  << marketWheat.currentPrice();
    cout << "   Volume : " << marketWheat.currentVolume() << endl;
    cout << "Price flour : " << marketFlour.currentPrice();
    cout << "   Volume : " << marketFlour.currentVolume() << endl;
    cout << "Price bread : " << marketBread.currentPrice();
    cout << "   Volume : " << marketBread.currentVolume() << endl;
    cout << endl;
    /*for(auto it = net.industries.begin(); it!=net.industries.end(); it++)
    {
      IndustrialNode * indus = *it;
      for(auto it2 = indus->m_bots.begin(); it2!= indus->m_bots.end(); it2++)
      {
        Bot * b = *it2;
        cout << b->displayStock() << endl;
      }
      cout << endl;
    }
    cout << endl;*/
  }

  return 0;
}
