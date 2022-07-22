
#ifndef ENEMY_H
#define ENEMY_H

#include <memory>
#include <random>

#include "moving_object.h"
#include "projectile.h"
#include "lava.h"
#include "player.h"

/**
 * Abstract base class for all enemies.
 */
class Enemy : public Moving_Object
{
public:
    /**
     * Create an enemy object with a bounding rectangle, a textured shape, a health value and a .movement radius.
     */
    Enemy(sf::FloatRect & rect, sf::Sprite & sprite, int health, double move_radius);

    /**
     * Keeps an enemy within its radius and calls resolve_collisions.
     */
    Update_Result update(sf::Time const& time, Level & level) override;


protected:

    /**
     * Enemy health.
     * Varies depending on enemy type.
     */
    int health;

    /**
     * Maximum range an enemy can move from its starting position.
     */
    double move_radius;

    /**
     * Start position of an enemy.
     */
    sf::Vector2f start_pos;

    /**
     * Time since the enemy took damage.
     */
    sf::Time time_since_damage;

    /**
     * Time since the enemy
     */
    sf::Time action_timer;

    /**
     * Helper function that returns a random integer between min and max, inclusive.
     */
    int random_int(int min, int max);

    /**
     * Determines which frame of an animation will be drawn.
     */
    void animate() override;

private:
    /**
     * Random device used to generate random numbers.
     */
    std::random_device rand;

    /**
     * Handles collisions between an enemy and other moving objects,
     *  then handle collisions between enemy and platforms + window borders.
     */
    void resolve_collisions(std::vector<std::shared_ptr<Game_Object>> collisions) override;


};


#endif
