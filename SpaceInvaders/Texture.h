#pragma once

#include <string>
#include <SDL.h>

#include "Graphics.h"

namespace Common
{
  /*
   * @brief SDL Texture wrapper class, supports sprite (and spritesheet) rendering.
   * Stolen with pride from lazyfoo.net's "Clip Rendering and Sprite Sheets" tutorial. Cudos to LazyFoo for sharing.
   */
  class Texture
  {
  public:
    explicit Texture(Graphics& graphics);

    /**
     * @brief Deallocates memory
     */
    ~Texture();

    /**
     * @brief Loads image at specified path
     * @param path The path to the texture file
     */
    bool loadFromFile(std::wstring path);

    /** 
     * @brief Renders texture at given point and only the part that is is defined by the clip param.
     * @param position The texture position
     * @param clip The rectangle that defines which part (sprite) of the texture to draw
     * @param scale The scale of the texture, defaults to 1.0f (no scaling)
     */
    void render(const Vector2f position, const Rect2D& clip, const float scale = 1.f) const;
    
    /** 
     * @brief Renders texture at given point
     */
    void render(const Vector2f position, const float scale = 1.f) const;

    int getWidth() const;
    int getHeight() const;

    bool isLoaded() const;

  private:
    //Deallocates texture
    void free();

    Graphics& m_graphics;
    //The actual hardware texture
    SDL_Texture* m_texture;

    //Image dimensions
    int m_width;
    int m_height;

    bool m_isLoaded;
  };
}
