#ifndef GAME_TILE_MAP_
#define GAME_TILE_MAP_

#include <SFML/Graphics.hpp>

namespace game {
class Entity: public sf::Drawable, public sf::Transformable {
    public:
        
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            states.transform *= getTransform();
            states.texture = &m_texture;
            target.draw(m_vertices, states);
        }
        sf::VertexArray m_vertices;
        sf::Texture m_texture;
};
} // namespace game


#endif // GAME_TILE_MAP_
