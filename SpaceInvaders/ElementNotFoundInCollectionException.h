#pragma once
#include <stdexcept>
#include "String.h"

namespace Common
{
  class ElementNotFoundInCollectionException : public std::logic_error
  {
  public:
    explicit ElementNotFoundInCollectionException(const std::wstring& message) : logic_error(Common::to_string(message))
    {
    }

    explicit ElementNotFoundInCollectionException(const char* message) : logic_error(message)
    {
    }
  };
}
