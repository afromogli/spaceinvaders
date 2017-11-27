#pragma once
#include <stdexcept>

namespace Common
{
  class ElementNotFoundInCollectionException : public std::logic_error
  {
  public:
    explicit ElementNotFoundInCollectionException(const std::string& message) : logic_error(message)
    {
    }

    explicit ElementNotFoundInCollectionException(const char* message) : logic_error(message)
    {
    }
  };
}
