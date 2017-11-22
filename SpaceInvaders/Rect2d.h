#pragma once

#include "Vector2.h"

namespace Common {
  class Rect2D {
  public:
    Rect2D() : Rect2D(Vector2f(0.f, 0.f), 0, 0) {
    }

    Rect2D(const Vector2f position, const int width, const int height) : m_width{ width }, m_height{ height }, m_position{ position } {
    }

    Rect2D(const Rect2D& other) : m_width{ other.getWidth() }, m_height{ other.getHeight() }, m_position{ other.getPosition() } {
    }

    bool intersects(const Rect2D& otherBBox) const;

    const Vector2f& getPosition() const {
      return m_position;
    }

    void setPosition(const Vector2f& position) {
      m_position = position;
    }

    int getWidth() const {
      return m_width;
    }

    int getHeight() const {
      return m_height;
    }

    void setSize(const int width, const int height)
    {
      m_width = width;
      m_height = height;
    }

    void setSize(const Vector2f size)
    {
      m_width = int(size.x);
      m_height = int(size.y);
    }

    Vector2f getCenter() const;

  private:
    int m_width;
    int m_height;
    // The position is treated as the upper left corner of the bounding box
    Vector2f m_position;
  };
}
