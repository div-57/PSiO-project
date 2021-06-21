#include "class.h"

void Game::setWindowBounds(int left, int right, int top, int bottom)
{
    window_bound_left = left;
    window_bound_right = right;
    window_bound_top = top;
    window_bound_bottom = bottom;
}

int Game::check_score()
{
    return score_;
}

int Game::wave_size()
{
    return wave_size_;
}

void Game::add_point()
{
    score_++;
}

void Game::upgrade_wave_size()
{
    wave_size_++;
}

void Game::upgrade_score_in_wave()
{
    score_in_wave++;
}

int Game::get_score_in_wave()
{
    return score_in_wave;
}

void Game::reset_score_in_wave()
{
    score_in_wave = 0;
}

void Game::upgrade_score_in_size()
{
    score_in_size_ = score_in_size_ + (5 * wave_size_);
}

int Game::get_score_in_size()
{
    return score_in_size_;
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
}

void Enemy_red::animate(const sf::Time &elapsed)
{
    if(getGlobalBounds().top < 0)
    {
        move(0, 3 * speed_ * elapsed.asSeconds());
    }
    else
    {
        move(0, speed_ * elapsed.asSeconds());
    }

}

Bullet::Bullet(sf::Texture &texture, sf::FloatRect player_bounds)
{
    setTexture(texture);
    setPosition(player_bounds.left + player_bounds.width/2 - 4, player_bounds.top);
}

float Game::get_sum_of_time()
{
    return sum_of_time_;
}

float Game::get_shooting_time()
{
    return shooting_time_;
}

void Game::reset_sum_of_time()
{
    sum_of_time_ = 0;
}

float Game::update_sum_of_time(const sf::Time &elapsed)
{
    sum_of_time_ = sum_of_time_ + elapsed.asSeconds();
    return sum_of_time_;
}

void Bullet::animate(const sf::Time &elapsed)
{
    move(0, -bullet_speed_ * elapsed.asSeconds());
}

int Enemy_red::get_HP()
{
    return HP_;
}

int Enemy_red::get_damage(int damage)
{
    HP_ = HP_ - damage;
    return HP_;
}
