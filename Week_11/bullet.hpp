#pragma once
#include <SFML/Graphics.hpp>

#include <cmath>
#include "entity.hpp"

namespace asteroids
{
    class Bullet : public Entity
    {
    public:
        Bullet(
            Animation& anim, float x, float y, float angle = 0.0f,
            float radius = 1.0f) : Entity(Objects::Bullet, anim, x, y, angle, radius) {}

    private:
        void update_impl() override
        {
            m_dx = std::cos(m_angle * m_anim.deg_to_rad) * 5;
            m_dy = std::sin(m_angle * m_anim.deg_to_rad) * 5;
            move();

            if (is_out_of_bounds())
            {
                die();
            }
        }
    };
}