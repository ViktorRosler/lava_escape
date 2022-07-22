

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "state.h"
#include "menu_state.h"
#include "level.h"
#include "level_loader.h"


/**
 * A state class that represents the program being in-game.
 */
class Game_State : public State
{
public:
    /**
     * Constructor that loads a level.
     */
    Game_State(std::string const& level_name);

    /**
     *  Default destructor.
     */
    ~Game_State() = default;

    /**
     * Handles user keyboard- and button presses.
     * May result in a state change between Game_State and Menu_State.
     */
    std::shared_ptr<State> take_user_input() override;

    /**
     * Called to update a Game_State.
     */
    std::shared_ptr<State> update(sf::Time time) override;

    /**
     * Called to draw a Game_State to the screen.
     */
    void draw(sf::RenderWindow & window) override;

    /**
     * Returns the name of the level in a Game_State.
     */
    std::string get_level_name() const;
private:
    /**
     *  The level being played.
     */
    std::shared_ptr<Level> level;

    /**
     * The name of the level being played.
     */
    std::string level_name;

    /**
     * Time since last time the game was paused.
     */
    sf::Time delay;
};


#endif
