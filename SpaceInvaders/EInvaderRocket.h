#pragma once
#include <memory>
#include "ECannonRocket.h"

using namespace Common;

namespace SpaceInvaders
{
  class EInvaderRocket : public ECannonRocket
  {
    friend class EntityFactory;
  public:
    void draw(Graphics& graphics) override;
  
  private:
    EInvaderRocket(const shared_ptr<Texture> spriteSheet);

    bool isOutOfView() const override;

    const shared_ptr<Texture> m_spriteSheet;

    static Rect2D InvaderRocketClip;
  };
}
