
#include "flying_enemy.h"


Update_Result Flying_Enemy::update(sf::Time const& time, Level & level)
{
    // increment timer
    action_timer += time;

    // take action
    if (action_timer.asMilliseconds() > 200) {
        action_timer = sf::Time{};

        int x{random_int(-1, 1)};
        velocity.x = x / 10.0f;

        int y{random_int(-1, 1)};
        velocity.y = y / 10.0f;

        velocity.x < 0 ? flip_sprite = true : flip_sprite = false;
    }

    // adjust y-velocity if too far away from start position
    if ((velocity.y < 0 && rect.top <= start_pos.y - move_radius - rect.height / 2) ||
        (velocity.y > 0 && rect.top >= start_pos.y + move_radius + rect.height / 2))
    {
        velocity.y = 0;
    }

    return Enemy::update(time, level);
}

void Flying_Enemy::animate()
{
    if (animation_timer.asMilliseconds() >=  75)
    {
        ++current_frame %= 3;
        animation_timer = sf::Time{};
    }

    Enemy::animate();
}