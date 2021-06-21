#ifndef CLASS_H
#define CLASS_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Game : public sf::Sprite
{
private:
    int score_ = 0;
    int wave_size_ = 1;
    int score_in_size_ = 5;
    int score_in_wave = 1;

    float shooting_time_ = 0.4;
    float sum_of_time_ = 0.35;

public:
    Game() : Sprite() {};
    virtual ~Game() = default;
    virtual void animate(const sf::Time &elapsed) = 0;

    int window_bound_left;
    int window_bound_right;
    int window_bound_top;
    int window_bound_bottom;
    void setWindowBounds(int, int, int, int);

    int check_score();
    int wave_size();
    void add_point();
    void upgrade_wave_size();
    void upgrade_next_wave();
    void upgrade_score_in_wave();
    int get_score_in_wave();
    void reset_score_in_wave();
    void upgrade_score_in_size();
    int get_score_in_size();

    float get_sum_of_time();
    float get_shooting_time();
    void reset_sum_of_time();
    float update_sum_of_time(const sf::Time &elapsed);
};

class Player : public Game
{
private:
    int HP_;
    int speed_;

public:
    Player() {};
    Player(sf::Texture &texture, const int &resolution_x, const int &resolution_y, int HP, int speed);
    void animate(const sf::Time &elapsed);
};

class Bullet : public Game
{
private:
    int bullet_speed_ = 600;

public:
    Bullet(sf::Texture &texture, sf::FloatRect player_bounds);
    void animate(const sf::Time &elapsed);
};

class Enemy_red : public Game
{
private:
    int HP_;
    int speed_;

public:
    Enemy_red(sf::Texture &texture, const int &resolution_x, int HP, int speed);
    void animate(const sf::Time &elapsed);

    int get_HP();
    int get_damage(int damage);
};

class Enemy_gray : public Game
{

};

#endif // CLASS_H
