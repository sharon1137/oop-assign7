// TODO 
// Finish the declaration of GameObjectFactory that
// 1. offers some methods to create a GameObject.
// 2. encapsulates the constructor from the caller. 
#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H


#include "gameObject.h"
#include <memory>

class GameObjectFactory {
public:
    // 建立一個靜止藍色方塊
    static GameObject* createBlueBox(int x, int y);

    // 建立一個紅色的玩家（可擴充為 Player 子類）
    static GameObject* createRedPlayer(int x, int y);
};

#endif

