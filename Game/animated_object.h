

#ifndef ANIMATED_OBJECT_H
#define ANIMATED_OBJECT_H

#include "textured_object.h"
#include "level.h"

/**
 * A textured object that is animated.
 */
class Animated_Object : public Textured_Object
{
public:
    /**
     * Create an animated object with a bounding rectangle, and a textured shape.
     */
    Animated_Object(sf::FloatRect & rect, sf::Sprite & sprite, int frame = 0);

    /**
     * Advance the animation timer.
     */
    Update_Result update(sf::Time const& time, Level & level) override;

    /**
     * Animate then draw.
     */
    void draw(sf::RenderWindow & window) override;



protected:
    /**
     * Time since an animation updated.
     */
    sf::Time animation_timer;

    /**
     * The current frame of an animation.
     */
    int current_frame;

    /**
     * Determines which frame of an animation will be drawn.
     */
    virtual void animate();
};


#endif
