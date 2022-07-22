

#include "game_state.h"


Game_State::Game_State(std::string const& level_name)
: level{Level_Loader::load_level(level_name)}, level_name{level_name}, delay{sf::Time{}}
{}

std::shared_ptr<State> Game_State::take_user_input()
{
    // pause a level
    if (delay.asMilliseconds() > 500 &&
            (sf::Keyboard::isKeyPressed(sf::Keyboard::P) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
    {
        delay = sf::Time{};
        return std::make_shared<Menu_State>(Menu_Type::pause, shared_from_this());
    }

    return shared_from_this();
}


std::shared_ptr<State> Game_State::update(sf::Time time)
{
    delay += time;

    // update the level
    Update_Result result{level -> update(time)};

    if (result == Update_Result::game_over)
    {
        return std::make_shared<Menu_State>(Menu_Type::game_over, shared_from_this());
    }
    else if (result == Update_Result::level_complete)
    {
        return std::make_shared<Menu_State>(Menu_Type::level_complete, shared_from_this());
    }

    return shared_from_this();
}

void Game_State::draw(sf::RenderWindow & window)
{
    level -> draw(window);
}

std::string Game_State::get_level_name() const
{
    return level_name;
}