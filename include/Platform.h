#ifndef GAME_PLATFORM_H_
#define GAME_PLATFORM_H_

#include <SFML/Graphics.hpp>

namespace game {
class Platform: public sf::Drawable, public sf::Transformable {
    public:
        bool load(int size, int season);
        sf::FloatRect get_local_bounds();
        sf::FloatRect get_global_bounds();
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        sf::Sprite _sprite;
        sf::Texture _texture;
        int _size;
        int _season;
        sf::FloatRect _collision_rect;
};
} // namespace game

#endif // GAME_PLATFORM_H_
