#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "class.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1366, 768), "Air Battle");
    window.setFramerateLimit(60);

    sf::Texture tex_player_plane;
    sf::Texture tex_sea;

    sf::Image icon;
    icon.loadFromFile("img/player_plane.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    if(!tex_player_plane.loadFromFile("img/player_plane.png"))
    {
        std::cerr<<"Could not load texture"<<std::endl;
        return 1;
    }

    if(!tex_sea.loadFromFile("img/sea.png"))
    {
        std::cerr<<"Could not load texture"<<std::endl;
        return 1;
    }
    tex_sea.setRepeated(true);

    Player player;
    player.setTexture(tex_player_plane);
    player.setPosition((window.getSize().x/2) - 60, 600);

    player.setWindowBounds(0, window.getSize().x, 0, window.getSize().y);

    sf::Sprite sea;
    sea.setTexture(tex_sea);
    sea.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y + 300));
    sea.setPosition(0, -300);

    sf::Clock clock;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        sf::Time elapsed = clock.restart();
        sea.move(0, 35 * elapsed.asSeconds());

        if(sea.getPosition().y >= -150)
        {
            sea.setPosition(0, -300);
        }

        player.animate(elapsed);

        window.clear(sf::Color::Black);

        window.draw(sea);
        window.draw(player);

        window.display();
    }

    return 0;
}
