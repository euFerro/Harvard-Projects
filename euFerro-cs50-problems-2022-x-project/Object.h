//
//  Object.cpp
//
//  Created by Breno Ferro 10/29/2022
//

#ifndef __Object__
#define __Object__

#include <iostream>
using namespace std;

#ifdef WIN32
#include <windows.h>
#include <GL/glut.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

#include "Point.h"
#include <vector>

class Object
{
    vector<Point> Vertices;
    Point Min, Max;
    string name;

public:
    // Constructor
    Object();
    // Manipulation
    void put(Point);
    void put(Point p, int pos);
    string getName();
    Point getVertex(int);
    void alterVertex(int i, Point P);
    void getEdge(int i, Point &P1, Point &P2);
    unsigned long getSize();
    // Paint functions (display)
    void paintVertices(float pointSize);
    void paintWireframe();
    void paintEdges();
    void paintEdge(int n);
    void paintFaces();
    void paintTriangleStrip();
    // Terminal Debug
    void debug();
    // Limits
    void getExtremes(Point &Min, Point &Max);
    void updateExtremes();
    // Load txt Object
    void LoadObject(string filename);
    //  Transformations
    void rotationX(float deg);
    void rotationY(float deg);
    void rotationZ(float deg);
};

#endif
