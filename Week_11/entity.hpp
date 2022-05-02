#pragma once
#include <SFML/Graphics.hpp>

#include "animation.hpp"
#include <string>

namespace asteroids
{
    enum class Objects
    {
        Asteroid,
        Bullet,
        Player,
        Explosion
    };
}

namespace asteroids
{
    class Entity
    {
    public:
        Entity(
            Objects name,
            Animation& anim, float x, float y, float angle = 0.0f,
            float radius = 1.0f) :
            m_anim(anim), m_x(x), m_y(y), m_angle(angle), m_radius(radius),
            m_name(name) {}

        virtual const bool is_alive() const noexcept
        {
            return m_is_alive;
        }

        void die() noexcept
        {
            m_is_alive = false;
        }

        void rotate_by_deg(float angle) noexcept
        {
            m_angle += angle;
        }

        void update()
        {
            update_impl();
            m_anim.update();
        }

        void draw(sf::RenderWindow& app)
        {
            auto sprite = m_anim.sprite();
            sprite.setPosition(m_x, m_y);
            sprite.setRotation(m_angle + 90);

            app.draw(sprite);
        }

        virtual ~Entity() = default;

    public:
        float x() const noexcept { return m_x; }
        float y() const noexcept { return m_y; }
        float angle() const noexcept { return m_angle; }
        float radius() const noexcept { return m_radius; }
        const Objects& name() const noexcept { return m_name; }

        const Animation& anim() const noexcept { return m_anim; }
        Animation& anim() { return m_anim; }

    protected:
        void move()
        {
            m_x += m_dx;
            m_y += m_dy;
        }

        void wrap()
        {
            if (m_x > m_anim.W * 1.0f) { m_x = 0; }
            if (m_x < 0.0) { m_x = m_anim.W * 1.0f; }
            if (m_y > m_anim.H * 1.0f) { m_y = 0; }
            if (m_y < 0.0) { m_y = m_anim.H * 1.0f; }
        }

        bool is_out_of_bounds() const
        {
            return m_x > m_anim.W || m_x < 0.0 || m_y > m_anim.H || m_y < 0.0;
        }

    protected:
        Animation m_anim;

        float m_x;
        float m_y;
        float m_radius;
        float m_angle;
        float m_dx = 0.0;
        float m_dy = 0.0;

        bool m_is_alive = true;
        Objects m_name;
    private:
        virtual void update_impl() = 0;
    };
}


namespace asteroids
{
    bool collide(const Entity& a, const Entity& b)
    {
        return (b.x() - a.x()) * (b.x() - a.x()) + (b.y() - a.y()) * (b.y() - a.y()) <
            (a.radius() + b.radius()) * (a.radius() + b.radius());
    }
}
