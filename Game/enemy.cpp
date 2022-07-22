

#include "enemy.h"

Enemy::Enemy(sf::FloatRect & rect, sf::Sprite & sprite, int health, double move_radius)
: Moving_Object{rect, sprite}, health{health}, move_radius{move_radius},
  start_pos{sf::Vector2f{rect.left, rect.top}},
  time_since_damage{sf::Time{sf::milliseconds(500)}},
  action_timer{sf::Time{}}
{}

Update_Result Enemy::update(sf::Time const& time, Level & level)
{
    // increment timer
    time_since_damage += time;

    // adjust x-velocity if too far away from start position
    if ((velocity.x < 0 && rect.left <= start_pos.x - move_radius - rect.width / 2) ||
            (velocity.x > 0 && rect.left >= start_pos.x + move_radius + rect.width / 2))
    {
        velocity.x = 0;
    }

    // move, then resolve collisions
    Moving_Object::update(time, level);

    if (health <= 0)
    {
        return Update_Result::remove_object;
    }
    return Update_Result::none;
}

void Enemy::resolve_collisions(std::vector<std::shared_ptr<Game_Object>> collisions)
{
    for (size_t i{0}; i < collisions.size(); ++i)
    {
        auto other_ptr{collisions.at(i).get()};
        // collisions with projectiles
        if (dynamic_cast<Projectile*>(other_ptr))
        {
            if (time_since_damage.asMilliseconds() > 350)
            {
                --health;
                time_since_damage = sf::Time{};
            }
            collisions.erase(collisions.begin() + i);
            --i;
        }
        // collisions with player
        else if (dynamic_cast<Player*>(other_ptr))
        {
            collisions.erase(collisions.begin() + i);
            --i;
        }
        // collisions with lava
        else if (dynamic_cast<Lava*>(other_ptr))
        {
            health = 0;

        }
    }

    // collisions with platforms
    Moving_Object::resolve_collisions(collisions);
}

void Enemy::animate()
{
    sf::IntRect texture_rect{sprite.getTextureRect()};

    texture_rect.left = current_frame * 16;

    // flip sprite
    if (flip_sprite)
    {
        texture_rect.left += 16;
        texture_rect.width = - 16;
    }
    else
    {
        texture_rect.width = 16;
    }


    // taking damage effect
    if (health > 0 && time_since_damage.asMilliseconds() < 350)
    {
        if ((time_since_damage.asMilliseconds() / 100) % 2 == 0)
        {
            sprite.setColor(sf::Color{255,80,80});
        }
        else
        {
            sprite.setColor(sf::Color::White);
        }
    }

    sprite.setTextureRect(texture_rect);
}



int Enemy::random_int(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rand);
}