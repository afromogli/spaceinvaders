#pragma once
#include <stdexcept>
#include <string>

namespace Common {
  class InvalidCastException : public std::logic_error
  {
  public:
    InvalidCastException() : InvalidCastException("Null reference exception") { }
    explicit InvalidCastException(const std::string message) : logic_error(message) { }
  };
}
