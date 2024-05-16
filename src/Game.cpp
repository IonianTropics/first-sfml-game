#include "Game.h"

namespace game {
Game::Game() {
    _window.create(sf::VideoMode(WIDTH, HEIGHT), TITLE);
    _window.setFramerateLimit(FRAMERATE);
    _window.setVerticalSyncEnabled(VSYNC);

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

    if (!_platform.load(2, 3)) {
        exit(EXIT_FAILURE);
    }
    _platform.setPosition(196.f, 208.f);
    _world_rects[10] = _platform.get_global_bounds();

    if (!_knight.load()) {
        exit(EXIT_FAILURE);
    }

    if (!_music.openFromFile("../../../assets/music/time_for_adventure.mp3")) {
        exit(EXIT_FAILURE);
    }
    _music.setLoop(true);
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
        
        while (lag > SECONDS_PER_UPDATE) {
            _knight.update_input();
            _knight.update_physics(SECONDS_PER_UPDATE, _world_rects, _world_rect_count);
            lag -= SECONDS_PER_UPDATE;
        }
        
        _knight.update_sound();
        _knight.update_graphics();
        
        _window.setView(_window.getDefaultView());
        _window.clear();
        _window.draw(_background);
        
        // _window.setView(_knight.camera);
        _window.draw(_world);
        _window.draw(_platform);
        _window.draw(_knight);
        _window.display();
    }
}
} // namespace game
