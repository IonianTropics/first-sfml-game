#include "Platform.h"

namespace game {
bool Platform::load(int size, int season) {
    if (!_texture.loadFromFile("../../../assets/sprites/platforms.png")) {
        return false;
    }

    _size = size;
    _season = season;

    _sprite.setTexture(_texture);
    _sprite.setTextureRect(sf::IntRect((_size - 1) * 16, _season * 16, 16 * _size, 16));

    _collision_rect = sf::FloatRect(0.f, 0.f, 16.f * _size, 8.f);
    return true;
}

sf::FloatRect Platform::get_local_bounds() {
    return _collision_rect;
}

sf::FloatRect Platform::get_global_bounds() {
    return getTransform().transformRect(get_local_bounds());
}

void Platform::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &_texture;
    target.draw(_sprite, states);
}
} // namespace game
