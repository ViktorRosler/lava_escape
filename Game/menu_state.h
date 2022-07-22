

#ifndef MENU_STATE_H
#define MENU_STATE_H


#include <string>
#include <vector>
#include <functional>
#include <filesystem>

#include "state.h"
#include "game_state.h"
#include "constants.h"

class Game_State;  // forward declaration

/**
 * Specifies menu types.
 */
enum class Menu_Type : int
{
    main, pause, levels, level_complete, game_over
};

/**
 * A state class that represents the program being in a menu.
 */
class Menu_State : public State
{
public:
    /*
     * Construct a menu of a given type, with an optional previous State.
     */
    Menu_State(Menu_Type type, std::shared_ptr<State> game = nullptr);

    /**
     *  Default destructor.
     */
    ~Menu_State() = default;

    /**
     * Handles user keyboard- and button presses.
     * May result in a state change between Game_State and Menu_State.
     */
    std::shared_ptr<State> take_user_input() override;

    /**
     * Called to update a Menu_State.
     */
    std::shared_ptr<State> update(sf::Time time) override;

    /**
     * Called to draw a Game_State to the screen.
     */
    void draw(sf::RenderWindow & window) override;

private:

    /**
     *   Game state to display behind the menu
     */
    std::shared_ptr<Game_State> game;

    /**
     *   Menu item.
     */
    struct Menu_Item
    {
        /**
         *   Menu item text to display on screen
         */
        sf::Text text;

        /**
         *   Action to perform when selected.
         */
        std::function<std::shared_ptr<State>()> action;
    };

    /**
     *  All menu items.
     */
    std::vector<Menu_Item> menu_items;

    /**
     * Font for menu item text.
     */
    sf::Font font;

    /**
     * The currently selected menu item
     * From top to bottom, [0..*]
     */
    unsigned int selected;

    /**
     * Time since selected menu item changed
     */
    sf::Time delay;

    /**
     * The type of a menu.
     * Can be one of the following:
     * main, pause, levels, options, game_over
     */
    Menu_Type type;

    /**
     * Helper function that return a vector with the names of all levels in the Level folder.
     */
    std::vector<std::string> get_level_names() const;

};


#endif
