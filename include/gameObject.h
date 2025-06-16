#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include "unit.h"
#include "icon.h"
#include <iostream>
class GameObject{

public:
    Position getPosition() const;
	void setPosition(const Position& pos);
    Icon getIcon() const;
	void setIcon(const Icon& icon);
	virtual void update();
	bool intersects(const GameObject* other) const;
	virtual void onCollision(GameObject* other);
    void incrementCollision() { _collisionCount++; }
    int getCollisionCount() const { return _collisionCount; }
    void resetCollision() { _collisionCount = 0; }
protected:
    Position _pos;
	Position _prevPos;   //移動前的位置
    Icon _icon;
	int _collisionCount = 0;
};

#endif
