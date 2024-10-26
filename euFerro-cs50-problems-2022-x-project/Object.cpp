//
//  Object.cpp
//
//  Created by Breno Ferro 10/29/2022
//

#include <iostream>
#include <fstream>
using namespace std;

#include "Object.h"

// Constructor ------------------------------------------------------------------------------------
Object::Object()
{
    this->name = "Object";
}

// Manipulation -----------------------------------------------------------------------------------
void Object::put(Point p)
{
    Vertices.push_back(p);
}

void Object::put(Point p, int pos)
{
    if ((pos < 0) || (pos > Vertices.size()))
    {
        cout << "ERROR: " << __FUNCTION__ << " (Invalid Position)"<< endl;
        return;
    }
    Vertices.insert(Vertices.begin() + pos, p);
}

string Object::getName()
{
    return this->name;
}

Point Object::getVertex(int i)
{
    return Vertices[i];
}

void Object::alterVertex(int i, Point P)
{
    Vertices[i] = P;
}

void Object::getEdge(int n, Point &P1, Point &P2)
{
    P1 = Vertices[n];
    int n1 = (n + 1) % Vertices.size();
    P2 = Vertices[n1];
}

unsigned long Object::getSize()
{
    return Vertices.size();
}

// Painting functions -----------------------------------------------------------------------------
void Object::paintVertices(float pointSize)
{
    glPointSize(pointSize);
    glBegin(GL_POINTS);
    for (int i = 0; i < Vertices.size(); i++)
        glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
    glEnd();
}

void Object::paintWireframe()
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < Vertices.size(); i++)
        glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
    glEnd();
}

void Object::paintEdges()
{
    glBegin(GL_LINES);
    for (int i = 0; i < Vertices.size(); i++)
        glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
    glEnd();
}

void Object::paintEdge(int n)
{
    glBegin(GL_LINES);
    glVertex3f(Vertices[n].x, Vertices[n].y, Vertices[n].z);
    int n1 = (n + 1) % Vertices.size();
    glVertex3f(Vertices[n1].x, Vertices[n1].y, Vertices[n1].z);
    glEnd();
}

void Object::paintFaces()
{
    glBegin(GL_POLYGON);
    for (int i = 0; i < Vertices.size(); i++)
        glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
    glEnd();
}

void Object::paintTriangleStrip()
{
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i < Vertices.size(); i++)
        glVertex3f(Vertices[i].x, Vertices[i].y, Vertices[i].z);
    glEnd();
}

// Debug ------------------------------------------------------------------------------------------
void Object::debug()
{
    for (int i = 0; i < Vertices.size(); i++)
        Vertices[i].debug();
}

// Object Limits ----------------------------------------------------------------------------------
void Object::getExtremes(Point &Min, Point &Max)
{
    Max = Min = Vertices[0];

    for (int i = 0; i < Vertices.size(); i++)
    {
        Min = getMin(Vertices[i], Min);
        Max = getMax(Vertices[i], Max);
    }
}

// Load txt Object ------------------------------------------------------------------------------------
void Object::LoadObject(string filename)
{
    ifstream input;                // ofstream arq;
    input.open(filename, ios::in); // arq.open(filename, ios::out);
    if (!input)
    {
        cout << "ERROR: " << __FUNCTION__ << " (Couldn't load file)" << endl;
        return;
    }
    cout << "Loading txt Object " << filename << "..." << endl;
    string S;
    unsigned int totalVertices;

    input >> totalVertices; // arq << totalVertices

    for (int i = 0; i < totalVertices; i++)
    {
        double x, y, z;
        // Reads every line element
        input >> x >> y >> z;
        if (!input)
            break;
        put(Point(x, y, z));
    }
    cout << "Done!" << endl;
}

//  Transformations
void Object::rotationX(float deg)
{
    for (int i = 0; i < Vertices.size(); i++)
    {
        Vertices[i].rotateX(deg);
    }
}

void Object::rotationY(float deg)
{
    for (int i = 0; i < Vertices.size(); i++)
    {
        Vertices[i].rotateY(deg);
    }
}

void Object::rotationZ(float deg)
{
    for (int i = 0; i < Vertices.size(); i++)
    {
        Vertices[i].rotateZ(deg);
    }
}