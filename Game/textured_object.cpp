

#include "textured_object.h"
#include "level.h"

Textured_Object::Textured_Object(sf::FloatRect & rect, sf::Sprite & sprite)
: Game_Object{rect}, sprite{sprite}
{}


Update_Result Textured_Object::update(sf::Time const&, Level &)
{
    return Update_Result::none;
}

void Textured_Object::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}