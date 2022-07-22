

#ifndef LEVEL_H
#define LEVEL_H

#include <set>
#include <memory>
#include <SFML/Graphics.hpp>

#include "game_object.h"
#include "constants.h"

/**
 * Specifies the result of an update function call.
 */
enum class Update_Result : int
{
    none, remove_object, level_complete, game_over
};

/*
 * A level in the game.
 */
class Level
{
public:
     /**
      * Create a level consisting of the given objects.
      */
    Level(std::multiset<std::pair<int, std::shared_ptr<Game_Object>>> & game_objects, sf::Vector2f & player_pos);


    /**
     * Update each object in a level based on time passed.
     *
     * Return value notifies Game_State if the player has completed or failed the level.
     */
    Update_Result update(sf::Time time);

    /**
     * Draw a level to the screen.
     */
    void draw(sf::RenderWindow & window) const;

    /**
     * Returns every object in a level that the parameter obj is colliding with.
     */
    std::vector<std::shared_ptr<Game_Object>> get_collisions(Game_Object & obj) const;

    /**
     * Add an object to the level.
     *
     * Used to add a projectile to the level when a player/enemy shoots.
     */
    void add_object(std::shared_ptr<Game_Object> obj, int draw_priority);

    /**
     * Determines if the lava in the level is rising.
     */
    bool rising_lava;

    /**
     * Position of the player.
     *
     * Used to update the window view after drawing.
     */
    sf::Vector2f player_pos;
private:

    /**
     * Every object in the level paired with its draw priority.
     *
     * Objects with a higher priority are drawn in front of objects with a lower priority.
     *
     * Sorted by priority, low -> high.
     */
    std::multiset<std::pair<int, std::shared_ptr<Game_Object>>> game_objects;
};


#endif
