
#include "moving_object.h"

Moving_Object::Moving_Object(sf::FloatRect & rect, sf::Sprite & sprite, sf::Vector2f velocity)
: Animated_Object{rect, sprite}, velocity{velocity}, flip_sprite{false}
{}

Update_Result Moving_Object::update(sf::Time const& time, Level & level)
{
    // move object
    rect.left += velocity.x * time.asMilliseconds();
    rect.top += velocity.y * time.asMilliseconds();

    // resolve collisions
    auto collisions{level.get_collisions(*this)};
    resolve_collisions(collisions);

    // increase animation timer
    Animated_Object::update(time, level);

    return Update_Result::none;
}


void Moving_Object::resolve_collisions(std::vector<std::shared_ptr<Game_Object>> collisions)
{

    // 1. collision with window borders
    if (rect.left < 0)
    {
        rect.left=0;
        velocity.x = 0;
    }
    else if (rect.left + rect.width > constants::window_width)
    {
        rect.left = constants::window_width - rect.width;
        velocity.x = 0;
    }

    // 2. collisions with platforms
    // find distance to objects in collision
    std::vector<std::pair<Game_Object*, double>> collision_distances;
    for (auto & other : collisions)
    {
        collision_distances.push_back(std::make_pair(other.get(), pow_dist_to(*other)));
    }

    // sort collisions by distance
    std::sort(collision_distances.begin(), collision_distances.end(),
              [] (std::pair<Game_Object*, double> const& a, std::pair<Game_Object*, double> const& b)
              {
                  return a.second < b.second;
              });

    // handle collisions in order of distance, closest first
    for (auto & other : collision_distances)
    {
        // check if there still is a collision
        if (!rect.intersects(other.first -> rect))
        {
            continue;
        }

        sf::IntRect other_rect{other.first -> rect};

        double x_overlap;
        rect.left < other_rect.left ? x_overlap = abs(other_rect.left - (rect.left + rect.width)) :
                                      x_overlap = abs(rect.left - (other_rect.left + other_rect.width));

        double y_overlap;
        rect.top < other_rect.top ? y_overlap = abs(other_rect.top - (rect.top + rect.height)) :
                                    y_overlap = abs(rect.top - (other_rect.top + other_rect.height));


        // move object the shortest way out of the collision
        if (x_overlap < y_overlap)
        {
            if (other_rect.left < rect.left)
            {
                // collision to the left
                velocity.x = std::max(0.0f, velocity.x);
                rect.left = other_rect.left + other_rect.width;
            }
            else
            {
                // collision to the right
                velocity.x = std::min(0.0f, velocity.x);
                rect.left = other_rect.left - rect.width;
            }
        }
        else
        {
            if (other_rect.top < rect.top)
            {
                // collision from above
                velocity.y = std::max(0.0f,velocity.y);
                rect.top = other_rect.top + other_rect.height;
            }
            else
            {
                // collision from below
                velocity.y = std::min(0.0f, velocity.y);
                rect.top = other_rect.top - rect.height;
            }
        }
    }
}

void Moving_Object::draw(sf::RenderWindow &window)
{
    sprite.setPosition(rect.left - ((48 - rect.width) / 2), rect.top - ((48 - rect.height)));
    Animated_Object::draw(window);
}

double Moving_Object::pow_dist_to(Game_Object & other) const
{
    return std::pow(rect.left - other.rect.left, 2) + std::pow(rect.top - other.rect.top, 2);
}