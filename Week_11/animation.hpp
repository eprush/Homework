#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace asteroids
{
    class Animation
    {
    public:
        Animation() = default;

        Animation(
            sf::Texture& t, int x, int y, int w, int h, int count, float speed) :
            m_speed(speed)
        {
            for (auto i = 0; i < count; ++i)
            {
                m_frames.emplace_back(x + i * w, y, w, h);
            }

            m_sprite.setTexture(t);
            m_sprite.setOrigin(w * 1.0f / 2, h * 1.0f / 2);
            m_sprite.setTextureRect(m_frames[0]);
        }

        void update()
        {
            m_frame += m_speed;

            auto n = m_frames.size() * 1.0f;
            if (m_frame >= n)
            {
                m_frame -= n;
            }

            if (!m_frames.empty())
            {
                m_sprite.setTextureRect(m_frames[static_cast<std::size_t>(m_frame)]);
            }
        }

        const bool is_end() const noexcept
        {
            return m_frame + m_speed >= m_frames.size() * 1.0f;
        }

        const sf::Sprite& sprite() const noexcept { return m_sprite; }

    public:
        static inline const auto W = sf::VideoMode::getDesktopMode().width;
        static inline const auto H = sf::VideoMode::getDesktopMode().height;

        static inline const auto deg_to_rad = 0.017453f;

    private:
        float m_frame = 0.0;
        float m_speed = 0.0;
        std::vector< sf::Rect<int> > m_frames;
        sf::Sprite m_sprite;
    };
}

