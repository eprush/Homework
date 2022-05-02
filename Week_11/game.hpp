#pragma once
#include "animation.hpp"
#include "asteroid.hpp"
#include "bullet.hpp"
#include "explosion.hpp"
#include "player.hpp"

#include <iostream>
#include <memory>
#include <list>

namespace asteroids
{
    class Game
    {
    public:
        explicit Game() : app(sf::VideoMode(m_rock.W, m_rock.H), title)
        {
            init_app();
            init_texts();
            load_visuals();
        }

        void run()
        {
            init_game();
            game_loop();
        }

    private:
        void init_game()
        {
            for (auto i = 0; i < initial_asteroids; ++i)
            {
                entities.push_back(std::make_shared<Asteroid>(
                    m_rock, rand() % m_rock.W, rand() % m_rock.H, rand() % 360, 25));
            }

            p = std::make_shared<Player>(m_player, 200, 200, 0, 20);
            entities.push_back(p);

            text.setString("score: " + std::to_string(p->score()) + "\nLifes: "
                + std::to_string(p->lives()));
        }

        void init_app()
        {
            app.setFramerateLimit(60);
        }

        void init_texts()
        {
            text.setCharacterSize(character_size);
            text.setFillColor(sf::Color::Red);
        }

        void game_loop()
        {
            while (app.isOpen() && p->is_alive()) {
                poll_events();
                position();
                process_collisions();
                thrust();
                update_explosions();
                spawn_new_asteroids();
                remove_dead_entities();
                redraw();
            }
        }

        void poll_events()
        {
            sf::Event event;
            while (app.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    app.close();
                }

                if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Space)
                {
                    bullet();
                }
            }
        }

        void position()
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                p->rotate_by_deg(3);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                p->rotate_by_deg(-3);
            }
            p->set_hit(sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
        }

        void process_collisions()
        {
            for (const auto& a : entities)
            {
                for (const auto& b : entities)
                {
                    if (a->name() == Objects::Asteroid && b->name() == Objects::Bullet
                        && collide(*a, *b))
                    {
                        a->die();
                        b->die();

                        for (auto i = 0; i < 2; i++)
                        {
                            if (a->radius() == std::dynamic_pointer_cast<Asteroid>(a) -> m_size)
                            {
                                continue;
                            }
                            auto e = std::make_shared<Asteroid>(
                                m_small_rock, a->x(), a->y(), rand() % 360, std::dynamic_pointer_cast<Asteroid>(a) -> m_size);
                            entities.push_back(e);
                        }

                        p->score_increase();
                    }

                    if (a->name() == Objects::Player && b->name() == Objects::Asteroid
                        && collide(*a, *b))
                    {
                        b->die();

                        p->respawn();
                    }
                }
            }
        }

        void thrust()
        {
            if (p->is_thrust())
            {
                p->anim() = m_go_player;
            }
            else
            {
                p->anim() = m_player;
            }
        }

        void bullet()
        {
            auto b = std::make_shared<Bullet>(m_bullet, p->x(), p->y(), p->angle(), 10);
            entities.push_back(b);
        }

        void update_explosions()
        {
            for (const auto& e : entities)
            {
                if (e->name() == Objects::Explosion)
                {
                    if (e->anim().is_end())
                    {
                        e->die();
                    }
                }
            }
        }

        void remove_dead_entities()
        {
            for (auto it = std::begin(entities); it != std::end(entities);)
            {
                (*it)->update();

                if (!(*it)->is_alive())
                {
                    it = entities.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }

        void spawn_new_asteroids()

        {
            std::default_random_engine engine(0);
            std::uniform_int_distribution uid;
            if (!(uid(engine) % 150))
            {
                auto a = std::make_shared<Asteroid>(
                    m_rock, 0, uid(engine) % m_rock.H, uid(engine) % 360, 25);
                entities.push_back(a);
            }
        }

        void load_visuals() //throw std::logic_error
        {

            if (!t1.loadFromFile("images/spaceship.png")
                || !t2.loadFromFile("images/space.jpg")
                || !t3.loadFromFile("images/explosions.png")
                || !t4.loadFromFile("images/rock.jpg")
                || !t6.loadFromFile("images/small_rock.png")
                )
            {
                throw std::logic_error("File could not be loaded");
            }
            

            t1.loadFromFile("images/spaceship.png");
            t2.loadFromFile("images/space.jpg");
            t3.loadFromFile("images/explosions.png");
            t4.loadFromFile("images/rock.jpg");
            t5.loadFromFile("images/fire.png");
            t6.loadFromFile("images/small_rock.png");

            t1.setSmooth(true);
            t2.setSmooth(true);

            m_sprite.setTexture(t2);

            m_explosion = Animation(t3, 0, 0, 256, 256, 48, 0.5);
            m_rock = Animation(t4, 0, 0, 64, 64, 16, 0.5);
            m_small_rock = Animation(t6, 0, 0, 64, 64, 16, 0.2);
            m_bullet = Animation(t5, 0, 0, 32, 64, 16, 1);
            m_player = Animation(t1, 40, 0, 40, 40, 2, 0);
            m_go_player = Animation(t1, 40, 40, 40, 40, 1, 0);
        }

        void redraw()
        {
            app.draw(m_sprite);
            for (const auto& i : entities)
            {
                i->draw(app);
            }
            app.display();
        }

    private:
        static inline const std::string title = "Asteroids!";
        static inline const int initial_asteroids = 10;
        static inline const int character_size = 25;

        sf::Text text;

        sf::RenderWindow app;

        sf::Texture t1, t2, t3, t4, t5, t6;

        sf::Sprite m_sprite;

        Animation m_explosion, m_rock, m_small_rock, m_bullet, m_player, m_go_player;

        std::shared_ptr<Player> p;

        std::list< std::shared_ptr<Entity> > entities;
    };
}
