#ifndef GAME_ANIMATED_SPRITE_H_
#define GAME_ANIMATED_SPRITE_H_

#include <SFML/Graphics.hpp>

namespace game {
class AnimatedSprite: public sf::Drawable, public sf::Transformable {
    public:
        bool load(
            const std::string sprite_sheet_path,
            int sprite_width,
            int sprite_height,
            int sheet_width,
            int sheet_height,
            int start_index,
            int frame_count,
            float frame_duration
        );
        bool flip_h;
        
        void update();

        void set_animation(int start_index, int frame_count, float frame_duration);

        sf::FloatRect get_local_bounds() const;

        sf::FloatRect get_global_bounds() const;
    private:
        float _frame_duration;
        int _start_index;
        int _frame_count;
        sf::Clock _animation_clock;
        int _animation_index;

        int _sprite_index;
        int _sprite_left;
        int _sprite_top;
        int _sprite_width;
        int _sprite_height;
        sf::Sprite _sprite;
        sf::Texture _sprite_sheet;

        int _sheet_width;
        int _sheet_height;

        void _update_sprite();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
} // namespace game

#endif // GAME_ANIMATED_SPRITE_H_
