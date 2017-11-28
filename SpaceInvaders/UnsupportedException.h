#pragma once

#include <stdexcept>
#include <string>

namespace Common {
   class UnsupportedException : public std::logic_error
   {
   public:
     explicit UnsupportedException(std::string message) : logic_error(message) { };
   };
}
