#include "market.h"
namespace Econ
{

Market::Market()
{
  m_LastPrice = 1.0;
  m_LastVolume = 0.0;
}

// TODO : improve this algorithm. It will solve the market in o(N^2) but it
//        should be done in o(N.log(N))
// TODO : give priority to best prices
list<order> Market::solve()
{
  float bestprice = m_LastPrice;
  float bestvolume = 0;
  list<order> ret;

  for(auto it = orders.begin(); it!=orders.end(); it++)
  {
    order o = *it;
    float vol = evaluateVolumeAtPrice(o.price);
    if(vol>bestvolume)
    {
      bestprice = o.price;
      bestvolume = vol;
    }
  }
  m_LastPrice = bestprice;
  m_LastVolume = bestvolume;

  float volume_to_buy = bestvolume;
  float volume_to_sell = bestvolume;
  for(auto it = orders.begin(); it!=orders.end(); it++)
  {
    order o = *it;
    if((o.type==BUY)&&(o.price>=bestprice))
    {
      if(o.volume<=volume_to_buy)
      {
        volume_to_buy-=o.volume;
        ret.push_back(o);
      }
      else
      {
        order newo = o;
        newo.volume = volume_to_buy;
        volume_to_buy=0;
        ret.push_back(newo);
      }
    }
    if((o.type==SELL)&&(o.price<=bestprice))
    {
      if(o.volume<=volume_to_sell)
      {
        volume_to_sell-=o.volume;
        ret.push_back(o);
      }
      else
      {
        order newo = o;
        newo.volume = volume_to_sell;
        volume_to_sell=0;
        ret.push_back(newo);
      }
    }
  }
  orders.clear();
  return ret;
}

float Market::evaluateVolumeAtPrice(float price)
{
  float volume_sold = 0.0f;
  float volume_bought = 0.0f;

  for(auto it = orders.begin(); it!=orders.end(); it++)
  {
    order o = *it;
    if((o.type == BUY) && (o.price>=price))
    {
      volume_bought += o.volume;
    }
    else if((o.type == SELL) && (o.price<=price))
    {
      volume_sold += o.volume;
    }
  }
  return std::min(volume_sold, volume_bought);
}

}
