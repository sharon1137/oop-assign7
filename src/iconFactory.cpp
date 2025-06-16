// TODO implementation
#include "iconFactory.h"

// 紅色
Icon IconFactory::createRedPlayer() {
    return Icon{{
        Cell(Color::RED, " ")
    }};
}

// 藍色
Icon IconFactory::createBluePlayer() {
    return Icon{{
        Cell(Color::BLUE, " ")
    }};
}

// 牆
Icon IconFactory::createWall() {
    return Icon{{
        Cell(Color::WHITE, " ")
    }};
}

