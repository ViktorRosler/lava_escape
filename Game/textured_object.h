
#ifndef TEXTURED_OBJECT_H
#define TEXTURED_OBJECT_H

#include <SFML/Graphics.hpp>

#include "game_object.h"

/**
 * An game object with a texture.
 */
class Textured_Object : public Game_Object
{
public:
    /**
     * Create a textured object with a bounding rectangle and a textured shape.
     */
    Textured_Object(sf::FloatRect & rect, sf::Sprite & shape);

    /**
     * Default destructor.
     */
    ~Textured_Object() = default;

    /**
     * Update the state of an object over time.
     * Empty implementation for derived classes to override.
     */
    Update_Result update(sf::Time const& time, Level & level) override;

    /**
     * Draw a textured object to the screen.
     */
    void draw(sf::RenderWindow & window) override;

protected:
    /**
     * Textured sprite used to draw an object.
     */
    sf::Sprite sprite;
};


#endif
