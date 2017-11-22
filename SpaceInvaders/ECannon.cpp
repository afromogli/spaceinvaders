#include "ECannon.h"
#include "GameConfig.h"


namespace SpaceInvaders
{
  ECannon::ECannon(const shared_ptr<Texture> spriteSheet) : Entity(), m_spriteSheet{ spriteSheet }
  {
    m_rect.setSize(int(GameConfig::CannonSize.x), int(GameConfig::CannonSize.y));
  }

  void ECannon::update(const float & deltaTime)
  {
    const float deltaSeconds = deltaTime / 1000;
    const Vector2f nextPosition = getPosition() + m_velocity*deltaSeconds;
    if ((nextPosition.y) > 0 && (nextPosition.y + m_rect.getHeight()) < GameConfig::WinSize.y) {
      setPosition(nextPosition);
    }
  }

  void ECannon::draw(Graphics& graphics)
  {
    m_spriteSheet->render(getPosition(), CannonClip, GameConfig::SpriteScale);
  }

  Rect2D ECannon::CannonClip = Rect2D(Vector2f(277, 21), 26, 16);

  //bool EPaddle::isColliding(const EBall& ball) const
  //{
  //   return m_rect.intersects(ball.getRect());
  //}

  //void EPaddle::doBallCollision(EBall& ball) const
  //{
  //   const Vector2f& ballCenterPos = ball.getRect().getCenter();
  //   // Collision from top
  //   if (ballCenterPos.x >= getPosition().x && ballCenterPos.x <= getPosition().x + getRect().getWidth() )
  //   {
  //      const float relativeIntersectX = getRect().getCenter().x - ball.getPosition().x;
  //      const float normalizedRelativeIntersectionX = (relativeIntersectX / (getRect().getWidth() / 2));
  //      const float bounceAngle = normalizedRelativeIntersectionX * EBall::Maxbounceangle * float(PI) / 180.0f;

  //      const float currentBallSpeed = GameConfig::BallSpeed;
  //      const float ballVy = currentBallSpeed*cos(bounceAngle)*-1;
  //      const float ballVx = currentBallSpeed*sin(bounceAngle)*-1;

  //      ball.setVelocity(Vector2f(ballVx, ballVy));
  //   }
  //   // Collision on sides
  //   else
  //   {
  //      ball.setVelocity(Vector2f(-1*ball.getVelocity().x, ball.getVelocity().y));
  //   }
  //       
  //}
}