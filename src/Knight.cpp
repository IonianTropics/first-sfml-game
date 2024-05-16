#include "Knight.h"

#include <algorithm>

namespace game {
// public
bool Knight::load() {
    if (!_animated_sprite.load(
        "../../../assets/sprites/knight.png",
        32, 32, 
        8, 8,
        0, 4,
        .15f
    )) {
        return false;
    }

    if (!_jump_sound_buffer.loadFromFile("../../../assets/sounds/jump.wav")) {
        return false;
    }

    _jump_sound.setBuffer(_jump_sound_buffer);

    if (!_tap_sound_buffer.loadFromFile("../../../assets/sounds/tap.wav")) {
        return false;
    }

    _tap_sound.setBuffer(_tap_sound_buffer);
    _tap_sound_clock.restart();
    _tap_sound_pause = 0.4f;

    _direction = 0.f;
    _space_held = false;
    _space_just_pressed = false;
    _space_just_released = false;

    _collision_rect = sf::FloatRect(13.f, 18.f, 6.f, 9.f);
    _velocity = sf::Vector2f();
    _max_speed = 90.f;
    _acceleration = 1080.f;

    _max_air_speed = 75.f;
    _air_acceleration = 720.f;
    _gravity = 240.f;
    _jump_impulse = 160.f;
    _terminal_velocity = 400.f;
    _on_ground = false;

    _animation_speed = 0.1f;

    return true;
}

void Knight::update_input() {
    // TODO: add roll
    _direction = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        setPosition(sf::Vector2f());
        _velocity = sf::Vector2f();
    }
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

void Knight::update_physics(float delta, const sf::FloatRect world_rects[], int world_rect_count) {
    _velocity.y += delta * _gravity;
    _velocity.y = std::min(_velocity.y, _terminal_velocity);

    if (_on_ground) {
        if (_space_just_pressed) {
            _jump_sound.play();
            _velocity.y = -_jump_impulse;
            _on_ground = false;
            _gravity = 300.f;
        } else {
            _gravity = 600.f;
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
    } else {
        if (_space_just_released) {
            _gravity = 600.f;
        }
        if (_direction) {
            _velocity.x += delta * _air_acceleration * _direction;
            if (_velocity.x > 0.f) {
                _velocity.x = std::min(_velocity.x, _max_air_speed);
            } else if (_velocity.x < 0.f) {
                _velocity.x = std::max(_velocity.x, -_max_air_speed);
            }
        } else {
            if (_velocity.x > 0.f) {
                _velocity.x -= delta * _air_acceleration;
                _velocity.x = std::max(_velocity.x, 0.f);
            } else if (_velocity.x < 0.f) {
                _velocity.x += delta * _air_acceleration;
                _velocity.x = std::min(_velocity.x, 0.f);
            }
        }
    }

    move_and_slide(delta, world_rects, world_rect_count);
}

void Knight::update_graphics() {
    if (_velocity.x < 0.f) {
        _animated_sprite.flip_h = true;
    } else if (_velocity.x > 0.f) {
        _animated_sprite.flip_h = false;
    }
    if (!_on_ground) {
        _animated_sprite.set_animation(16, 1, _animation_speed);
    } else {
        if (std::abs(_velocity.x) > 0.5f) {
            _animated_sprite.set_animation(16, 16, _animation_speed);
            
        } else {
            _animated_sprite.set_animation(0, 4, _animation_speed);
        }
    }
    _animated_sprite.update();
}

void Knight::update_sound() {
    if (_on_ground) {
        if (std::abs(_velocity.x) > 0.5f) {
            if (_tap_sound_clock.getElapsedTime().asSeconds() > _tap_sound_pause) {
                _tap_sound.play();
                _tap_sound_clock.restart();
            }
        }
        if (_space_just_pressed) {
            _jump_sound.play();
        }
    }
}

void Knight::move_and_slide(float delta, const sf::FloatRect world_rects[], int world_rect_count) {
    move(delta * _velocity);
    sf::FloatRect hitbox = get_global_bounds();
    sf::FloatRect intersection = sf::FloatRect();
    _on_ground = false;
    for (int i = 0; i < world_rect_count; i++) {
        if (hitbox.intersects(world_rects[i], intersection)) {
            if (intersection.width < intersection.height) {
                if (intersection.left > hitbox.left) {
                    move(sf::Vector2f(-intersection.width, 0.f));
                    _velocity.x = std::max(0.f, _velocity.x);
                } else {
                    move(sf::Vector2f(intersection.width, 0.f));
                    _velocity.x = std::min(0.f, _velocity.x);
                }
            } else {
                if (intersection.top > hitbox.top) {
                    move(sf::Vector2f(0.f, -intersection.height));
                    _velocity.y = std::min(0.f, _velocity.y);
                    _on_ground = true;
                } else {
                    move(sf::Vector2f(0.f, intersection.height));
                    _velocity.y = std::max(0.f, _velocity.y);
                }
            }
        }
    }
}

sf::FloatRect Knight::get_local_bounds() {
    return _collision_rect;
}

sf::FloatRect Knight::get_global_bounds() {
    return getTransform().transformRect(get_local_bounds());
}

void Knight::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(_animated_sprite, states);
}
} // namespace game
