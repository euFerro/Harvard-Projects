//
//  Point.cpp
//
//  Created by Breno Ferro 10/29/2022
//

#include "Point.h"

// Constructors -----------------------------------------------------------------------------------
Point::Point()
{
    x = y = z = 0;
}

Point::Point(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Point::set(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

// Debug ------------------------------------------------------------------------------------------
void Point::debug()
{
    cout << "(" << x << ", " << y << ", " << z << ")" << flush;
}

// Simple Operations ------------------------------------------------------------------------------
void Point::multiply(float x, float y, float z)
{
    this->x *= x;
    this->y *= y;
    this->z *= z;
}

void Point::add(float x, float y, float z)
{
    this->x += x;
    this->y += y;
    this->z += z;
}

void Point::normalize()
{
    float m = length();
    x /= m;
    y /= m;
    z /= m;
}

// Rotation ------------------------------------------------------------------------------------
void Point::rotateZ(float angle)
{
    float xr, yr;
    // cout << "angle: " << angle << " ";
    double angleRad = angle * 3.14159265359 / 180.0;
    xr = x * cos(angleRad) - y * sin(angleRad);
    yr = x * sin(angleRad) + y * cos(angleRad);
    x = xr;
    y = yr;
}

void Point::rotateY(float angle)
{
    float xr, zr;
    double angleRad = angle * 3.14159265359 / 180.0;
    xr = x * cos(angleRad) + z * sin(angleRad);
    zr = -x * sin(angleRad) + z * cos(angleRad);
    x = xr;
    z = zr;
}

void Point::rotateX(float angle)
{
    float yr, zr;
    double angleRad = angle * 3.14159265359 / 180.0;
    yr = y * cos(angleRad) - z * sin(angleRad);
    zr = y * sin(angleRad) + z * cos(angleRad);
    y = yr;
    z = zr;
}

// Vector Length ----------------------------------------------------------------------------------
double Point::length()
{
    return sqrt((x * x) + (y * y) + (z * z));
}

// Vector and Point operations --------------------------------------------------------------------
Point getMax(Point P1, Point P2)
{
    Point Max;

    Max.x = (P2.x > P1.x) ? P2.x : P1.x;
    Max.y = (P2.y > P1.y) ? P2.y : P1.y;
    Max.z = (P2.z > P1.x) ? P2.z : P1.z;
    return Max;
}

Point getMin(Point P1, Point P2)
{
    Point Min;

    Min.x = (P2.x < P1.x) ? P2.x : P1.x;
    Min.y = (P2.y < P1.y) ? P2.y : P1.y;
    Min.z = (P2.z < P1.x) ? P2.z : P1.z;
    return Min;
}

bool operator==(Point P1, Point P2)
{
    if (P1.x != P2.x)
        return false;
    if (P1.y != P2.y)
        return false;
    if (P1.z != P2.z)
        return false;
    return true;
}

Point operator+(Point P1, Point P2)
{
    Point temp;
    temp = P1;
    temp.x += P2.x;
    temp.y += P2.y;
    temp.z += P2.z;
    return temp;
}

Point operator-(Point P1, Point P2)
{
    Point temp;
    temp = P1;
    temp.x -= P2.x;
    temp.y -= P2.y;
    temp.z -= P2.z;
    return temp;
}

Point operator*(Point P1, float k)
{
    Point temp;
    temp.x = P1.x * k;
    temp.y = P1.y * k;
    temp.z = P1.z * k;
    return temp;
}

Point operator-(Point P1)
{
    return P1 * -1;
}

Point normalize(Point vec)
{
    float m = vec.length();
    vec.x /= m;
    vec.y /= m;
    vec.z /= m;
}

double DotProd(Point v1, Point v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

Point CrossProd(Point v1, Point v2)
{
    Point vresult;
    vresult.x = v1.y * v2.z - (v1.z * v2.y);
    vresult.y = v1.z * v2.x - (v1.x * v2.z);
    vresult.z = v1.x * v2.y - (v1.y * v2.x);
    return vresult;
}

long int ContadorInt = 0;
/* ********************************************************************** */
/*                                                                        */
/*  Calcula a interseccao entre 2 retas (no plano "XY" Z = 0)             */
/*                                                                        */
/* k : Point inicial da reta 1                                            */
/* l : Point final da reta 1                                              */
/* m : Point inicial da reta 2                                            */
/* n : Point final da reta 2                                              */
/*                                                                        */
/* s: valor do parâmetro no Point de interseção (sobre a reta KL)         */
/* t: valor do parâmetro no Point de interseção (sobre a reta MN)         */
/*                                                                        */
/* ********************************************************************** */
int intersec2d(Point k, Point l, Point m, Point n, double &s, double &t)
{
    double det;

    det = (n.x - m.x) * (l.y - k.y) - (n.y - m.y) * (l.x - k.x);

    if (det == 0.0)
        return 0; // não há intersecção

    s = ((n.x - m.x) * (m.y - k.y) - (n.y - m.y) * (m.x - k.x)) / det;
    t = ((l.x - k.x) * (m.y - k.y) - (l.y - k.y) * (m.x - k.x)) / det;

    return 1; // há intersecção
}

bool HaInterseccao(Point k, Point l, Point m, Point n)
{
    int ret;
    double s, t;

    ContadorInt = ContadorInt + 1;
    ret = intersec2d(k, l, m, n, s, t);
    if (!ret)
        return false;
    if (s >= 0.0 && s <= 1.0 && t >= 0.0 && t <= 1.0)
        return true;
    else
        return false;
}

void resetContadorInt()
{
    ContadorInt = 0;
}

long int getContadorInt()
{
    return ContadorInt;
}

double Distance(Point S, Point E)
{
    float dx, dy, dz;

    dx = S.x - E.x;
    dy = S.y - E.y;
    dz = S.z - E.z;

    return sqrt((dx * dx) + (dy * dy) + (dz * dz));
}
