#include "class.h"

#include <sstream>
#include <fstream>

void Game::setWindowBounds(int left, int right, int top, int bottom)
{
    window_bound_left = left;
    window_bound_right = right;
    window_bound_top = top;
    window_bound_bottom = bottom;
}

int Game::get_player_score()
{
    return player_score_;
}

int Game::get_wave_size()
{
    return wave_size_;
}

int Game::get_wave_counter()
{
    return wave_counter_;
}

int Game::get_waves_to_next_wave_()
{
    return waves_to_next_wave_;
}

int Game::get_score_in_wave()
{
    return score_in_wave_;
}

float Game::get_crate_speed()
{
    return crate_speed_;
}

float Game::get_crate_shoot()
{
    return crate_shoot_;
}

int Game::get_crate_dmg()
{
    return crate_dmg_;
}

void Game::reset_crate_effects()
{
    crate_speed_ = 1;
    crate_dmg_ = 1;
}

void Game::set_crate_speed()
{
    crate_speed_ = 1.5;
}

void Game::set_crate_dmg()
{
    crate_dmg_ = 2;
}

float Game::get_effect_time()
{
    return effect_time_;
}

float Game::update_effect_time(const sf::Time &elapsed)
{
    effect_time_ = effect_time_ + elapsed.asSeconds();
    return effect_time_;
}

void Game::reset_effect_time()
{
    effect_time_ = 0;
}

bool Game::is_with_effect()
{
    if(is_effect)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Game::set_is_with_effect()
{
    is_effect = true;
}

void Game::reset_is_with_effect()
{
    is_effect = false;
}

void Game::add_point()
{
    player_score_++;
}

void Game::upgrade_wave_size()
{
    wave_size_++;
}

void Game::reset_wave_size()
{
    wave_size_ = 1;
}

void Game::upgrade_wave_counter()
{
    wave_counter_++;
}

void Game::upgrade_waves_to_next_wave()
{
    waves_to_next_wave_ = waves_to_next_wave_ + 5;
}

void Game::upgrade_score_in_wave()
{
    score_in_wave_++;
}

void Game::reset_score_in_wave()
{
    score_in_wave_ = 0;
}

void Game::reset_waves_to_next_wave()
{
    waves_to_next_wave_ = 5;
}

float Game::get_sum_of_time()
{
    return sum_of_time_;
}

float Game::update_sum_of_time(const sf::Time &elapsed)
{
    sum_of_time_ = sum_of_time_ + elapsed.asSeconds();
    return sum_of_time_;
}

void Game::reset_sum_of_time()
{
    sum_of_time_ = 0;
}

float Game::get_shooting_time()
{
    return shooting_time_;
}

bool Game::new_record(std::vector<std::string> v_score)
{
    int score;
    bool record = false;

    for(size_t i = 0; i < v_score.size(); i++)
    {
        std::stringstream conv;
        conv << v_score[i];
        conv >> score;

        if(get_player_score() > score)
        {
            record = true;
        }
    }

    if(record)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Game::restart_game()
{
    player_score_ = 0;
    wave_size_ = 1;
    waves_to_next_wave_ = 5;
    score_in_wave_ = 1;
}

void Game::read_ranking(std::vector<std::string> v_name, std::vector<std::string> v_score)
{
    v_name.clear();
    v_score.clear();

    size_t position = 0;

    std::fstream odczyt;
    odczyt.open("ranking.txt", std::ios::in);
    while(!odczyt.eof())
    {
        std::string line;
        getline(odczyt, line);
        position = line.find(';');
        v_name.emplace_back(line.substr(0, position));
        v_score.emplace_back(line.substr(position + 1));
    }
    odczyt.close();
}

void Game::update_ranking(std::string player_name, std::vector<std::string> v_name, std::vector<std::string> v_score)
{
    int score;
    int iterator = 0;

    for(size_t i = 0; i < 5; i++)
    {
        std::stringstream conv;
        conv << v_score[i];
        conv >> score;

        if(get_player_score() > score)
        {
            iterator = i;
            break;
        }
    }

    std::fstream zapis;
    zapis.open("ranking.txt");
    for(int i = 0; i < 5; i++)
    {
        if(i < iterator)
        {
            zapis<<v_name[i]<<";"<<v_score[i]<<std::endl;
        }
        else if(i == iterator)
        {
            zapis<<player_name<<";"<<get_player_score()<<std::endl;
        }
        else
        {
            zapis<<v_name[i-1]<<";"<<v_score[i-1]<<std::endl;
        }
    }
    zapis.close();
}



Player::Player(sf::Texture &texture, const int &resolution_x, const int &resolution_y, int HP, int speed)
{
    setTexture(texture);
    setPosition((resolution_x/2) - getGlobalBounds().width/2, resolution_y - 178);
    setWindowBounds(0, resolution_x, 0, resolution_y);
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
            move(-speed_ * elapsed.asSeconds() * get_crate_speed(), 0);
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if(player_bounds.left + player_bounds.width <= window_bound_right)
        {
            move(speed_ * elapsed.asSeconds() * get_crate_speed(), 0);
        }

    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if(player_bounds.top >= window_bound_top)
        {
            move(0, -speed_ * elapsed.asSeconds() * get_crate_speed());
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if(player_bounds.top + player_bounds.height <= window_bound_bottom)
        {
            move(0, speed_ * elapsed.asSeconds() * get_crate_speed());
        }
    }
}



Bullet::Bullet(sf::Texture &texture, sf::FloatRect player_bounds)
{
    setTexture(texture);
    setPosition(player_bounds.left + player_bounds.width/2 - 4, player_bounds.top);
}

void Bullet::animate(const sf::Time &elapsed)
{
    move(0, -bullet_speed_ * elapsed.asSeconds());
}



Crate::Crate(sf::Texture &texture, sf::FloatRect enemy_bounds, int effect)
{
    setTexture(texture);
    setPosition(enemy_bounds.left + enemy_bounds.width/2 + 22, enemy_bounds.top + enemy_bounds.height/2);
    effect_ = effect;

    if(effect == 0)
    {
        set_crate_speed();
    }
    else
    {
        set_crate_dmg();
    }
}

void Crate::animate(const sf::Time &elapsed)
{
    move(0, crate_speed_ * elapsed.asSeconds());
}

int Crate::get_effect()
{
    return effect_;
}

Explosion::Explosion(const sf::Texture &texture, sf::FloatRect enemy_bounds)
{
    setTexture(texture);
    setPosition(enemy_bounds.left, enemy_bounds.top);
    setTextureRect(sf::IntRect(0, 0, 48, 48));
    add_frame(sf::IntRect(0, 0, 48, 48));
    add_frame(sf::IntRect(48, 0, 48, 48));
    add_frame(sf::IntRect(96, 0, 48, 48));
    add_frame(sf::IntRect(144, 0, 48, 48));
    add_frame(sf::IntRect(192, 0, 48, 48));
    add_frame(sf::IntRect(240, 0, 48, 48));
    add_frame(sf::IntRect(288, 0, 48, 48));
    setScale(2.5, 2.5);
}

void Explosion::add_frame(const sf::IntRect &frame)
{
    frames_of_animation.emplace_back(frame);
}

void Explosion::frame_animate(const sf::Time &elapsed)
{
    sum_of_time += elapsed.asSeconds();

    if(sum_of_time >= 1.0 / 14.0)
    {
        setTextureRect(frames_of_animation[current_frame]);
        {
            current_frame++;
            sum_of_time = 0;
        }
    }
}

size_t Explosion::get_current_frame()
{
    return current_frame;
}


Enemy::Enemy(sf::Texture &texture, int respawn_pos, int HP, int speed)
{
    setTexture(texture);
    setPosition(respawn_pos, -getGlobalBounds().height);
    HP_ = HP;
    speed_ = speed;
}

void Enemy::animate(const sf::Time &elapsed)
{
    if(getGlobalBounds().top < 10)
    {
        move(0, 4.5 * speed_ * elapsed.asSeconds());
    }
    else
    {
        move(0, speed_ * elapsed.asSeconds());
    }

}

int Enemy::get_HP()
{
    return HP_;
}

int Enemy::get_damage(int damage)
{
    HP_ = HP_ - damage;
    return HP_;
}
