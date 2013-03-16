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
  ///
  /// The solver works by trying to find the price that maximizes the volume of
  /// transactions that will be done.
  list<order> solve();

  /// Returns the last computed price
  float currentPrice() {return m_LastPrice;}

private:
  float m_LastPrice;
  float m_LastVolume;

  /// Used by solve() to evaluate the volume of transactions that will be done
  /// at the current price
  float evaluateVolumeAtPrice(float price);

};


}


#endif // MARKET_H
