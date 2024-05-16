#include "Game.h"

namespace game {
Game::Game() {
    _window.create(sf::VideoMode(WIDTH, HEIGHT), TITLE);
    _window.setFramerateLimit(FRAMERATE);

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

void Game::run() {
    float lag = 0.f;
    _music.play();
    _clock.restart();

    while (_window.isOpen()) {
        lag += _clock.getElapsedTime().asSeconds();
        _clock.restart();

        for (sf::Event event; _window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }
        }
        _knight.update_input();

        while (lag > SECONDS_PER_UPDATE) {
            _knight.update_physics(SECONDS_PER_UPDATE, _world_rects, _world_rect_count);
            lag -= SECONDS_PER_UPDATE;
        }
        
        _knight.update_graphics();
        _window.clear();
        _window.draw(_background);
        _window.draw(_world);
        _window.draw(_knight);
        _window.display();
    }
}
} // namespace game
