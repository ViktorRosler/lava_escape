
#include "animated_object.h"

Animated_Object::Animated_Object(sf::FloatRect & rect, sf::Sprite & sprite, int frame)
        : Textured_Object{rect, sprite}, animation_timer{sf::Time{}},
          current_frame{frame}
{}

Update_Result Animated_Object::update(const sf::Time & time, Level &)
{
    animation_timer += time;

    return Update_Result::none;
}

void Animated_Object::draw(sf::RenderWindow &window)
{
    animate();

    Textured_Object::draw(window);
}

void Animated_Object::animate()
{
    if (animation_timer.asMilliseconds() >=  250)
    {
        ++current_frame %= 3;
        animation_timer = sf::Time{};
    }

    sf::IntRect texture_rect{sprite.getTextureRect()};
    texture_rect.left = current_frame * 16;
    sprite.setTextureRect(texture_rect);
}