#include "class.h"

void Game::setWindowBounds(int left, int right, int top, int bottom)
{
    window_bound_left = left;
    window_bound_right = right;
    window_bound_top = top;
    window_bound_bottom = bottom;
}

void Player::animate(const sf::Time &elapsed)
{
    sf::FloatRect player_bounds = getGlobalBounds();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if(player_bounds.left >= window_bound_left)
        {
            move(-speed * elapsed.asSeconds(), 0);
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if(player_bounds.left + player_bounds.width <= window_bound_right)
        {
            move(speed * elapsed.asSeconds(), 0);
        }

    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if(player_bounds.top >= window_bound_top)
        {
            move(0, -speed * elapsed.asSeconds());
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if(player_bounds.top + player_bounds.height <= window_bound_bottom)
        {
            move(0, speed * elapsed.asSeconds());
        }
    }
}
