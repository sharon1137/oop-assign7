// TODO implementation
#include "gameObjectFactory.h"
#include "unit.h"
#include "icon.h"

// 建立藍色靜止方塊
GameObject* GameObjectFactory::createBlueBox(int x, int y) {
    GameObject* obj = new GameObject();
    obj->setPosition(Position{x, y});
    obj->setIcon(Icon{
        { Cell(Color::CYAN, "OO") }//obstacle
    });
    return obj;
}

// 建立紅色可移動方塊（玩家）
GameObject* GameObjectFactory::createRedPlayer(int x, int y) {
    GameObject* obj = new GameObject();
	obj->setPosition(Position{x, y});
    obj->setIcon(Icon{
        { Cell(Color::RED, "PP")}//player
    });
    return obj;
}


