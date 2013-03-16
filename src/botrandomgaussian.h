#ifndef BOTRANDOMGAUSSIAN_H
#define BOTRANDOMGAUSSIAN_H
#include "bot.h"
#include <random>

namespace Econ
{
/// This bot buys and sells at the current market price plus a variation given
/// by a normal distribution. It will only operate if it does a profit.It will
/// spend half its cash at each iteration.
class BotRandomGaussian : public Bot
{
public:
  BotRandomGaussian(IndustrialNode* home, float sigma);

  void updateInfo();
  std::list<order> makeTradingDecisions();
  float makeProcessingDecisions();

private:
  float m_sigma;

  /// Random number generator
  static std::default_random_engine& s_rng();
};

}
#endif // BOTRANDOMGAUSSIAN_H
