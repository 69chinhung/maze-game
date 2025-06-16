#include "gameObject.h"
#include "environment.h"

GameObject::GameObject(Icon icon, Position pos) : _icon(icon), _pos(pos) {
    _dir = NONE;
}

GameObject::~GameObject() {}

void GameObject::update() {
    if (_dir == UP) {
        _pos.y()--;
    } else if (_dir == LEFT) {
        _pos.x()--;
    } else if (_dir == DOWN) {
        _pos.y()++;
    } else if (_dir == RIGHT) {
        _pos.x()++;
    }
    _dir = NONE; 
}

void GameObject::setDirection(Direction dir) { 
    _dir = dir; 
}
