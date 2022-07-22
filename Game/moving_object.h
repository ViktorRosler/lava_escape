
#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H

#include <cmath>

#include "animated_object.h"
#include "level.h"

/**
 * Animated object that can move (abstract)
 */
class Moving_Object : public Animated_Object
{
public:

    /**
     * Create an moving object with a bounding rectangle, a textured shape, and a velocity.
     */
    Moving_Object(sf::FloatRect & rect, sf::Sprite & sprite, sf::Vector2f velocity = sf::Vector2f{0,0});


    /**
     * Move the object and call resolve_collisions.
     */
    Update_Result update(sf::Time const& time, Level & level) override;

    /**
     * Display the object on the screen.
     */
    void draw(sf::RenderWindow & window) override;

protected:
    /**
     * The speed and direction the object is moving in.
     */
    sf::Vector2f velocity;

    /**
     *  Determines if the texture should be flipped horizontally.
     *  false -> face right.
     *  true -> face left.
     */
    bool flip_sprite;

    /**
     *  Handles collisions between moving objects and platforms + window borders.
     */
    virtual void resolve_collisions(std::vector<std::shared_ptr<Game_Object>> collisions) = 0;

private:
    /**
     * Helper function that calculates the distance to another object, to the power of two.
     */
    double pow_dist_to(Game_Object & other) const;

};


#endif
