

#include "walking_enemy.h"


Update_Result Walking_Enemy::update(sf::Time const& time, Level & level)
{
    // apply gravity
    velocity.y = std::min(velocity.y + constants::gravity_const * time.asMilliseconds(), 4.0f);

    // increment timer
    action_timer += time;

    // take action
    if (action_timer.asMilliseconds() > 500)
    {
        action_timer = sf::Time{};
        int num = random_int(0,6);
        switch (num)
        {
            // walk right
            case 0:
                velocity.x = 0.03;
                flip_sprite = false;
                break;
            // walk left
            case 1:
                velocity.x = -0.03;
                flip_sprite = true;
                break;
            // keep doing same action
            case 2:
                break;
            // stop
            default:
                velocity.x = 0;
                break;
        }
    }

    return Enemy::update(time, level);
}


void Walking_Enemy::animate()
{
    sf::IntRect texture_rect{sprite.getTextureRect()};

    // walking animation
    if (velocity.x != 0)
    {
        if (animation_timer.asMilliseconds() >=  250)
        {
            ++current_frame %= 3;
            animation_timer = sf::Time{};
        }
    }
    else
    // standing frame
    {
        texture_rect.left = 0;
    }

    Enemy::animate();
}