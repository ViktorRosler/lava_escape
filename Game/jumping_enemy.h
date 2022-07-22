
#ifndef JUMPING_ENEMY_H
#define JUMPING_ENEMY_H

#include "enemy.h"

/**
 * Jumping enemy type.
 */
class Jumping_Enemy : public Enemy
{
public:
    /**
     * Construct a jumping enemy using constructor for Enemy.
     */
    using Enemy::Enemy;

    /**
     * Decide what action an enemy should take.
     */
    Update_Result update(sf::Time const& time, Level & level) override;

private:
    /**
     * Time since last time the enemy fired a projectile.
     */
    sf::Time time_since_fire;

    /**
     * Determines which frame of an animation will be drawn.
     */
    void animate() override;

    /**
     * Fire a projectile.
     *  false -> fire left.
     *  true -> fire right.
     */
    void fire(Level &level, bool direction);


};


#endif
