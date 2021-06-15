#ifndef CLASS_H
#define CLASS_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Game : public sf::Sprite
{
public:
    Game() : Sprite() {};
    virtual ~Game() = default;

    int window_bound_left;
    int window_bound_right;
    int window_bound_top;
    int window_bound_bottom;
    void setWindowBounds(int, int, int, int);

protected:

};

class Player : public Game
{
private:
    int HP_;
    int speed_;
    int bullet_speed_ = 600;
    float shooting_time_ = 1.0;
public:
    Player() {};
    Player(sf::Texture &texture, const int &resolution_x, const int &resolution_y, int HP, int speed);
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
};

class Enemy_gray : public Game
{

};

#endif // CLASS_H
