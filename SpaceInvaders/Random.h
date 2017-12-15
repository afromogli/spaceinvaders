#pragma once

namespace Common
{
  class Random
  {
  public:
    /**
     * @brief Returns a random integer value between the specified interval (inclusive)
     * @param minValue The allowed minimum random value 
     * @param maxValue The allowed maximum random value
     * @return The random value in the range [minValue, maxValue]
     */
    static int getValue(const int minValue, const int maxValue);

    /**
    * @brief Returns a random integer value between the specified interval (inclusive)
    * @param minValue The allowed minimum random value
    * @param maxValue The allowed maximum random value
    * @return The random value in the range [minValue, maxValue]
    */
    static float getValue(const float minValue, const float maxValue);
  };
}