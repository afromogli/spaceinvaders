#pragma once
#include "EInvader.h"

namespace SpaceInvaders
{
  class EMysteryShip : public EInvader
  {
    friend class EntityFactory;
  public:
    void draw(Graphics& graphics) override;

    static Rect2D MysterShipClip;

  protected:
    EMysteryShip(const shared_ptr<Texture> spriteSheet);
  };
}
