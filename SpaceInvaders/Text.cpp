#include "Text.h"
#include <SDL_ttf.h>
#include "String.h"

namespace Common
{
  Text::Text(const wstring text, const Color color, const Vector2f position, const int charWidth,
    const int charHeight, Font& font, Graphics& graphics) :
    m_text{ text },
    m_color{ color },
    m_charWidth{ charWidth },
    m_charHeight{ charHeight },
    m_texture{ nullptr },
    m_font{ font },
    m_graphics{ graphics }
  {
    m_rect.x = int(position.x);
    m_rect.y = int(position.y);
    m_rect.w = m_charWidth * text.length();
    m_rect.h = m_charHeight;
    m_texture = createTexture(graphics, m_font, m_text, m_color);
  }

  Text::~Text()
  {
    SDL_DestroyTexture(m_texture);
  }

  void Text::update(const float& deltaTime)
  {
  }

  void Text::draw(Graphics& graphics)
  {
    SDL_RenderCopy(graphics.getRenderer(), m_texture, nullptr, &m_rect);
  }

  void Text::setText(const wstring newText)
  {
    if (m_texture != nullptr)
    {
      SDL_DestroyTexture(m_texture);
    }
    m_text = newText;
    m_rect.w = newText.length() * m_charWidth;
    m_texture = createTexture(m_graphics, m_font, m_text, m_color);
  }

  Vector2f Text::getPosition() const
  {
    return Vector2f(float(m_rect.x), float(m_rect.y));
  }

  float Text::getWidth() const
  {
    return float(m_rect.w);
  }

  SDL_Texture* Text::createTexture(Graphics& graphics, const Font& font, const wstring text, const Color color)
  {
    SDL_Surface *surface = TTF_RenderText_Solid(font.get(), to_string(text).c_str(), { color.R, color.G, color.B, color.A });
    SDL_Texture* texture = SDL_CreateTextureFromSurface(graphics.getRenderer(), surface);
    SDL_FreeSurface(surface);
    return texture;
  }
}
