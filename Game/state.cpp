
#include "state.h"

State::~State() {}

void State::run(sf::RenderWindow & window, std::shared_ptr<State> state, bool paused)
{
    // measures elapsed time
    sf::Clock timer;

    // game loop
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                // close program
                case sf::Event::Closed:
                    return;
                // pause program
                case sf::Event::LostFocus:
                    paused = true;
                    break;
                // resume program
                case sf::Event::GainedFocus:
                    timer.restart();
                    paused = false;
                    break;
                default:
                    break;
            }
        }

        if (!paused) {
            // handle user input
            state = state -> take_user_input();

            // exit the game
            if (!state) {
                return;
            }

            // update the state
            state = state -> update(timer.restart());
        }

        // clear the screen
        window.clear(sf::Color(2,23,33));

        // add objects to the draw buffer
        state -> draw(window);

        // draw to the screen
        window.display();


    }
}