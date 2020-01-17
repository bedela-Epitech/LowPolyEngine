//
// Created by adrien on 17/01/20.
//

#ifndef INC_71K2LEDEB_QUADTREE_H
#define INC_71K2LEDEB_QUADTREE_H

#include "map/Chunk.h"

class QuadTree
{
private:
    Chunk   _chunk;
    std::shared_ptr<QuadTree> _north;
    std::shared_ptr<QuadTree> _east;
    std::shared_ptr<QuadTree> _south;
    std::shared_ptr<QuadTree> _west;

    std::shared_ptr<QuadTree> _northEast;
    std::shared_ptr<QuadTree> _northWest;
    std::shared_ptr<QuadTree> _southEast;
    std::shared_ptr<QuadTree> _southWest;
};

#endif //INC_71K2LEDEB_QUADTREE_H
