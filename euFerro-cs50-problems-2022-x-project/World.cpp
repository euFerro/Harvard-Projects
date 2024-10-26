//
//  World.cpp
//
//  Created by Breno Ferro 10/29/2022
//

#include "Object.h"
#include "Point.h"
#include "ColorListRGB.h"
#include "World.h"

World::World()
{
    Min = Point(-10.0f, -10.0f, 10.0f);
    Max = Point(10.0f, 10.0f, 10.0f);
    basisX = Point(1.0f, 0.0f, 0.0f);
    basisY = Point(0.0f, 1.0f, 0.0f);
    basisZ = Point(0.0f, 0.0f, 1.0f);
    // Center Cursor
    Cursor.put(Point(0.0, 0.0, 0.0));
}

Point World::getMax()
{
    return Max;
}

void World::setGridSize(float size)
{
    if (size < 0.0f)
    {
        return;
    }
    Min = Point(-size, -size, -size);
    Max = Point(size, size, size);
}

Point World::getCursor()
{
    return this->Cursor.getVertex(0);
}

void World::setCursor(Point new_pos)
{
    this->Cursor.alterVertex(0, new_pos);
}

void World::createWorldGrid()
{
    // Horizon grid
    for (int i = Min.z; i <= Max.z; i++)
    {
        if (i == 0)
        {
            i++;
        }
        WorldGrid.put(Point(Min.x, 0.0, i));
        WorldGrid.put(Point(Max.x, 0.0, i));
        WorldGrid.put(Point(i, 0.0, Min.z));
        WorldGrid.put(Point(i, 0.0, Max.z));
    }

    // Middle X axis
    X_Axis.put(Point(Min.x, 0.0, 0.0));
    X_Axis.put(Point(Max.x, 0.0, 0.0));

    // Middle Y Axis
    Y_Axis.put(Point(0.0, Min.y, 0.0));
    Y_Axis.put(Point(0.0, Max.y, 0.0));

    // Middle Z axis
    Z_Axis.put(Point(0.0, 0.0, Min.z));
    Z_Axis.put(Point(0.0, 0.0, Max.z));
}

void World::paintWorldGrid()
{
    // Horizon Grid
    glColor3f(0.3f, 0.3f, 0.3f);
    WorldGrid.paintEdges();

    // Middle Axis
    //  X axis
    defineColor(LightRed);
    X_Axis.paintEdge(0);
    // Y axis
    // defineColor(LightBlue);
    // Y_Axis.paintEdges();
    // Z axis
    defineColor(LightGreen);
    Z_Axis.paintEdge(0);

    // Center Cursor (Orange Point)
    defineColor(Orange);
    Cursor.paintVertices(6.0f);
}
