#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

#include "class.h"

/*
    Funkcja ładująca tekstury
*/

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
    srand(time(NULL));

    sf::Clock clock;
    sf::String playerInput;

    int resolution_x = 1366;
    int resolution_y = 768;

    bool main_menu = true;
    bool menu_ranking = false;
    bool menu_jakgrac = false;
    bool menu_exit = false;
    bool game_over = false;

    bool record = false;

    std::vector<std::string> v_name;
    std::vector<std::string> v_score;
    std::string player_name;
    size_t position = 0;

    std::vector<std::string> from_file;

//    Odczytanie pliku "cfg.txt" i przypisanie wartosci
    std::fstream cfg;
    cfg.open("cfg.txt", std::ios::in);
    while(!cfg.eof())
    {
        std::string line;
        getline(cfg, line);
        position = line.find(';');
        from_file.emplace_back(line.substr(position + 1));
    }
    cfg.close();

    std::stringstream conversion1;
    conversion1 << from_file[0];
    int player_damage;
    conversion1 >> player_damage;

    std::stringstream conversion2;
    conversion2 << from_file[1];
    int enemy_red_hp;
    conversion2 >> enemy_red_hp;

    std::stringstream conversion3;
    conversion3 << from_file[2];
    int enemy_gray_hp;
    conversion3 >> enemy_gray_hp;

//    Czcionka
    sf::Font capture_it;
    capture_it.loadFromFile("Capture_it.ttf");

    sf::Text text_player_name;
    sf::Text text_name;
    sf::Text text_score;
    text_player_name.setFont(capture_it);
    text_player_name.setFillColor(sf::Color::White);
    text_player_name.setCharacterSize(60);
    text_player_name.setPosition(650.0, 465.0);
    text_name.setFont(capture_it);
    text_name.setFillColor(sf::Color::White);

    sf::RenderWindow window(sf::VideoMode(resolution_x, resolution_y), "Air Battle");
    window.setFramerateLimit(60);

//    Wektory
    std::vector<std::unique_ptr<Game>> enemies;
    std::vector<std::unique_ptr<Game>> bullets;
    std::vector<std::unique_ptr<Game>> crates;
    std::vector<std::unique_ptr<Explosion>> explosions;

//    Tekstury
    sf::Texture tex_main_menu = load_texture("img/main_menu.png");
    sf::Texture tex_main_menu_graj = load_texture("img/main_menu_1.png");
    sf::Texture tex_main_menu_ranking = load_texture("img/main_menu_2.png");
    sf::Texture tex_main_menu_jakgrac = load_texture("img/main_menu_3.png");
    sf::Texture tex_main_menu_wyjscie = load_texture("img/main_menu_4.png");
    sf::Texture tex_ranking = load_texture("img/ranking_1.png");
    sf::Texture tex_ranking_menu = load_texture("img/ranking_2.png");
    sf::Texture tex_jakgrac = load_texture("img/jak_grac_1.png");
    sf::Texture tex_jakgrac_menu = load_texture("img/jak_grac_2.png");
    sf::Texture tex_game_over_n = load_texture("img/game_over_n.png");
    sf::Texture tex_game_over_n_menu = load_texture("img/game_over_n_menu.png");
    sf::Texture tex_game_over_y = load_texture("img/game_over_y.png");
    sf::Texture tex_game_over_y_menu = load_texture("img/game_over_y_menu.png");
    sf::Texture tex_player_plane = load_texture("img/player_plane.png");
    sf::Texture tex_enemy_plane_red = load_texture("img/enemy_plane_red.png");
    sf::Texture tex_enemy_plane_gray = load_texture("img/enemy_plane_gray.png");
    sf::Texture tex_bullet = load_texture("img/bullet.png");
    sf::Texture tex_crate_speed = load_texture("img/crate_speed.png");
    sf::Texture tex_crate_dmg = load_texture("img/crate_dmg.png");
    sf::Texture tex_explosion = load_texture("img/explosion_frames.png");
    sf::Texture tex_sea = load_texture("img/sea.png");
    tex_sea.setRepeated(true);

//    Stworzenie menu gry
    sf::Sprite menu;

//    Ustawienie ikony
    sf::Image icon;
    icon.loadFromFile("img/player_plane.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

//    Obiekty
    Player player(tex_player_plane, resolution_x, resolution_y, 100, 400);

    sf::Sprite sea;
    sea.setTexture(tex_sea);
    sea.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y + 300));
    sea.setPosition(0, -300);

//    Wczytanie rankingu
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

//    Pętla
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

//    Logika
        sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

//    Obsluga menu glownego
        if(main_menu)
        {
            menu.setTexture(tex_main_menu);
            if(mouse_pos.x >= 617 && mouse_pos.x <= 747 && mouse_pos.y >= 463 && mouse_pos.y <= 505)
            {
                menu.setTexture(tex_main_menu_graj);

                if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {
                    main_menu = false;
                    playerInput = "";
                    clock.restart();
                }
            }
            if(mouse_pos.x >= 564 && mouse_pos.x <= 801 && mouse_pos.y >= 527 && mouse_pos.y <= 569)
            {
                menu.setTexture(tex_main_menu_ranking);

                if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {
                    main_menu = false;
                    menu_ranking = true;

                    v_name.clear();
                    v_score.clear();

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
            }
            if(mouse_pos.x >= 550 && mouse_pos.x <= 815 && mouse_pos.y >= 582 && mouse_pos.y <= 636)
            {
                menu.setTexture(tex_main_menu_jakgrac);

                if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {
                    main_menu = false;
                    menu_jakgrac = true;
                    clock.restart();
                }
            }
            if(mouse_pos.x >= 570 && mouse_pos.x <= 796 && mouse_pos.y >= 649 && mouse_pos.y <= 703)
            {
                menu.setTexture(tex_main_menu_wyjscie);

                if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {
                    window.close();
                }
            }
        }

//    Obsluga rankingu
        if(menu_ranking)
        {
            menu.setTexture(tex_ranking);

            if(mouse_pos.x >= 1165 && mouse_pos.x <= 1293 && mouse_pos.y >= 678 && mouse_pos.y <= 713)
            {
                menu.setTexture(tex_ranking_menu);

                if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {
                    main_menu = true;
                    menu_ranking = false;
                }
            }
        }

//    Obsluga sekcji "jak grac"
        if(menu_jakgrac)
        {
            menu.setTexture(tex_jakgrac);

            if(mouse_pos.x >= 1165 && mouse_pos.x <= 1293 && mouse_pos.y >= 678 && mouse_pos.y <= 713)
            {
                menu.setTexture(tex_jakgrac_menu);

                if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {
                    main_menu = true;
                    menu_jakgrac = false;
                }
            }
        }

//    Obsluga okna po zakonczonej grze
        if(game_over)
        {
            std::stringstream conv;
            conv << player.get_player_score();
            text_name.setString(conv.str());
            text_name.setCharacterSize(85);

            if(record)
            {
                menu.setTexture(tex_game_over_y);

                text_name.setPosition(984.0, 190.0);

                if (event.type == sf::Event::TextEntered)
                {
                    if((event.text.unicode > 64 && event.text.unicode < 91) || (event.text.unicode > 96 && event.text.unicode < 123) || event.text.unicode == 8)
                    {
                        sf::Time typing = clock.restart();

                        if(typing.asSeconds() > 0.018)
                        {
                            if(event.text.unicode == 8 && playerInput.getSize() >= 1)
                            {
                                playerInput.erase(playerInput.getSize() - 1, 1);
                                text_player_name.setString(playerInput);
                            }
                            else
                            {
                                if(event.text.unicode != 8)
                                {
                                    playerInput += event.text.unicode;
                                    text_player_name.setString(playerInput);
                                }
                            }
                        }
                    }
                }

                if(mouse_pos.x >= 1165 && mouse_pos.x <= 1293 && mouse_pos.y >= 678 && mouse_pos.y <= 713)
                {
                    menu.setTexture(tex_game_over_y_menu);

                    if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                    {
                        game_over = false;
                        main_menu = true;
                        player_name = playerInput;
                        player.update_ranking(player_name, v_name, v_score);
                        player.restart_game();
                        enemies.clear();
                        bullets.clear();
                        player.setPosition((resolution_x/2) - player.getGlobalBounds().width/2, resolution_y - 178);
                    }
                }
            }
            else
            {
                menu.setTexture(tex_game_over_n);

                text_name.setPosition(984.0, 240.0);

                if(mouse_pos.x >= 1165 && mouse_pos.x <= 1293 && mouse_pos.y >= 678 && mouse_pos.y <= 713)
                {
                    menu.setTexture(tex_game_over_n_menu);

                    if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                    {
                        game_over = false;
                        main_menu = true;
                        player.restart_game();
                        enemies.clear();
                        bullets.clear();
                        player.setPosition((resolution_x/2) - player.getGlobalBounds().width/2, resolution_y - 178);
                    }
                }
            }

        }

//    Obsluga gry
        if(!main_menu && !menu_ranking && !menu_jakgrac && !menu_exit && !game_over)
        {
//    Ruch morza
            sf::Time elapsed = clock.restart();
            sea.move(0, 35 * elapsed.asSeconds());
            if(sea.getPosition().y >= -150)
            {
                sea.setPosition(0, -300);
            }

//    Strzelanie
            if(player.get_shooting_time() <= player.get_sum_of_time())
            {
                bullets.emplace_back(std::make_unique<Bullet>(tex_bullet, player.getGlobalBounds()));
                player.reset_sum_of_time();
            }
            else
            {
                player.update_sum_of_time(elapsed);
            }

//    Zderzenie z przeciwnikiem lub przepuszczenie przeciwnika konczy gre
            for(auto &i : enemies)
            {
                if(i->getGlobalBounds().intersects(player.getGlobalBounds()) || (i->getGlobalBounds().top + i->getGlobalBounds().height) >= resolution_y)
                {              
                    game_over = true;
                    record = player.new_record(v_score);
                    text_player_name.setString("");
                    break;
                }
            }

//    Zderzenie kuli z przeciwnikiem
            for(size_t i = 0; i < enemies.size(); i++)
            {
                for(size_t j = 0; j < bullets.size(); j++)
                {
                    if(bullets[j]->getGlobalBounds().intersects(enemies[i]->getGlobalBounds()))
                    {
                        Enemy *enemy = dynamic_cast<Enemy *>(enemies[i].get());
                        Bullet *bullet = dynamic_cast<Bullet *>(bullets[j].get());

                        if (enemy != nullptr)
                        {
                            if(bullet != nullptr)
                            {
                                if(enemy->get_HP() - (player_damage * player.get_crate_dmg()) < player_damage)
                                {
                                    player.add_point();
                                    player.upgrade_score_in_wave();

                                    if(rand()% 10 == 1)
                                    {
                                        int random_effect = rand()% 2;

                                        if(random_effect == 1)
                                        {
                                            crates.emplace_back(std::make_unique<Crate>(tex_crate_speed, enemy->getGlobalBounds(), random_effect));
                                        }
                                        else
                                        {
                                            crates.emplace_back(std::make_unique<Crate>(tex_crate_dmg, enemy->getGlobalBounds(), random_effect));
                                        }

                                    }

                                    auto iterator_enemy = enemies.begin() + i;
                                    enemies.erase(iterator_enemy);

                                    auto iterator_bullet = bullets.begin() + j;
                                    bullets.erase(iterator_bullet);

                                    explosions.emplace_back(std::make_unique<Explosion>(tex_explosion, enemy->getGlobalBounds()));
                                }
                                else
                                {
                                    enemy->get_damage(50 * player.get_crate_dmg());

                                    auto iterator_bullet = bullets.begin() + j;
                                    bullets.erase(iterator_bullet);
                                }
                            }
                        }
                    }
                }
            }

//    Usuwanie strzalow, ktore zblizaja sie do granicy ekranu
            for(size_t i = 0; i < bullets.size(); i++)
            {
                if(bullets[i]->getGlobalBounds().top <= 2)
                {
                    Bullet *bullet = dynamic_cast<Bullet *>(bullets[i].get());

                    if(bullet != nullptr)
                    {
                        auto iterator_bullet = bullets.begin() + i;
                        bullets.erase(iterator_bullet);
                    }
                }
            }

//    Zderzenie ze skrzynka z ulepszeniami
            for(size_t i = 0; i < crates.size(); i++)
            {
                if(crates[i]->getGlobalBounds().intersects(player.getGlobalBounds()))
                {
                    Crate *crate = dynamic_cast<Crate *>(crates[i].get());

                    if(crate != nullptr)
                    {
                        if(crate->get_effect() == 1)
                        {
                            player.set_crate_speed();
                            clock.restart();
                            player.set_is_with_effect();
                            player.reset_effect_time();
                        }
                        else
                        {
                            player.set_crate_dmg();
                            clock.restart();
                            player.set_is_with_effect();
                            player.reset_effect_time();
                        }

                        auto iterator_crate = crates.begin() + i;
                        crates.erase(iterator_crate);

                        break;
                    }
                }

//    Usuwanie skrzynek, ktore nie zostaly zebrane
                if(crates[i]->getGlobalBounds().top >= resolution_y)
                {
                    Crate *crate = dynamic_cast<Crate *>(crates[i].get());

                    if(crate != nullptr)
                    {
                        auto iterator_crate = crates.begin() + i;
                        crates.erase(iterator_crate);
                    }
                }
            }

//    Eksplozja po zniszczeniu przeciwnika
            for(size_t i = 0; i < explosions.size(); i++)
            {
                if(explosions[i]->get_current_frame() == 7)
                {
                    Explosion *explosion = dynamic_cast<Explosion *>(explosions[i].get());

                    if(explosion != nullptr)
                    {
                        auto iterator_explosion = explosions.begin() + i;
                        explosions.erase(iterator_explosion);
                    }
                }
            }

//    Obsluga efektow ulepszenia
            if(player.is_with_effect())
            {
                if(player.get_effect_time() > 10)
                {
                    player.reset_crate_effects();
                    player.reset_effect_time();
                    player.reset_is_with_effect();
                }
                else
                {
                    player.update_effect_time(elapsed);
                }
            }

//    Kolejna fala
            if(player.get_score_in_wave() == player.get_wave_size())
            {
                player.upgrade_wave_counter();

                if(player.get_waves_to_next_wave_() + 1 == player.get_wave_counter())
                {
                    player.upgrade_wave_size();
                    player.upgrade_waves_to_next_wave();
                }

                for(int i = 0; i < player.get_wave_size(); i++)
                {                   
                    int zones = resolution_x / player.get_wave_size();
                    int max = (zones * (i + 1)) - 121;
                    int min = zones * i;
                    int respawn_pos = min + rand()% (max - min + 1);

                    if(player.get_wave_counter() <= 25)
                    {
                        enemies.emplace_back(std::make_unique<Enemy>(tex_enemy_plane_red, respawn_pos, enemy_red_hp, 50));
                    }
                    else if(player.get_wave_counter() == 26)
                    {
                        player.reset_wave_size();

                        enemies.emplace_back(std::make_unique<Enemy>(tex_enemy_plane_gray, respawn_pos, enemy_gray_hp, 50));
                    }
                    else if(player.get_wave_counter() <= 40)
                    {
                        enemies.emplace_back(std::make_unique<Enemy>(tex_enemy_plane_gray, respawn_pos, enemy_gray_hp, 50));
                    }
                    else if(player.get_wave_counter() == 41)
                    {
                        player.reset_wave_size();

                        int random = rand()% 2;

                        if(random == 0)
                        {
                            enemies.emplace_back(std::make_unique<Enemy>(tex_enemy_plane_red, respawn_pos, enemy_red_hp, 50));
                        }
                        else
                        {
                            enemies.emplace_back(std::make_unique<Enemy>(tex_enemy_plane_gray, respawn_pos, enemy_gray_hp, 50));
                        }
                    }
                    else
                    {
                        int random = rand()% 2;

                        if(random == 0)
                        {
                            enemies.emplace_back(std::make_unique<Enemy>(tex_enemy_plane_red, respawn_pos, enemy_red_hp, 50));
                        }
                        else
                        {
                            enemies.emplace_back(std::make_unique<Enemy>(tex_enemy_plane_gray, respawn_pos, enemy_gray_hp, 50));
                        }
                    }
                }

                player.reset_score_in_wave();
            }

//        Animacje
            player.animate(elapsed);

            for(auto &it : bullets)
            {
                it->animate(elapsed);
            }

            for(auto &it : enemies)
            {
                it->animate(elapsed);
            }

            for(auto &it : crates)
            {
                it->animate(elapsed);
            }

            for(auto &it : explosions)
            {
                it->frame_animate(elapsed);
            }
        }

//        Wyświetlanie
        window.clear(sf::Color::Black);

        if(main_menu || menu_jakgrac)
        {
            window.draw(menu);
        }
        else if(menu_ranking)
        {
            window.draw(menu);

            for(int i = 0; i < 5; i++)
            {
                std::stringstream conv;
                conv << i + 1;
                std::string it = conv.str();

                text_name.setString(it + ". " + v_name[i] + " -> " + v_score[i]);
                text_name.setPosition(525.0, 236.0 + (75.0 * i));
                text_name.setCharacterSize(60);
                window.draw(text_name);
            }
        }
        else if(game_over)
        {
            window.draw(menu);
            window.draw(text_name);
            window.draw(text_player_name);
        }
        else
        {
            window.draw(sea);

            for(auto &it : enemies)
            {
                window.draw(*it);
            }

            for(auto &it : bullets)
            {
                window.draw(*it);
            }

            for(auto &it : crates)
            {
                window.draw(*it);
            }

            for(auto &it : explosions)
            {
                window.draw(*it);
            }

            std::stringstream conv;
            conv << player.get_player_score();
            text_name.setString("Wynik: " + conv.str());
            text_name.setCharacterSize(30);
            text_name.setPosition(20.0, 15.0);

            window.draw(player);
            window.draw(text_name);
        }

        window.display();
    }

    return 0;
}
