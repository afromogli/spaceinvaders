#include "Texture.h"
#include <SDL_image.h>
#include "String.h"

namespace Common
{
  Texture::Texture(Graphics& graphics) : m_graphics{ graphics }, m_isLoaded{ false }
  {
    //Initialize
    m_texture = nullptr;
    m_width = 0;
    m_height = 0;
  }

  Texture::~Texture()
  {
    //Deallocate
    free();
  }

  bool Texture::loadFromFile(std::wstring path)
  {
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = nullptr;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(std::string(path.begin(), path.end()).c_str());
    if (loadedSurface == nullptr)
    {
      printf("Unable to load image %ls! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
      //Color key image
      // Png:s have own alpha channel so don't need to set color key (transparent pixel)
      if (ends_with(to_lower(path), L".png") == false)
      {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
      }

      //Create texture from surface pixels
      newTexture = SDL_CreateTextureFromSurface(m_graphics.getRenderer(), loadedSurface);
      if (newTexture == nullptr)
      {
        printf("Unable to create texture from %ws! SDL Error: %s\n", path.c_str(), SDL_GetError());
      }
      else
      {
        //Get image dimensions
        m_width = loadedSurface->w;
        m_height = loadedSurface->h;
      }

      //Get rid of old loaded surface
      SDL_FreeSurface(loadedSurface);
    }
    //Return success
    m_texture = newTexture;

    m_isLoaded = m_texture != nullptr;

    return m_isLoaded;
  }

  void Texture::free()
  {
    //Free texture if it exists
    if (m_texture != nullptr)
    {
      SDL_DestroyTexture(m_texture);
      m_texture = nullptr;
      m_width = 0;
      m_height = 0;
    }
  }

  void Texture::render(const Vector2f position, const Rect2D& clip, const float scale) const
  {
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { int(position.x), int(position.y), int(clip.getWidth()*scale), int(clip.getHeight()*scale) };

    //Set clip rendering dimensions
    SDL_Rect sdlClip = { int(clip.getPosition().x), int(clip.getPosition().y), clip.getWidth(), clip.getHeight() };
    //Render to screen
    SDL_RenderCopy(m_graphics.getRenderer(), m_texture, &sdlClip, &renderQuad);
  }

  void Texture::render(const Vector2f position, const float scale) const
  {
    // Set rendering space and render to screen
    SDL_Rect renderQuad = { int(position.x), int(position.y), int(m_width*scale), int(m_height*scale) };
    // Render to screen
    SDL_RenderCopy(m_graphics.getRenderer(), m_texture, nullptr, &renderQuad);
  }

  int Texture::getWidth() const
  {
    return m_width;
  }

  int Texture::getHeight() const
  {
    return m_height;
  }

  bool Texture::isLoaded() const
  {
    return m_isLoaded;
  }
}
