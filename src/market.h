#ifndef MARKET_H
#define MARKET_H

#include <list>
#include "types.h"

using std::list;

namespace Econ
{

/// Class simulating the market of a single good.
class Market
{
public:
  Market();

  list<order> orders;

  /// Returns the list of accepted transactions
  list<order> solve();

  /// Returns the last computed price
  float currentPrice();

private:
  float m_LastPrice;
  float m_LastVolume;

};


}


#endif // MARKET_H
