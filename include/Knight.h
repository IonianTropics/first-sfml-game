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

        void update_graphics();

        sf::FloatRect get_local_bounds();

        sf::FloatRect get_global_bounds();
    private:
        float _direction;
        bool _space_held;
        bool _space_just_pressed;
        bool _space_just_released;

        AnimatedSprite _animated_sprite;

        sf::FloatRect _collision_rect;
        sf::Vector2f _velocity;
        float _max_speed;
        float _acceleration;
        float _gravity;
        float _jump_impulse;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            states.transform *= getTransform();
            target.draw(_animated_sprite, states);
        }
};
} // namespace game

#endif // GAME_KNIGHT_H_
