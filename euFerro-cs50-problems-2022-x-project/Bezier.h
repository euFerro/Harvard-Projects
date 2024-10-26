//
//  CurvaBezier.h
//  OpenGL

#ifndef Bezier_h
#define Bezier_h

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

class Bezier
{
    Point Coords[3];
    //int Indices[3];

public:
    float ComprimentoTotalDaCurva;
    int cor;

    Bezier();
    Bezier(Point P0, Point P1, Point P2);
    Bezier(Point V[]);
    Point Calcula(double t);
    Point getPC(int i);
    void desenha();
    double CalculaT(double distanciaPercorrida);
    void calculaComprimentoDaCurva();
};

#endif
