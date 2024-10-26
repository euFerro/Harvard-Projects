//
//  World.h
//
//  Created by Breno Ferro 10/29/2022
//

#ifndef __World__
#define __World__

#include "Point.h"
#include "Object.h"
#include <vector>

class World
{
    // Logical Limits of the World Space)
    Point Min, Max;
    // Grid size
    unsigned int GridSize;
    // World Grid
    Object WorldGrid, X_Axis, Y_Axis, Z_Axis, Cursor;
    // World basis vectors
    Point basisX, basisY, basisZ;
    // World Objects
    vector<Object> objects;

public:
    World();
    Point getMax();
    void setGridSize(float size);
    void createWorldGrid();
    void paintWorldGrid();
    Point getCursor();
    void setCursor(Point);
};

#endif