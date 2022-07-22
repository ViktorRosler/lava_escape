

#include "lava.h"

Lava::Lava(sf::FloatRect & rect, sf::Sprite & sprite, bool animated)
: Animated_Object{rect, sprite}, active{sf::Time{}}, animated{animated}
{}

Update_Result Lava::update(sf::Time const& time, Level & level)
{

    if (level.rising_lava)
    {
        active += time;
        rect.top -= 0.1 * time.asMilliseconds() * std::min(active.asSeconds(), 2.0f);
    }
    Animated_Object::update(time, level);

    return Update_Result::none;
}


void Lava::animate()
{
    sprite.setPosition(rect.left, rect.top - 24);
    if (animated)
    {
        if (animation_timer.asMilliseconds() >=  250)
        {
            ++current_frame %= 6;
            animation_timer = sf::Time{};
        }

        sf::IntRect texture_rect{sprite.getTextureRect()};
        texture_rect.left = current_frame * 32;
        sprite.setTextureRect(texture_rect);
    }
}