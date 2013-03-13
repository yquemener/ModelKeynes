#ifndef MARKET_H
#define MARKET_H

#include <list>

using std::list;

namespace Econ
{

/// Identification of an economical agent (typically a bot) able to pass orders
/// to a market.
typedef int agent_id;

/// Nature of an order : buy or sell
typedef enum{BUY, SELL} order_t;

/// Structure describing a sell or buy orders passed on the market
struct order
{
  agent_id author;
  order_t type;
  float volume;
  float price;
};

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
