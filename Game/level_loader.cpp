
#include "level_loader.h"

Level_Loader Level_Loader::instance;

Level_Loader::Level_Loader()
: tile_sheet{sf::Texture{}}, animation_sheet{sf::Texture{}}
{
    // load sprite textures for non-animated objects
    tile_sheet.loadFromFile("Media/map_tiles.png");

    // load sprite textures for animated objects
    animation_sheet.loadFromFile("Media/animation_sheet.png");
}

std::unique_ptr<Level> Level_Loader::load_level(std::string const& level_name)
{
    // read file data
    std::string path{"Levels/" + level_name + ".csv"};
    std::fstream fs{path};

    // container for every object in a level
    std::multiset<std::pair<int, std::shared_ptr<Game_Object>>> game_objects;

    // player start position
    sf::Vector2f player_pos;

    sf::FloatRect rect;

    sf::Sprite sprite;
    sprite.setTexture(instance.tile_sheet);
    sprite.setScale(3, 3);

    sf::Sprite animated_sprite;
    animated_sprite.setTexture(instance.animation_sheet);
    animated_sprite.setScale(3, 3);

    /* ---ADD MAIN LAYER--- */
    rect.width = 48;
    rect.height = 48;
    int position{0};
    int value;
    while (fs >> value)
    {
        rect.left = position % constants::window_width;
        rect.top = 48 * (position / constants::window_width);

        // add walking enemy
        if (value == 111)
        {
            rect.width = 42;
            rect.height = 42;
            rect.top += 6;

            animated_sprite.setTextureRect(
                    sf::IntRect{0, 16 * 6, 16, 16});

            game_objects.insert(std::make_pair(4,std::make_shared<Walking_Enemy>(
                    rect, animated_sprite, 3, 48)));

            rect.width = 48;
            rect.height = 48;
        }
        // add jumping enemy
        else if (value == 112)
        {
            rect.width = 40;
            rect.height = 44;
            rect.top += 8;

            animated_sprite.setPosition(rect.left, rect.top);

            animated_sprite.setTextureRect(
                    sf::IntRect{0,16 * 4,16,16});

            game_objects.insert(std::make_pair(4,std::make_shared<Jumping_Enemy>(
                            rect, animated_sprite,2, 96)));

            rect.width = 48;
            rect.height = 48;
        }
        // add flying enemy
        else if (value == 113)
        {
            rect.width = 40;
            rect.height = 40;
            rect.top += 4;

            animated_sprite.setPosition(rect.left, rect.top);

            animated_sprite.setTextureRect(
                    sf::IntRect{1, 16 * 5 + 1, 16, 16});

            game_objects.insert(std::make_pair(
                    4,std::make_shared<Flying_Enemy>(
                           rect, animated_sprite,1,96)));

            rect.width = 48;
            rect.height = 48;
        }
        // add Player 1
        else if (value == 135)
        {
            rect.width = 40;
            animated_sprite.setPosition(rect.left, rect.top);

            animated_sprite.setTextureRect(
                    sf::IntRect{16, 16, 16, 16});

            std::shared_ptr<Player> p{new Player{rect, animated_sprite}};

            game_objects.insert(std::make_pair(5,
                                               std::make_shared<Player>(rect, animated_sprite)));

            player_pos = sf::Vector2f{rect.left, rect.top};
            rect.width = 48;
        }
        // add platform
        else if (value < 312 && value > 0 && value != 136)
        {
            sprite.setPosition(rect.left, rect.top);

            sprite.setTextureRect(sf::IntRect{
                16 * (value % 24), 16 * (value / 24), 16, 16});

            game_objects.insert(std::make_pair(
                    4,std::make_shared<Textured_Object>(rect, sprite)));
        }

        fs.ignore(1);
        position += 48;
    }
    fs.close();


    /*  ---ADD LAVA--- */
    rect.width = 96;
    rect.height = 96;

    // add animated lava
    for (int i{0}; i < 12; ++i)
    {
        rect.left = position % constants::window_width;
        rect.top = 48 * (position / constants::window_width);
        animated_sprite.setPosition(rect.left, rect.top);
        animated_sprite.setTextureRect(
                sf::IntRect{(i % 6) * 32, 16 * 9, 32, 32});
        game_objects.insert(std::make_pair(
                10,std::make_shared<Lava>(rect, animated_sprite, true)));
        position += 96;
    }
    // add large non-animated lava rectangle
    rect = sf::FloatRect{0, 48.0f * (position / constants::window_width),
                                  constants::window_width, constants::window_height};
    sprite.setTextureRect(sf::IntRect{16 * 10, 16 * 6, 16, 16});
    sprite.setScale(72,72);
    game_objects.insert(std::make_pair(
            10,std::make_shared<Lava>(rect, sprite, false)));
    sprite.setScale(3,3);




    /* ---ADD BACKGROUND--- */
    path = "Levels/" + level_name + "_bg.csv";
    fs.open(path);

    rect.width = 0;
    rect.height = 0;

    if (fs.is_open())
    {
        position = 0;

        while (fs >> value)
        {
            rect.left = position % constants::window_width;
            rect.top = 48 * (position / constants::window_width);

            if (value > 312 && value < 480) {
                // add lava fall
                if (value == 384) {
                    animated_sprite.setPosition(rect.left, rect.top);
                    animated_sprite.setTextureRect(sf::IntRect{
                        (position / constants::window_width) % 3,16 * 7, 16, 16});

                    game_objects.insert(std::make_pair(
                            2,std::make_shared<Animated_Object>(rect, animated_sprite)));
                }
                // add torch
                else if (value == 432)
                {
                    animated_sprite.setPosition(rect.left, rect.top);
                    animated_sprite.setTextureRect(sf::IntRect{
                            (position / constants::window_width) % 3,
                             16 * 13, 16, 16});

                    game_objects.insert(std::make_pair(
                            2,std::make_shared<Animated_Object>(rect, animated_sprite)));
                }
                // misc background
                else
                {
                    sprite.setPosition(rect.left, rect.top);
                    sprite.setTextureRect(sf::IntRect{
                        16 * (value % 24),16 * (value / 24), 16, 16});

                    game_objects.insert(std::make_pair(
                            2, std::make_shared<Textured_Object>(rect, sprite)));
                }
            }

            fs.ignore(1);
            position += 48;
        }
    }
    fs.close();


    /* ---ADD FOREGROUND--- */
    path = "Levels/" + level_name + "_fg.csv";
    fs.open(path);

    if (fs.is_open())
    {
        position = 0;
        while (fs >> value)
        {
            rect.left = position % constants::window_width;
            rect.top = 48 * (position / constants::window_width);

            if (value > 480)
            {
                sprite.setPosition(rect.left, rect.top);

                sprite.setTextureRect(sf::IntRect{
                    16 * (value % 24),16 * (value / 24), 16, 16});

                game_objects.insert(std::make_pair(
                        8, std::make_shared<Textured_Object>(rect, sprite)));
            }

            fs.ignore(1);
            position += 48;
        }
    }
    fs.close();

    return std::make_unique<Level>(game_objects, player_pos);
}



