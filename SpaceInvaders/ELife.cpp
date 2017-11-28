#include "ELife.h"

namespace SpaceInvaders
{
  void ELife::draw(Graphics& graphics)
  {
    m_spriteSheet->render(getPosition(), CannonClip, CannonAsLifeScale);
  }
}
