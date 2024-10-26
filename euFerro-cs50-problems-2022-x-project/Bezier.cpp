//
//  Bezier.cpp
//  OpenGL
//

#include "Bezier.h"
#include "ColorListRGB.h"

// **********************************************************************
Bezier::Bezier()
{
    for (int i=0;i<3;i++)
        Coords[i] = Point(0,0,0);
    ComprimentoTotalDaCurva = 0;
    cor = nextColor();
    //cout << "Cor: " << cor << endl;
}
// **********************************************************************
//
// **********************************************************************
void Bezier::calculaComprimentoDaCurva()
{
    double DeltaT = 1.0/50;
    double t=DeltaT;
    Point P1, P2;

    ComprimentoTotalDaCurva = 0;

    P1 = Calcula(0.0);
    while(t<1.0)
    {
        P2 = Calcula(t);
        ComprimentoTotalDaCurva += Distance(P1,P2);
        P1 = P2;
        t += DeltaT;
    }
    P2 = Calcula(1.0); // faz o fechamento da curva
    ComprimentoTotalDaCurva += Distance(P1,P2);

}
// **********************************************************************
Bezier::Bezier(Point P0, Point P1, Point P2)
{
    Coords[0] = P0;
    Coords[1] = P1;
    Coords[2] = P2;
    calculaComprimentoDaCurva();
    cor = nextColor();
}
// **********************************************************************
Bezier::Bezier(Point V[])
{
    for (int i=0;i<3;i++)
        Coords[i] = V[i];
    calculaComprimentoDaCurva();
    cor = nextColor();
}
// **********************************************************************
//
// **********************************************************************
Point Bezier::Calcula(double t)
{
    Point P;
    double UmMenosT = 1-t;

    P =  Coords[0] * UmMenosT * UmMenosT + Coords[1] * 2 * UmMenosT * t + Coords[2] * t*t;
    return P;
}
// **********************************************************************
//
// **********************************************************************
double Bezier::CalculaT(double distanciaPercorrida)
{
    return (distanciaPercorrida/ComprimentoTotalDaCurva);
}
// **********************************************************************
//
// **********************************************************************
Point Bezier::getPC(int i)
{
    return Coords[i];
}
// **********************************************************************
void Bezier::desenha()
{
    double t=0.0;
    double DeltaT = 1.0/50;
    Point P;
    //cout << "DeltaT: " << DeltaT << endl;
    glBegin(GL_LINE_STRIP);

    while(t<1.0)
    {
        P = Calcula(t);
        //P.imprime("P: ");
        glVertex3f(P.x, P.y, P.z);
        t += DeltaT;
    }
    P = Calcula(1.0); // faz o fechamento da curva
    glVertex3f(P.x, P.y, P.z);
    glEnd();
}

