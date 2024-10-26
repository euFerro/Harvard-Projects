//
//  Point.h
//
//  Created by Breno Ferro 10/29/2022
//

#ifndef __Point__
#define __Point__

#include <iostream>
#include <cmath>
using namespace std;

class Point
{

public:
    float x, y, z;
    int color;
    // Constructor
    Point();
    Point(float x, float y, float z);
    void set(float x, float y, float z);
    // Terminal debug
    void debug();
    // Simple Operations
    void multiply(float x, float y, float z);
    void add(float x, float y, float z);
    void normalize();
    // Length of a Vector
    double length();
    // Rotation
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
};

// Vector Operations
Point getMax(Point P1, Point P2);
Point getMin(Point P1, Point P2);

bool operator==(Point P1, Point P2);
Point operator+(Point P1, Point P2);
Point operator-(Point P1, Point P2);
Point operator*(Point P1, float k);
Point operator-(Point P1);

Point normalize(Point vec);
double DotProd(Point v1, Point v2);
Point CrossProd(Point v1, Point v2);

int intersec2d(Point k, Point l, Point m, Point n, double &s, double &t);
bool HaInterseccao(Point k, Point l, Point m, Point n);

long int getContadorInt();
void resetContadorInt();
int lado(Point P1, Point P2, Point A);

double Distance(Point P, Point Q);

#endif
