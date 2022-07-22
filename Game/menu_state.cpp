

#include "menu_state.h"


Menu_State::Menu_State(Menu_Type type, std::shared_ptr<State> gs)
: game{std::dynamic_pointer_cast<Game_State>(gs)}, font{sf::Font{}},
  selected{0}, delay{sf::Time{}}, type{type}
{
    font.loadFromFile("Media/font.ttf");

    // create a background Game_State to be drawn behind the menu
    if (game == nullptr)
    {
        game = std::make_shared<Game_State>("level1");
    }

    switch (type)
    {
        case Menu_Type::main:
        {
            menu_items.push_back(Menu_Item{sf::Text{"Start Game", font, 60},
                                           [this]() { return game; }});

            menu_items.push_back(Menu_Item{sf::Text{"Level Select", font, 60},
                                           []() { return std::make_shared<Menu_State>(Menu_Type::levels); }});

            menu_items.push_back(Menu_Item{sf::Text{"Exit", font, 60},
                                           []() { return nullptr; }});
            break;
        }
        case Menu_Type::pause:
        {
            menu_items.push_back(Menu_Item{sf::Text{"Resume", font, 60},
                                           [this]() { return game; }});

            menu_items.push_back(Menu_Item{sf::Text{"Retry", font, 60}, [this]() {
                return std::make_shared<Game_State>(game->get_level_name());
            }});

            menu_items.push_back(Menu_Item{sf::Text{"Main Menu", font, 60},
                                           []() { return std::make_shared<Menu_State>(Menu_Type::main); }});
            menu_items.push_back(Menu_Item{sf::Text{"Exit", font, 60},
                                           []() { return nullptr; }});
            break;
        }
        case Menu_Type::levels:
        {
            // create a menu item for each level in the Levels folder
            std::vector<std::string> names{get_level_names()};
            for (auto &level_name : names) {
                menu_items.push_back(Menu_Item{sf::Text{level_name, font, 60},
                                               [level_name]() { return std::make_shared<Game_State>(level_name); }});
            }

            menu_items.push_back(Menu_Item{sf::Text{"Back", font, 60},
                                           []() { return std::make_shared<Menu_State>(Menu_Type::main); }});
            break;
        }
        case Menu_Type::level_complete:
        {
            // find the name of the next level
            std::vector<std::string> names{get_level_names()};
            auto it{std::find(names.begin(), names.end(), game -> get_level_name())};
            it == --names.end() ? it = names.begin() : ++it;
            std::string level_name{*it};

            menu_items.push_back(Menu_Item{sf::Text{"Continue", font, 60}, [level_name]()
            {
                return std::make_shared<Game_State>(level_name);
            }});
        }
        // no break statement - intentional fall-through
        case Menu_Type::game_over:
        {
            menu_items.push_back(Menu_Item{sf::Text{"Retry", font, 60},[this]()
            {
                return std::make_shared<Game_State>(game -> get_level_name());
            }});

            menu_items.push_back(Menu_Item{sf::Text{"Main Menu", font, 60},
                                           []() { return std::make_shared<Menu_State>(Menu_Type::main);}});

            menu_items.push_back(Menu_Item{sf::Text{"Exit", font, 60},
                                           []() { return nullptr;}});
            break;
        }
        default:
            break;
    }
}

std::shared_ptr<State> Menu_State::take_user_input()
{

    if (delay.asMilliseconds() > 200)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            return menu_items[selected].action();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (selected != 0)
            {
                --selected;
            }
            if (type == Menu_Type::levels)
            {
                game = std::make_shared<Game_State>(menu_items[selected].text.getString());
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (selected != menu_items.size() - 1)
            {
                ++selected;
            }
            if (type == Menu_Type::levels && selected + 1 < menu_items.size())
            {
                game = std::make_shared<Game_State>(menu_items[selected].text.getString());
            }
        }
        else if (type == Menu_Type::pause &&
        (sf::Keyboard::isKeyPressed(sf::Keyboard::P) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
        {
            return game;
        }
        else
        {
            return shared_from_this();
        }
        delay = sf::Time{};
    }

    return shared_from_this();
}

std::shared_ptr<State> Menu_State::update(sf::Time time)
{
    delay += time;
    return shared_from_this();
}


void Menu_State::draw(sf::RenderWindow & window)
{
    // draw background Game_State
    game -> draw(window);


    sf::Vector2f view_position = window.getView().getCenter();
    double y{view_position.y - constants::window_height / 4};

    // draw text over certain menus
    if (type == Menu_Type::game_over || type == Menu_Type::level_complete)
    {
        sf::Text txt;
        txt.setFont(font);
        if (type == Menu_Type::game_over)
        {
            txt.setString("Game Over");
            txt.setFillColor(sf::Color{255,0,0});
        }
        else
        {
            txt.setString("Level Finished!");
            txt.setFillColor(sf::Color{0,255,0});
        }

        txt.setCharacterSize(70);
        txt.setPosition((constants::window_width - txt.getLocalBounds().width) / 2, y);
        window.draw(txt);
        y += txt.getLocalBounds().height * 3.5f;
    }


    // draw menu items
    for (size_t i{0}; i < menu_items.size(); ++i)
    {
        sf::FloatRect bounds = menu_items[i].text.getLocalBounds();
        menu_items[i].text.setPosition((constants::window_width - bounds.width) / 2, y);
        y += bounds.height * 2.0f;

        if (i == selected)
        {
            menu_items[i].text.setFillColor(sf::Color{255, 255, 0});
        }
        else
        {
            menu_items[i].text.setFillColor(sf::Color{255, 255, 255});
        }

        window.draw(menu_items[i].text);
    }
}

std::vector<std::string> Menu_State::get_level_names() const
{
    std::vector<std::string> names{};
    for (const auto & entry : std::filesystem::directory_iterator("Levels"))
    {
        std::string file_name{entry.path().filename().string()};
        // ignore background/foreground files
        if (file_name.find("_bg.csv") == std::string::npos
            && file_name.find("_fg.csv") == std::string::npos)
        {
            std::string level_name{file_name.substr(0, file_name.size() - 4)};
            names.push_back(level_name);

        }
    }
    return names;
}