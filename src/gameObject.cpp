// TODO implementation
#include "gameObject.h"

Position GameObject::getPosition() const {
    return _pos;
}

void GameObject::setPosition(const Position& pos){
	_pos = pos;
}

Icon GameObject::getIcon() const {
    return _icon;
}

void GameObject::setIcon(const Icon& icon){
	_icon = icon;
}

void GameObject::update() {
    // 預設無，由子類別覆寫（如移動）
}

bool GameObject::intersects(const GameObject* other) const {
    return _pos.x() == other->_pos.x() && _pos.y() == other->_pos.y();
}

void GameObject::onCollision(GameObject* other) {
	if (_icon[0][0].color == Color::RED) {
    _pos = _prevPos;  // 發生碰撞時，退回上一個位置
    incrementCollision(); 
	}
}
