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
}
