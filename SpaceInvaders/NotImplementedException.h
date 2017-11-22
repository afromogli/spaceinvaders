#pragma once

#include <stdexcept>

namespace Common {
   class NotImplementedException : public std::logic_error
   {
   public:
      NotImplementedException() : logic_error("Function not yet implemented") { };
   };
}

