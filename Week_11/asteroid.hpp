#pragma once
#include <SFML/Graphics.hpp>

#include <random>
#include <ctime>

#include "animation.hpp"
#include "entity.hpp"

namespace asteroids
{
    class Asteroid : public Entity
    {
    public:
        Asteroid(
            Animation& anim, float x, float y, float angle = 0.0f,
            float radius = m_size * 1.0f) : Entity(Objects::Asteroid, anim, x, y, angle, radius)
        {
            m_dx = m_urd(m_engine);
            m_dy = m_urd(m_engine);
        }

        static inline const int m_size = 16;

    private:
        static inline std::uniform_real_distribution<float> m_urd = std::uniform_real_distribution<float>(-4, 4);
        static inline std::default_random_engine m_engine = std::default_random_engine(0);

    private:
        void update_impl() override
        {
            move();
            wrap();
        }
    };
}


