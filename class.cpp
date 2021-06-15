#include "class.h"

void Game::setWindowBounds(int left, int right, int top, int bottom)
{
    window_bound_left = left;
    window_bound_right = right;
    window_bound_top = top;
    window_bound_bottom = bottom;
}

Player::Player(sf::Texture &texture, const int &resolution_x, const int &resolution_y, int HP, int speed)
{
    setTexture(texture);
    setPosition((resolution_x/2) - getGlobalBounds().width/2, resolution_y - 178);
    setWindowBounds(0, resolution_x, 0, resolution_y);
    HP_ = HP;
    speed_ = speed;
}

Enemy_red::Enemy_red(sf::Texture &texture, const int &resolution_x, int HP, int speed)
{
    setTexture(texture);
    setPosition(rand() % (resolution_x - 121) + 1, -getGlobalBounds().height);
    HP_ = HP;
    speed_ = speed;
}

void Player::animate(const sf::Time &elapsed)
{
    sf::FloatRect player_bounds = getGlobalBounds();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if(player_bounds.left >= window_bound_left)
        {
            move(-speed_ * elapsed.asSeconds(), 0);
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if(player_bounds.left + player_bounds.width <= window_bound_right)
        {
            move(speed_ * elapsed.asSeconds(), 0);
        }

    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if(player_bounds.top >= window_bound_top)
        {
            move(0, -speed_ * elapsed.asSeconds());
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if(player_bounds.top + player_bounds.height <= window_bound_bottom)
        {
            move(0, speed_ * elapsed.asSeconds());
        }
    }

//    if(shooting_time_ <= 0)
//    {
//        shooting_time_ = 1;
//        shoot();
//    }
//    else
//    {
//        shooting_time_ -= elapsed.asSeconds();
//    }
}

void Enemy_red::animate(const sf::Time &elapsed)
{
    move(0, speed_ * elapsed.asSeconds());
}
