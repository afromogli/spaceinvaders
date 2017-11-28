#pragma once
#include <SDL.h>
#include "Entity.h"
#include "Font.h"

namespace Common
{
   class Text : public Object
   {
   public:
      Text(const string text, const Color color, const Vector2f position, const int charWidth, const int charHeight, Font& font, Graphics& graphics);
      ~Text();

      void update(const float& deltaTime) override;
      void draw(Graphics& graphics) override;

     /**
       * @brief Sets new text
       * @param newText The new text
       */
      void setText(const string newText);

   private:
      static SDL_Texture* createTexture(Graphics& graphics, const Font& font, const string text, const Color color);
   
      string m_text;
      Color m_color;
      int m_charWidth;
      int m_charHeight;

      SDL_Rect m_rect;
      SDL_Texture* m_texture;
      Font& m_font;
      Graphics& m_graphics;
   };
}
