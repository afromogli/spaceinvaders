#include "Vector2.h"
#include <random>
#include <sstream>
#include "Random.h"

namespace Common
{
  Vector2f Vector2f::Zero = Vector2f(0, 0);

  float Vector2f::distanceTo(const Vector2f & otherVec) const
  {
    const float xDiff = otherVec.x - this->x;
    const float yDiff = otherVec.y - this->y;
    return sqrt(xDiff*xDiff + yDiff*yDiff);
  }

  float Vector2f::length() const
  {
    return sqrt(x*x + y*y);
  }

  Vector2f Vector2f::getNormalized() const
  {
    return *this / length();
  }

  Vector2f Vector2f::getRandomizedVector(const int xMinValue, const int xMaxValue, const int yMinValue, const int yMaxValue)
  {
    return Vector2f(float(Random::getValue(xMinValue, xMaxValue)), float(Random::getValue(yMinValue, yMaxValue)));
  }

  std::wstring Vector2f::toString() const
  {
    std::ostringstream outStream;
    outStream << "x: ";
    outStream << x;
    outStream << " y: ";
    outStream << y;
    return std::wstring(outStream.str().begin(), outStream.str().end());
  }
}
