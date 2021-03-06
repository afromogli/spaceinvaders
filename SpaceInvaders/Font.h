#pragma once
#include <string>
#include <SDL_ttf.h>

namespace Common
{
  class Font
  {
  public:
    Font(std::wstring fontFilePath, const int pointSize);
    ~Font();

    TTF_Font* get() const;
  private:
    TTF_Font *m_font;
  };
}
