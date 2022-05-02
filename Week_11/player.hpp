#pragma once
#include <SFML/Graphics.hpp>

#include <cmath>
#include "entity.hpp"

namespace asteroids
{
    class Player : public Entity
    {
    public:
        Player(
            Animation& anim, float x, float y, float angle = 0.0f,
            float radius = 1.0f) : Entity(Objects::Player, anim, x, y, angle, radius) {}

        void respawn()
        {
            m_x = m_anim.W / 2;
            m_y = m_anim.H / 2;
            m_angle = 0;
            m_radius = 20;
            --m_lives;
        }

        const bool is_alive() const noexcept
        {
            return m_lives > 0;
        }

        void score_increase()
        {
            ++m_score;
        }

        void set_hit(bool enable)
        {
            m_thrust = enable;
        }

        const bool is_thrust() const noexcept
        {
            return m_thrust;
        }

        const int lives() const noexcept { return m_lives; }
        const int score() const noexcept { return m_score; }

    private:
        static inline const int initial_lives = 3;

        static inline const float max_speed = 15.0f;
        static inline const float motion_slowdown_coefficient = 0.99f;

        void update_impl() override
        {
            if (m_thrust)
            {
                m_dx += std::cos(m_angle * m_anim.deg_to_rad) * 0.2;
                m_dy += std::sin(m_angle * m_anim.deg_to_rad) * 0.2;
            }
            else
            {
                m_dx *= motion_slowdown_coefficient;
                m_dy *= motion_slowdown_coefficient;
            }

            float speed = std::sqrt(m_dx * m_dx + m_dy * m_dy);
            if (speed > max_speed)
            {
                m_dx *= max_speed / speed;
                m_dy *= max_speed / speed;
            }

            move();
            wrap();
        }

        bool m_thrust = false;
        int m_lives = initial_lives;
        int m_score = 0;
    };
}
