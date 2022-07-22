#include <SFML/Graphics.hpp>

#include "menu_state.h"
#include "constants.h"

int main()
{
    sf::RenderWindow window{sf::VideoMode{constants::window_width, constants::window_height},
                            "Lava Escape",sf::Style::Close | sf::Style::Titlebar};

    window.setView(sf::View{sf::FloatRect{0,0,
                                          constants::window_width, constants::window_height}});

    window.setFramerateLimit(200);

    State::run(window, std::make_shared<Menu_State>(Menu_Type::main));

    return 0;
}
