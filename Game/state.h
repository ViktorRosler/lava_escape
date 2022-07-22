
#ifndef STATE_H
#define STATE_H

#include <memory>
#include <SFML/Graphics.hpp>

/**
 * Represents the state of the program.
 * Only one State is active at a time.
 * Can be either a Game_State or a Menu_State.
 */
class State : public std::enable_shared_from_this<State>
{
public:
    /**
     * Default constructor.
     */
    State() = default;

    /**
     * Empty virtual destructor.
     */
    virtual ~State();

    /**
     * Handles user keyboard- and button input.
     * May result in a state change between Game_State and Menu_State.
     */
    virtual std::shared_ptr<State> take_user_input() = 0;

    /**
     * Called to update a State.
     * Can result in a state change between Game_State and Menu_State.
     */
    virtual std::shared_ptr<State> update(sf::Time time) = 0;

    /**
     * Called to draw a State to the screen.
     */
    virtual void draw(sf::RenderWindow & window) = 0 ;

    /**
     * Run a State, handling state-switches, until completion.
     */
    static void run(sf::RenderWindow & window, std::shared_ptr<State> state, bool paused = false);

};


#endif
