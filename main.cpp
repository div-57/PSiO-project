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

    std::vector<std::unique_ptr<Game>> enemies;
    std::vector<std::unique_ptr<Game>> bullets;

    sf::RenderWindow window(sf::VideoMode(resolution_x, resolution_y), "Air Battle");
    window.setFramerateLimit(60);

    sf::Texture tex_player_plane = load_texture("img/player_plane.png");
    sf::Texture tex_enemy_plane_red = load_texture("img/enemy_plane_red.png");
    sf::Texture tex_bullet = load_texture("img/bullet.png");
    sf::Texture tex_sea = load_texture("img/sea.png");
    tex_sea.setRepeated(true);

    sf::Image icon;
    icon.loadFromFile("img/player_plane.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Player player(tex_player_plane, resolution_x, resolution_y, 100, 400);

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

        if(player.get_shooting_time() <= player.get_sum_of_time())
        {
            bullets.emplace_back(std::make_unique<Bullet>(tex_bullet, player.getGlobalBounds()));
            player.reset_sum_of_time();
        }
        else
        {
            player.update_sum_of_time(elapsed);
        }

        for(auto &i : enemies)
        {
            if(i->getGlobalBounds().intersects(player.getGlobalBounds()) || (i->getGlobalBounds().top + i->getGlobalBounds().height) >= resolution_y)
            {
                std::cout<<"Przegrales"<<std::endl;
                std::cout<<"Twoj wynik to: "<<player.check_score()<<std::endl;
                window.close();
                break;
            }
        }

        for(size_t i = 0; i < enemies.size(); i++)
        {
            for(size_t j = 0; j < bullets.size(); j++)
            {
                if(bullets[j]->getGlobalBounds().intersects(enemies[i]->getGlobalBounds()))
                {
                    Enemy_red *enemy = dynamic_cast<Enemy_red *>(enemies[i].get());
                    Bullet *bullet = dynamic_cast<Bullet *>(bullets[j].get());

                    if (enemy != nullptr)
                    {
                        if(bullet != nullptr)
                        {
                            if(enemy->get_HP() <= 50)
                            {
                                player.add_point();
                                player.upgrade_score_in_wave();

                                auto iterator_enemy = enemies.begin() + i;
                                enemies.erase(iterator_enemy);

                                auto iterator_bullet = bullets.begin() + j;
                                bullets.erase(iterator_bullet);
                            }
                            else
                            {
                                enemy->get_damage(50);

                                auto iterator_bullet = bullets.begin() + j;
                                bullets.erase(iterator_bullet);
                            }
                        }
                    }
                }
            }
        }

        if(player.get_score_in_wave() == player.wave_size())
        {
            if(player.get_score_in_size() == player.check_score())
            {
                player.upgrade_wave_size();
                player.upgrade_score_in_size();
            }

            for(int i = 0; i < player.wave_size(); i++)
            {
                enemies.emplace_back(std::make_unique<Enemy_red>(tex_enemy_plane_red, resolution_x, 100, 50));
            }

            player.reset_score_in_wave();
        }

        player.animate(elapsed);

        for(auto &it : bullets)
        {
            it->animate(elapsed);
        }

        for(auto &it : enemies)
        {
            it->animate(elapsed);
        }

        window.clear(sf::Color::Black);

        window.draw(sea);

        for(auto &it : enemies)
        {
            window.draw(*it);
        }

        for(auto &it : bullets)
        {
            window.draw(*it);
        }

        window.draw(player);

        window.display();
    }

    return 0;
}
