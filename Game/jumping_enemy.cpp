
#include "jumping_enemy.h"


Update_Result Jumping_Enemy::update(sf::Time const& time, Level & level)
{
    // increment timers
    action_timer += time;
    time_since_fire += time;

    // take action
    if (velocity.y == 0)
    {
        velocity.x = 0;

        if (action_timer.asMilliseconds() > 300)
        {
            int action = random_int(0, 29);
            action_timer = sf::Time{};

            // small jump right
            if (action < 10)
            {
                if (rect.left + 25 < start_pos.x + move_radius)
                {
                    velocity.x = 0.1;
                    velocity.y = -0.5;
                    flip_sprite = false;
                }
            }
            // small jump left
            else if (action < 20)
            {
                if (rect.left - 25 > start_pos.x - move_radius)
                {
                    velocity.x = -0.1;
                    velocity.y = -0.5;
                    flip_sprite = true;
                }
            }
            // low jump right
            else if (action < 22)
            {
                if (rect.left + 100 < start_pos.x + move_radius)
                {
                    velocity.x = 0.6;
                    velocity.y = -0.6;
                    flip_sprite = false;
                }
            }
            // low jump left
            else if (action < 24)
            {
                if (rect.left - 100 > start_pos.x - move_radius)
                {
                    velocity.x = -0.6;
                    velocity.y = -0.6;
                    flip_sprite = true;
                }
            }
            // high jump right
            else if (action < 25)
            {
                if (rect.left + 50 < start_pos.x + move_radius)
                {
                    velocity.x = 0.2;
                    velocity.y = -1.8;
                    flip_sprite = false;
                }
            }
            // high jump left
            else if (action < 26)
            {
                if (rect.left - 50 > start_pos.x - move_radius)
                {
                    velocity.x = -0.2;
                    velocity.y = -1.8;
                    flip_sprite = true;
                }
            }
            // fire projectile
            else if (action < 30)
            {
                time_since_fire = sf::Time{};
                flip_sprite ? fire(level, false) : fire(level, true);
            }

        }
    }

    // apply gravity
    velocity.y = std::min(velocity.y + constants::gravity_const * time.asMilliseconds(), 4.0f);

    return Enemy::update(time, level);
}

void Jumping_Enemy::animate()
{

    sf::IntRect texture_rect{sprite.getTextureRect()};

    // jump frame or shoot frame
    if (time_since_fire.asMilliseconds() < 150)
    {
        texture_rect.left = 48;
    }
    else
    {
        texture_rect.left = 0;
    }

    sprite.setTextureRect(texture_rect);

    Enemy::animate();

}

void Jumping_Enemy::fire(Level &level, bool direction)
{
    sf::Sprite proj_sprite;
    sf::FloatRect proj_rect;
    sf::Vector2f proj_velocity{0,0};
    proj_sprite.setTexture(*sprite.getTexture());
    proj_sprite.setScale(2,2);
    if (direction)
    {
        proj_sprite.setTextureRect(sf::IntRect{0,15 * 16, 16, 16});
        proj_rect = sf::FloatRect{rect.left + rect.width + 10, rect.top + rect.height / 2 - 4, 4, 4};
        proj_velocity.x = 1;
    }
    else
    {
        proj_sprite.setTextureRect(sf::IntRect{16,15 * 16, -16, 16});
        proj_rect = sf::FloatRect{rect.left - 10, rect.top + rect.height / 2 - 4, 4, 4};
        proj_velocity.x = -1;
    }

    std::shared_ptr<Projectile> proj{new Projectile{proj_rect, proj_sprite, proj_velocity}};
    level.add_object(proj, 5);

}