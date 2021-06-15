#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "class.h"

sf::Texture load_texture(const std::string &path)
{
    sf::Texture texture;
    if(!texture.loadFromFile(path))
    {
        std::cerr<<"Could not load texture"<<std::endl;
    }

    return texture;
}

int main()
{
    int resolution_x = 1366;
    int resolution_y = 768;

    sf::RenderWindow window(sf::VideoMode(resolution_x, resolution_y), "Air Battle");
    window.setFramerateLimit(60);

    sf::Texture tex_player_plane = load_texture("img/player_plane.png");
    sf::Texture tex_enemy_plane_red = load_texture("img/enemy_plane_red.png");
    sf::Texture tex_sea = load_texture("img/sea.png");
    tex_sea.setRepeated(true);

    sf::Image icon;
    icon.loadFromFile("img/player_plane.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Player player(tex_player_plane, resolution_x, resolution_y, 100, 400);

    Enemy_red enemy(tex_enemy_plane_red, resolution_x, 100, 50);
    Enemy_red enemy_2(tex_enemy_plane_red, resolution_x, 100, 50);

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
        enemy.animate(elapsed);
        enemy_2.animate(elapsed);

        if(player.getGlobalBounds().intersects(enemy.getGlobalBounds()) || player.getGlobalBounds().intersects(enemy_2.getGlobalBounds()))
        {
            window.close();
            std::cout<<"Przegrales"<<std::endl;
        }

        window.clear(sf::Color::Black);

        window.draw(sea);
        window.draw(enemy);
        window.draw(enemy_2);
        window.draw(player);

        window.display();
    }

    return 0;
}
