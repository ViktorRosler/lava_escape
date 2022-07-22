

#include "player.h"

Player::Player(sf::FloatRect & rect, sf::Sprite & sprite)
: Moving_Object{rect, sprite}, time_since_jump{sf::Time{}},
  time_since_damage{sf::Time{sf::milliseconds(2000)}},
  time_since_fire{sf::Time{sf::milliseconds(1000)}},
  health{3}, health_bar{sf::Sprite{*sprite.getTexture()}}
{
    health_bar.setScale(1.5, 1.5);
}

Update_Result Player::update(sf::Time const& time, Level & level)
{

    // activate lava
    if (velocity.y < 0)
    {
        level.rising_lava = true;
    }

    // update player position variable in level
    level.player_pos = sf::Vector2f{rect.left, rect.top};

    // update timers
    time_since_damage += time;
    time_since_fire += time;


    // handle player input
    handle_input(time, level);


    // apply gravity
    velocity.y = std::min(velocity.y + constants::gravity_const * time.asMilliseconds(), 3.0f);

    // move, resolve collision, update animation
    Moving_Object::update(time, level);

    // notify Level if the player died or completed the level
    if (health <= 0 && velocity.y == 0)
    {
        return Update_Result::game_over;
    }
    else if (rect.top <= 0 && velocity.y == 0)
    {
        velocity.x = 0;
        return Update_Result::level_complete;
    }
    else
    {
        return Update_Result::none;
    }

}

void Player::draw(sf::RenderWindow & window)
{
    // update health bar position & draw
    health_bar.setTextureRect(sf::IntRect{(3 - health) * 32,16 * 18,24, 16});
    health_bar.setPosition(rect.left, rect.top - 24);
    window.draw(health_bar);

    // animate & draw player
    Moving_Object::draw(window);
}



void Player::handle_input(sf::Time const& time, Level & level)
{
    // update jump timer
    if (velocity.y == 0)
    {
        time_since_jump += time;
    }

    // jump
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (velocity.y == 0 && time_since_jump.asMilliseconds() > 50)
        {
            velocity.y -= 1.9;
            time_since_jump = sf::Time{};
        }
    }

    // fire
    if (time_since_fire.asMilliseconds() > 300 &&
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::X)))
    {
        time_since_fire = sf::Time{};
        velocity.x = 0;
        if (flip_sprite)
        {
            fire(level, false);
        }
        else
        {
            fire(level, true);
        }
    }

    // move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        velocity.x = std::max(-0.4f, velocity.x - 0.01f * time.asMilliseconds());
        flip_sprite = true;
    }
    // move right
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        velocity.x = std::min(0.4f, velocity.x + 0.01f * time.asMilliseconds());
        flip_sprite = false;
    }
    // stop
    else
    {
        velocity.x = 0;
    }

}

void Player::resolve_collisions(std::vector<std::shared_ptr<Game_Object>> collisions)
{
    // collisions with enemy or projectile
    for (size_t i{0}; i < collisions.size(); ++i)
    {
        auto other_ptr{collisions.at(i).get()};
        if (dynamic_cast<Enemy*>(other_ptr) || dynamic_cast<Projectile*>(other_ptr))
        {
            if (time_since_damage.asMilliseconds() >= 1618)
            {
                time_since_damage = sf::Time{};
                --health;

                if (health == 0)
                {
                    velocity.y = std::max(0.001f, velocity.y);
                }
            }
            collisions.erase(collisions.begin() + i);
            --i;
        }
        else if (dynamic_cast<Lava*>(other_ptr))
        {
            health = 0;
        }
    }

    // collisions with platforms
    Moving_Object::resolve_collisions(collisions);
}

void Player::animate()
{
    sf::IntRect texture_rect{0,0,16,16};

    // death frame
    if (health <= 0)
    {
        texture_rect.top = 16;
        texture_rect.left = 48;
    }
    // fire frame
    else if (time_since_fire.asMilliseconds() < 150 )
    {
        texture_rect.left = 64;
    }
    // jumping frame
    else if (velocity.y != 0 && time_since_jump.asMilliseconds() < 50 )
    {
        texture_rect.top = 16;
        texture_rect.left = 0;

    }
    // falling frame
    else if (velocity.y != 0)
    {
        texture_rect.top = 0;
        texture_rect.left = 0;
    }
    // walking animation
    else if (velocity.x != 0)
    {
        // adjust animation frame rate based on player velocity
        if (animation_timer.asMilliseconds() > 200 - fabs(velocity.x) * 300)
        {
            ++current_frame %= 4;
            animation_timer = sf::Time{};
        }

        texture_rect.top = 0;
        texture_rect.left = current_frame * 16;
    }
    // standing frame
    else
    {
        current_frame = 0;
        texture_rect.top = 16;
        texture_rect.left = 16;
    }

    // horizontal flip
    if (flip_sprite)
    {
        texture_rect.left += 16;
        texture_rect.width = -16;
    }

    // apply changes to texture
    sprite.setTextureRect(texture_rect);

    // player taking damage effect
    if (health > 0 && time_since_damage.asMilliseconds() < 1618)
    {
        if ((time_since_damage.asMilliseconds() / 100) % 2 == 0)
        {
            sprite.setColor(sf::Color::White);
        }
        else
        {
            sprite.setColor(sf::Color::Transparent);
        }
    }
}

void Player::fire(Level &level, bool direction) const
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
    level.add_object(proj, 3);

}