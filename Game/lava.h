

#ifndef LAVA_H
#define LAVA_H

#include "animated_object.h"
#include "level.h"

/**
 * Animated lava flow that follows the player character up through a level.
 * Kills the player on touch.
 */
class Lava : public Animated_Object
{
public:
    /**
     * Create a lava object with a bounding rectangle, a textured shape,
     * and a boolean that determines if the lava is animated.
     */
    Lava(sf::FloatRect & rect, sf::Sprite & sprite, bool animated);

    /**
     * Raise the lava level, if it is active.
     */
    Update_Result update(sf::Time const& time, Level & level) override;

private:

    /**
     * Time since the lava was activated.
     * Used to slow down the lava at the start.
     */
    sf::Time active;

    /**
     * Determines if a lava object should be animated.
     */
    bool const animated;

    /**
     * Determines which frame of an animation will be drawn.
     */
    void animate() override;
};


#endif

