#pragma once

#include <SDL.h>

#include "Vector2.h"
#include "Color.h"
#include "Rect2d.h"

using namespace std;

namespace Common {
  class Graphics {
  public:
    Graphics(const int& xWinPosition, const int& yWinPosition, const int& width, const int& height);
    ~Graphics();

    void startFrame() const;
    void endFrame() const;

    SDL_Renderer* getRenderer() const;

    SDL_Texture* loadTexture(const std::string &str) const;

    void drawFilledCircle(const Vector2f position, const int diameter, const Color color) const;
    void drawFilledRoundedBox(const Rect2D rect, const int borderRadius, const Color color) const;
    void drawFilledBox(const Rect2D rect, const Color color) const;
    
    /**
     * @brief Sets the SDL2 SDL_HINT_RENDER_SCALE_QUALITY flag. 
     * 0 or nearest means nearest pixel sampling. 
     * 1 means linear interpolation.
     * 2 is anistropic (only supported if the app runs on D3D/Windows).
     * 
     * @param value The render scale quality value. 
     */
    static void setRenderScaleQuality(char* value);
  private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Rect m_windowRect;

    bool initEverything();
    static bool initSDL();
    bool createWindow();
    bool createRenderer();
    void setupRenderer() const;
  };

}

