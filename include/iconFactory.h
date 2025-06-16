// TODO 
// Finish the declaration of IconFactory that
// 1. offers some methods to create an Icon.
// 2. encapsulates the constructor from the caller.
#ifndef ICON_FACTORY_H
#define ICON_FACTORY_H

#include "icon.h"

class IconFactory {
public:
    static Icon createRedPlayer();
    static Icon createBluePlayer();
    static Icon createWall();
};

#endif
 
