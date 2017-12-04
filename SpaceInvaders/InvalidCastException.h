#pragma once
#include <stdexcept>
#include <string>
#include "String.h"

namespace Common {
  class InvalidCastException : public std::logic_error
  {
  public:
    InvalidCastException() : InvalidCastException(L"Null reference exception") { }
    explicit InvalidCastException(const std::wstring message) : logic_error(Common::to_string(message)) { }
  };
}
