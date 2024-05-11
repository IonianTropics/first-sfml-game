#ifndef GAME_TILE_MAP_
#define GAME_TILE_MAP_

#include <SFML/Graphics.hpp>

namespace game {
class TileMap: public sf::Drawable, public sf::Transformable {
    public:
        bool load(
            const std::string& tileset,
            sf::Vector2u tileSize,
            const int* tiles,
            unsigned int width,
            unsigned int height
        );
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            // apply the transform
            states.transform *= getTransform();

            // apply the tileset texture
            states.texture = &m_tileset;

            // draw the vertex array
            target.draw(m_vertices, states);
        }
        sf::VertexArray m_vertices;
        sf::Texture m_tileset;
};
} // namespace game

#endif  // GAME_TILE_MAP_