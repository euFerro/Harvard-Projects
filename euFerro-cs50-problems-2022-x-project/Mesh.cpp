//
//  Mesh.cpp
//
//  Created by Breno Ferro 10/29/2022
//

#include "float.h"
#include "Object.h"
#include "Mesh.h"
#include <cmath>

void Mesh::Triangle(float scale)
{
    Point radius = Point(0.0f, 0.1f, 1.0f) * scale;

    radius.rotateY(0);
    for (int i=0; i < 360/120; i++)
    {
        this->put(radius);
        radius.rotateY(120);
    }
}

void Mesh::Square(float scale)
{
    Point radius = Point(1.0f, 0.1f, 1.0f) * scale;
    
    for (int i=0; i < 360/90; i++)
    {
        this->put(radius);
        radius.rotateY(90);
    }

}

void Mesh::Pentagon(float scale)
{   
    Point radius = Point(0.0f, 0.1f, 1.0f) * scale;

    radius.rotateY(0);
    for (int i=0; i < 360/72; i++)
    {
        this->put(radius);
        radius.rotateY(72);
    }
}

void Mesh::Hexagon(float scale)
{
    Point radius = Point(1.0f, 0.1f, 1.0f) * scale;

    radius.rotateY(45);
    for (int i=0; i < (int)360/60; i++)
    {
        this->put(radius);
        radius.rotateY(60);
    }
}

void Mesh::Circle(float scale)
{   
    Point radius = Point(1.0f, 0.1f, 1.0f) * scale;

    for (int i=0; i < (int)360/5; i++)
    {
        this->put(radius);
        radius.rotateY(5);
    }
}

void Mesh::Cube(float scale)
{
    Point radius = Point(1.0f, 1.0f, 1.0f) * scale;

    for (int i = 0; i < 4; i++)
    {
        this->put(radius * 1.0f);
        radius.rotateX(90);
    }
    for (int i = 0; i < 4; i++)
    {
        this->put(radius * -1.0f);
        radius.rotateX(90);
    }
    for (int i = 0; i < 4; i++)
    {
        this->put(radius * 1.0f);
        radius.rotateY(90);
    }
    for (int i = 0; i < 4; i++)
    {
        this->put(radius * -1.0f);
        radius.rotateY(90);
    }
    for (int i = 0; i < 4; i++)
    {
        this->put(radius * 1.0f);
        radius.rotateZ(90);
    }
    for (int i = 0; i < 4; i++)
    {
        this->put(radius * -1.0f);
        radius.rotateZ(90);
    }
}

void Mesh::Arrow3d(float scale)
{
    Point radius = Point(1.0f, 1.0f, 1.0f) * scale;

    radius.rotateY(0);
    for (int i=0; i < 360/120; i++)
    {
        this->put(radius);
        radius.rotateX(120);
    }
    for (int i=0; i < 360/120; i++)
    {
        this->put(radius * -1);
        radius.rotateX(120);
    }
    // for (int i=0; i < 360/120; i++)
    // {
    //     this->put(radius);
    //     radius.rotateY(120);
    // }
    // for (int i=0; i < 360/120; i++)
    // {
    //     this->put(radius * -1);
    //     radius.rotateY(120);
    // }
}
