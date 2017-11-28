#pragma once
#include "ECannon.h"

namespace SpaceInvaders
{
  /**
   * @brief Represents a life in UI, therefore it inherets ECannon since it is the same graphics.
   */
  class ELife : public ECannon
  {
  public:
    explicit ELife(const shared_ptr<Texture>& spriteSheet)
      : ECannon(spriteSheet)
    {
    }

    void draw(Graphics& graphics) override;
    static constexpr float CannonAsLifeScale = 1.3f;    
  };
}
