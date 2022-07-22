

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "moving_object.h"

/**
 * A projectile that is created when the player or an enemy fire.
 */
class Projectile : public Moving_Object
{
public:
    /**
     * Create a projectile object with a bounding rectangle, a textured shape, and a velocity.
     */
    Projectile(sf::FloatRect & rect, sf::Sprite & sprite, sf::Vector2f velocity);

    /**
     * Move or remove the projectile.
     */
    Update_Result update(sf::Time const& time, Level & level) override;

private:
    /**
     * Indicates if the projectile is about to be removed, after displaying a projectile hit frame.
     */
    bool remove;

    /**
     * Timer for how long since a projectile was set to be removed.
     */
    sf::Time remove_timer;

    /*
     * Resolve collisions with window borders and all objects.
     */
    void resolve_collisions(std::vector<std::shared_ptr<Game_Object>> collisions) override;

    /**
     * Determines which frame of an animation will be drawn.
     */
    void animate() override;
};


#endif
