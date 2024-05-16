#include "Game.h"

namespace game {
// public
Game::Game() {
    if (!_background.load(
            "../../../assets/sprites/world_tileset.png",
            sf::Vector2u(16, 16),
            _background_data,
            32, 16)
        ) {
        exit(EXIT_FAILURE);
    }

    if (!_world.load(
            "../../../assets/sprites/world_tileset.png",
            sf::Vector2u(16, 16),
            _world_data,
            32, 16)
        ) {
        exit(EXIT_FAILURE);
    }
    if (!_knight.load()) {
        exit(EXIT_FAILURE);
    }

    if (!_music.openFromFile("../../../assets/music/time_for_adventure.mp3")) {
        exit(EXIT_FAILURE);
    }
    _music.setLoop(true);
    _music.setVolume(1.f);
}

void Game::run(sf::RenderWindow* window) {
    _music.play();

    while (window->isOpen()) {
        for (auto event = sf::Event{}; window->pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }
        _knight.update_input();

        _delta = _clock.getElapsedTime().asSeconds();
        _knight.update_physics(_delta, _world_rects, _world_rect_count);
        _clock.restart();

        _knight.update_graphics();

        window->clear();
        window->draw(_background);
        window->draw(_world);
        window->draw(_knight);
        window->display();
    }
}
} // namespace game
