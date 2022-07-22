
#include "projectile.h"

Projectile::Projectile(sf::FloatRect & rect, sf::Sprite & sprite, sf::Vector2f velocity)
: Moving_Object{rect, sprite, velocity}, remove{false}, remove_timer{sf::Time{}}
{}

Update_Result Projectile::update(sf::Time const& time, Level & level)
{
    Moving_Object::update(time, level);
    if(remove)
    {
        remove_timer += time;
        if (remove_timer.asMilliseconds() > 50)
        {
            return Update_Result::remove_object;
        }
    }
    return Update_Result::none;
}

void Projectile::resolve_collisions(std::vector<std::shared_ptr<Game_Object>> collisions)
{
    // out of bounds
    if (rect.left < -10 || rect.left > constants::window_width + 10)
    {
        remove = true;
    }

    // collision with objects
    if (!collisions.empty())
    {
        velocity.x = 0;
        remove = true;
    }
}

void Projectile::animate()
{
    if (animation_timer.asMilliseconds() > 50)
    {
        ++current_frame %= 3;
        animation_timer = sf::Time{};
    }

    sprite.setPosition(rect.left - 12, rect.top - 12);
    sf::IntRect texture_rect{sf::IntRect{0,15 * 16,16, 16}};
    if (remove)
    {
        texture_rect.left = 48;
    }
    else if (velocity.x > 0)
    {
        texture_rect.left = 16 * current_frame;
    }
    else
    {
        texture_rect.width = -16;
        texture_rect.left = 16 * (current_frame + 1);
    }

    sprite.setTextureRect(texture_rect);
}