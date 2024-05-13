#include "Knight.h"

#include <algorithm>

namespace game {

bool Knight::load() {
    if (!_animated_sprite.load(
        "../../../assets/sprites/knight.png",
        32, 32, 
        8, 8,
        0, 4,
        .25f
    )) {
        return false;
    }

    _velocity = sf::Vector2f();
    _max_speed = 100.f;
    _acceleration = 1000.f;
    _gravity = 120.f;
    _jump_impulse = 120.f;

    _direction = 0.f;
    _space_held = false;
    _space_just_pressed = false;
    _space_just_released = false;
    return true;
}

void Knight::update_input() {
    _direction = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        _direction -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        _direction += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (!_space_held) {
            _space_just_pressed = true;
        } else {
            _space_just_pressed = false;
        }
        _space_held = true;
    } else {
        if (_space_held) {
            _space_just_released = true;
        } else {
            _space_just_released = false;
        }
        _space_held = false;
    }
}

void Knight::update_physics(float delta) {
    // TODO: add ground check
    _velocity.y += delta * _gravity;
    if (_space_just_pressed) {
        _velocity.y = -_jump_impulse;
    }
    if (_direction) {
        _velocity.x += delta * _acceleration * _direction;
        if (_velocity.x > 0.f) {
            _velocity.x = std::min(_velocity.x, _max_speed);
        } else if (_velocity.x < 0.f) {
            _velocity.x = std::max(_velocity.x, -_max_speed);
        }
    } else {
        if (_velocity.x > 0.f) {
            _velocity.x -= delta * _acceleration;
            _velocity.x = std::max(_velocity.x, 0.f);
        } else if (_velocity.x < 0.f) {
            _velocity.x += delta * _acceleration;
            _velocity.x = std::min(_velocity.x, 0.f);
        }
    }
    this->move(delta * _velocity);
}

void Knight::update_graphics() {
    if (_velocity.x < 0.f) {
        _animated_sprite.flip_h = true;
    } else if (_velocity.x > 0.f) {
        _animated_sprite.flip_h = false;
    }
    _animated_sprite.update();
}
} // namespace game
