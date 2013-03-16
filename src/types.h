#ifndef TYPES_H
#define TYPES_H
#include "good.h"

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
  good_t good;
  float volume;
  float price;
};

}

#endif // TYPES_H
