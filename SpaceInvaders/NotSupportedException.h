#pragma once

#include <stdexcept>
#include <string>

namespace Common {
   class NotSupportedException : public std::logic_error
   {
   public:
     explicit NotSupportedException(std::string message) : logic_error(message) { };
   };
}
