#ifndef CLASS_H
#define CLASS_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Game : public sf::Sprite
{
private:
    int player_score_ = 0;
    int wave_size_ = 1;
    int wave_counter_ = 0;
    int waves_to_next_wave_ = 5;
    int score_in_wave_ = 1;

    float shooting_time_ = 0.4;
    float sum_of_time_ = 0.35;

    float crate_speed_ = 1;
    float crate_shoot_ = 1.5;
    int crate_dmg_ = 1;

    float effect_time_ = 0;
    bool is_effect = false;

public:
    Game() : Sprite() {};
    virtual ~Game() = default;
    virtual void animate(const sf::Time &elapsed) = 0;

    int window_bound_left;
    int window_bound_right;
    int window_bound_top;
    int window_bound_bottom;
    void setWindowBounds(int, int, int, int);

    int get_player_score();
    int get_wave_size();
    int get_wave_counter();
    int get_waves_to_next_wave_();
    int get_score_in_wave();

    float get_crate_speed();
    float get_crate_shoot();
    int get_crate_dmg();
    void reset_crate_effects();

    void set_crate_speed();
    void set_crate_dmg();

    float get_effect_time();
    float update_effect_time(const sf::Time &elapsed);
    void reset_effect_time();

    bool is_with_effect();
    void set_is_with_effect();
    void reset_is_with_effect();

    void add_point();
    void upgrade_wave_size();
    void reset_wave_size();
    void upgrade_wave_counter();
    void upgrade_waves_to_next_wave();
    void upgrade_score_in_wave();
    void reset_score_in_wave();
    void reset_waves_to_next_wave();

    float get_sum_of_time();
    float update_sum_of_time(const sf::Time &elapsed);
    void reset_sum_of_time();
    float get_shooting_time();

    bool new_record(std::vector<std::string> v_score);
    void restart_game();
    void read_ranking(std::vector<std::string> v_name, std::vector<std::string> v_score);
    void update_ranking(std::string player_name, std::vector<std::string> v_name, std::vector<std::string> v_score);
    void unable_fast_waves();
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

class Crate : public Game
{
private:
    int crate_speed_ = 75;
    int effect_;
    bool first_crate = true;

public:
    Crate() {};
    Crate(sf::Texture &texture, sf::FloatRect enemy_bounds, int effect);
    void animate(const sf::Time &elapsed);
    int get_effect();
    void change_first_crate();
};

class Explosion : public Game
{
private:
    std::vector<sf::IntRect> frames_of_animation;
    size_t current_frame = 0;
    float sum_of_time = 0;

public:
    Explosion(const sf::Texture &texture, sf::FloatRect enemy_bounds);
    void animate(const sf::Time &elapsed) {};
    void add_frame(const sf::IntRect &frame);
    void frame_animate(const sf::Time &elapsed);
    size_t get_current_frame();
};

class Enemy : public Game
{
private:
    int HP_;
    int speed_;

public:
    Enemy(sf::Texture &texture, int respawn_pos, int HP, int speed);
    void animate(const sf::Time &elapsed);

    int get_HP();
    int get_damage(int damage);
};



#endif // CLASS_H
