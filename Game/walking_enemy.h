

#ifndef WALKING_ENEMY_H
#define WALKING_ENEMY_H

#include "enemy.h"

/**
 * Walking enemy type.
 */
class Walking_Enemy : public Enemy
{
public:
    /**
     * Construct a walking enemy using constructor for Enemy.
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
