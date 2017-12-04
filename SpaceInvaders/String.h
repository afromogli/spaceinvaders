#pragma once
#include <algorithm>

namespace Common
{
  static bool ends_with(const std::wstring& value, const std::wstring& ending)
  {
    if (ending.size() > value.size()) return false;
    return equal(ending.rbegin(), ending.rend(), value.rbegin());
  }

  static std::wstring to_lower(std::wstring value)
  {
    transform(value.begin(), value.end(), value.begin(), tolower);
    return value;
  }

  static std::string to_string(std::wstring value)
  {
    return std::string(value.begin(), value.end());
  }
}

