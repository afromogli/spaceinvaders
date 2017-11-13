#pragma once
#include <SDL.h>
#include "Entity.h"
#include "Font.h"

namespace Common
{
   class Text : public Object
   {
   public:
      Text(const string text, const Color color, const Vector2f position, const int totalTextWidth, const int totalTextHeight, Font& font, Graphics& graphics);
      ~Text();

      void update(const float& deltaTime) override;
      void draw(Graphics& graphics) override;

   private:
      static SDL_Texture* createTexture(Graphics& graphics, const Font& font, const string text, const Color color);
   
      string m_text;
      Color m_color;

      SDL_Rect m_rect;
      SDL_Texture* m_texture;
      Font& m_font;
      Graphics& m_graphics;
   };
}
