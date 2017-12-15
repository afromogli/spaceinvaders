#include "Random.h"
#include <random>
#include "xorshift.h"

namespace Common
{
  int Random::getValue(const int minValue, const int maxValue)
  {
    std::random_device rd;
    xorshift gen(rd());
    const std::uniform_int_distribution<> dist(minValue, maxValue);
    return dist(gen);
  }

  float Random::getValue(const float minValue, const float maxValue)
  {
    std::random_device rd;
    xorshift gen(rd());
    const std::uniform_real_distribution<> dist(minValue, maxValue);
    return float(dist(gen));
  }
}
