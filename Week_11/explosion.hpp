#pragma once
#include <SFML/Graphics.hpp>

#include <cmath>
#include "entity.hpp"

namespace asteroids
{
    class Explosion : public Entity
    {
    public:
        Explosion(
            Animation& anim, float x, float y, float angle = 0.0f,
            float radius = 1.0f) : Entity(Objects::Explosion, anim, x, y, angle, radius) {}

    private:
        void update_impl() override {}
    };
}
