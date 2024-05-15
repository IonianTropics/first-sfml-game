#ifndef GAME_KNIGHT_H_
#define GAME_KNIGHT_H_

#include <SFML/Graphics.hpp>

#include "AnimatedSprite.h"

namespace game {
class Knight: public sf::Drawable, public sf::Transformable {
    public:
        bool load();

        void update_input();

        void update_physics(float delta, sf::FloatRect world_rects[], int world_rect_count);

        void move_and_slide(float delta, int world_rect_count, sf::FloatRect world_rects[]);

        void update_graphics();

        sf::FloatRect get_local_bounds();

        sf::FloatRect get_global_bounds();

    private:
        float _direction;
        bool _space_held;
        bool _space_just_pressed;
        bool _space_just_released;

        sf::FloatRect _collision_rect;
        sf::Vector2f _velocity;
        float _max_speed;
        float _acceleration;
        float _max_air_speed;
        float _air_acceleration;
        float _gravity;
        float _jump_impulse;
        float _terminal_velocity;
        bool _on_ground;

        AnimatedSprite _animated_sprite;
        float _animation_speed;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
} // namespace game

#endif // GAME_KNIGHT_H_
