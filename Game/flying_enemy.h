
#ifndef FLYING_ENEMY_H
#define FLYING_ENEMY_H

#include "enemy.h"

/**
 * Flying enemy type.
 */
class Flying_Enemy : public Enemy
{
public:
    /**
     * Construct a flying enemy using constructor for Enemy.
     */
    using Enemy::Enemy;

    /**
     * Decide what action an enemy should take.
     */
    Update_Result update(sf::Time const& time, Level & level) override;

private:
    /**
     * Determines which frame of an animation will be drawn.
     */
    void animate() override;
};


#endif
