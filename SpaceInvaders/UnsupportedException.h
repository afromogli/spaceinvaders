#pragma once

#include <stdexcept>
#include <string>
#include "String.h"

namespace Common {
   class UnsupportedException : public std::logic_error
   {
   public:
     explicit UnsupportedException(const std::wstring message) : logic_error(Common::to_string(message)) { }
   };
}
