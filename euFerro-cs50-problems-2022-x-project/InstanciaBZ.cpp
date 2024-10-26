#include "InstanciaBZ.h"
#include <cstdlib>

// ***********************************************************
//  void InstanciaPoint(Point3D *p, Point3D *out)
//  Esta funcao calcula as coordenadas de um Point no
//  sistema de referencia do universo (SRU), ou seja,
//  aplica as rotacoes, escalas e translacoes a um
//  Point no sistema de referencia do objeto (SRO).
// ***********************************************************

void InstanciaPoint(Point &p, Point &out)
{
    GLfloat Point_novo[4];
    GLfloat matriz_gl[4][4];
    int i;

    glGetFloatv(GL_MODELVIEW_MATRIX, &matriz_gl[0][0]);

    for (i = 0; i < 4; i++)
    {
        Point_novo[i] = matriz_gl[0][i] * p.x +
                        matriz_gl[1][i] * p.y +
                        matriz_gl[2][i] * p.z +
                        matriz_gl[3][i];
    }
    out.x = Point_novo[0];
    out.y = Point_novo[1];
    out.z = Point_novo[2];
}

Point InstanciaPoint(Point P)
{
    Point temp;
    InstanciaPoint(P, temp);
    return temp;
}

InstanciaBZ::InstanciaBZ()
{
    Rotacao = 0;
    Posicao = Point(0, 0, 0);
    Escala = Point(1, 1, 1);

    nroDaCurva = 0;
    proxCurva = -1;
    tAtual = 0.0;
    direcao = 1;
    Velocidade = 1;
}
InstanciaBZ::InstanciaBZ(Bezier *C)
{
    Rotacao = 0;
    Posicao = Point(0, 0, 0);
    Escala = Point(1, 1, 1);

    Curva = C;
    tAtual = 0;
    direcao = 1;
    Velocidade = 1;
}

void InstanciaBZ::desenha()
{
    // cout << "Escala: ";
    // Escala.debug();
    // cout << endl;
    // Aplica as transformacoes geometricas no modelo
    glPushMatrix();
    glTranslatef(Posicao.x, 0.0f, Posicao.z);
    glRotatef(Rotacao, 0, 1, 0);
    glScalef(Escala.x, Escala.y, Escala.z);

    (*modelo)(); // desenha a instancia

    glPopMatrix();
}
Point InstanciaBZ::ObtemPosicao()
{
    // aplica as transformacoes geometricas no modelo
    // desenha a geometria do objeto

    glPushMatrix();
    glTranslatef(Posicao.x, 0, Posicao.z);
    glRotatef(Rotacao, 1, 0, 0);
    Point PosicaoDoPersonagem;
    Point Origem(0, 0, 0);
    InstanciaPoint(Origem, PosicaoDoPersonagem);
    // PosicaoDoPersonagem.imprime(); cout << endl;
    glPopMatrix();
    return PosicaoDoPersonagem;
}
void InstanciaBZ::AtualizaPosicao(double deltaTime)
{
    if (deltaTime >= 1000 / 60)
    {
        if (this->direcao == 1)
        {
            tAtual += 0.001 * Velocidade;
        }
        else
        {
            tAtual -= 0.001 * Velocidade;
        }
        this->Posicao = this->Curva[nroDaCurva].Calcula(tAtual);
        if (tAtual >= 1 || tAtual <= 0)
        {
            tAtual = rand() % 2;
            direcao = rand() % 2;
            nroDaCurva = rand() % 20;
        }
    }
}

