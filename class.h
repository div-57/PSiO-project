#ifndef CLASS_H
#define CLASS_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Game : public sf::Sprite
{
public:
    int window_bound_left;
    int window_bound_right;
    int window_bound_top;
    int window_bound_bottom;
    void setWindowBounds(int, int, int, int);
};

class Player : public Game
{
private:
    int HP = 100;
    int speed = 400;
public:
    Player(){};
    void animate(const sf::Time &elapsed);
};

class Enemy : public Game
{

};

#endif // CLASS_H
