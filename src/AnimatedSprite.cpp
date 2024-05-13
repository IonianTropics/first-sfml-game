#include "AnimatedSprite.h"
#include <iostream>

namespace game {
bool AnimatedSprite::load(
    const std::string sprite_sheet_path,
    int sprite_width,
    int sprite_height,
    int sheet_width,
    int sheet_height,
    int start_index,
    int frame_count,
    float frame_duration
) {
    if (!_sprite_sheet.loadFromFile("../../../assets/sprites/knight.png")) {
        return false;
    }
    _sprite.setTexture(_sprite_sheet);
    _start_index = start_index;
    _frame_duration = frame_duration;
    _frame_count = frame_count;

    flip_h = false;
    _animation_index = 0;

    _sprite_index = start_index;
    _sprite_width = sprite_width;
    _sprite_height = sprite_height;
    _sheet_width = sheet_width;
    _sheet_height = sheet_height;
    update_sprite();
    _animation_clock = sf::Clock();
    return true;
}

void AnimatedSprite::update() {
    if (_animation_clock.getElapsedTime().asSeconds() > _frame_duration) {
        _animation_index = (_animation_index + 1) % _frame_count;
        _sprite_index = _start_index + _animation_index;
        _animation_clock.restart();
    }
    update_sprite();
}

void AnimatedSprite::set_animation(int start_index, int frame_count, float frame_duration) {
    _start_index = start_index;
    _frame_count = frame_count;
    _frame_duration = frame_duration;
}

void AnimatedSprite::update_sprite() {
    _sprite_left = (_sprite_index % _sheet_width) * _sprite_width;
    _sprite_top = (_sprite_index / _sheet_width) * _sprite_height;
    _sprite.setTextureRect(sf::IntRect(
        _sprite_left + _sprite_width * flip_h,
        _sprite_top,
        _sprite_width - 2 * _sprite_width * flip_h,
        _sprite_height
    ));
}
} // namespace game
