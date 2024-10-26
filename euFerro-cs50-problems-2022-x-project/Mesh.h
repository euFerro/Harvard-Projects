//
//  Mesh.h
//
//  Created by Breno Ferro 10/29/2022
//

#ifndef __Shapes__
#define __Shapes__

#include "Object.h"
#include "Point.h"
#include <vector>

class Mesh : public Object
{
public:
// Shapes (generate Objects)
    void Triangle(float scale);
    void Square(float scale);
    void Pentagon(float scale);
    void Hexagon(float scale);
    void Circle(float scale);
    void Cube(float scale);
    void Arrow3d(float scale);
};

#endif