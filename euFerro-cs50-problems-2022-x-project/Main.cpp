// **********************************************************************
// PUCRS/Escola Polit�cnica
// COMPUTA��O GR�FICA
//
// Programa basico para criar aplicacoes 2D em OpenGL
//
// Marcio Sarroglia Pinho
// pinho@pucrs.br
// **********************************************************************

// Para uso no Xcode:
// Abra o menu Product -> Scheme -> Edit Scheme -> Use custom working directory
// Selecione a pasta onde voce descompactou o ZIP que continha este arquivo.
//

#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>

using namespace std;

#ifdef WIN32
#include <windows.h>
#include <GL/glut.h>
#else
#include "sys/utime.h"
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

#include "Point.h"
#include "Object.h"
#include "Mesh.h"
#include "Camera.h"
#include "World.h"
#include "ColorListRGB.h"
#include "Bezier.h"

// #include "InstanciaBZ.h"

// InstanciaBZ Personagens[10];
// InstanciaBZ Player;

Bezier Curvas[20];
unsigned int curveCount;

World world;
Camera mainCamera;
// Camera Circle Anim Variables
const float radius = 10.0f;
float camX;
float camZ;

// Meshes
Mesh cube, circle;

// Editor Variables
bool gizmos = true;
bool meshes = true;
bool showFPS = false;
bool fullScreen = false;

// Time and Animation
double Time, PrevTime = 0.0, DeltaTime;
int frame = 0;
float angle = 0.0f;
float camAngle = 0.0f;

void animate()
{
    // FPS Calculation
    Time = glutGet(GLUT_ELAPSED_TIME);
    DeltaTime = Time - PrevTime;

    // Update framerate
    if (DeltaTime >= 1000)
    {
        PrevTime = Time;
        if (showFPS)
        {
            cout << "FPS: " << frame << " / " << DeltaTime / frame << "ms" << endl;
        }
        frame = 0;
    }

    if (DeltaTime >= 1000 / 60) // Animation Controller for animation variables (60FPS)
    {
        angle += 0.05f;
        camAngle -= 0.01f;
    }
    glutPostRedisplay();
}

//  Redimentions OpenGL window
void reshape(int w, int h)
{
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // glOrtho(Min.x, Max.x, Min.y, Max.y, -5, +5);

    // Sets Camera's viewport 
    mainCamera.setViewport(mainCamera.getWidth(), mainCamera.getHeight());
    mainCamera.setPerspective();
    mainCamera.lookAt();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init()
{
    cout << glGetString(GL_VERSION) << endl;

    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_LIGHTING);
    // glEnable(GL_COLOR_MATERIAL);
    // glEnable(GL_CULL_FACE);

    // Background Color
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    // World Limit
    world.setGridSize(100.0f);
    world.createWorldGrid();

    mainCamera = Camera();

    cube.Cube(1);
    circle.Circle(2);

    // glShadeModel(GL_FLAT);
    // glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void RotateAnimation(Mesh obj)
{
    glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    defineColor(White);
    obj.paintFaces();
    defineColor(BrightBlue);
    obj.paintEdges();
    defineColor(Yellow);
    obj.paintVertices(4);
    glPopMatrix();
}

void PaintMeshes()
{
    RotateAnimation(cube);
    defineColor(BrightBlue);
    circle.paintWireframe();
}

void render(void)
{
    // Clears the screen with background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Specify the current matrix to render the models
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Rotate camera in a circle
    glPushMatrix();
    glRotatef(camAngle, 0.0f, 1.0f, 0.0f);

    glLineWidth(1);
    glColor3f(1, 1, 1); // R, G, B  [0..1]

    if (gizmos)
    {
        world.paintWorldGrid();
    }

    if (meshes)
    {
        // Paint Meshes
        PaintMeshes();
        // Animation
        // RotateAnimation(cube);
    }

    glPopMatrix();

    // Refresh frame and count the number of frames
    glutSwapBuffers();
    frame++;
}

void keyboard(unsigned char key, int x, int y)
{

    switch (key)
    {
    case 27:     // Termina o programa qdo
        exit(0); // a tecla ESC for pressionada
        break;
    case 't':
        showFPS = !showFPS;
        break;
    case 'g':
        gizmos = !gizmos;
        break;
    case 'c':
        break;
    case 'm':
        meshes = !meshes;
        break;
    case 'w':
        cout << "W" << endl;
        break;
    case 'a':
        cout << "A" << endl;
        break;
    case 's':
        cout << "S" << endl;
        break;
    case 'd':
        cout << "D" << endl;
        break;
    default:
        break;
    }
}

void arrow_button(int a_button, int x, int y)
{
    switch (a_button)
    {
    case GLUT_KEY_LEFT:
        // Player.direcao = 0;
        // Player.AtualizaPosicao(DeltaTime);
        cout << "Left" << endl;
        break;
    case GLUT_KEY_RIGHT:
        // Player.direcao = 1;
        // Player.AtualizaPosicao(DeltaTime);
        cout << "Right" << endl;
        break;
    case GLUT_KEY_UP:  
        cout << "Up" << endl;
        break;
    case GLUT_KEY_DOWN:
    cout << "Down" << endl;
        break;
    case GLUT_KEY_F11:
        fullScreen = !fullScreen;
        if (fullScreen == false)
        {
            // glMatrixMode(GL_PROJECTION);
            // glLoadIdentity();

            mainCamera.setWidth(1920.0f);
            mainCamera.setHeight(1080.0f);
            mainCamera.setRatio(1920.0f, 1080.0f);
            glutFullScreen();

            // glMatrixMode(GL_MODELVIEW);
            // glLoadIdentity();
        }
        else
        {
            mainCamera.setWidth(700.0f);
            mainCamera.setHeight(700.0f);
            mainCamera.setRatio(700.0f, 700.0f);
            glutPositionWindow(960 - 550, 0);
        }
        break;
    default:
        break;
    }
}

void mouse_input(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_MIDDLE_BUTTON:
        if (state == GLUT_DOWN)
        {
            cout << "Down: " << "(x: " << x << " y: " << y << ")" << endl;
        }
        if (state == GLUT_UP)
        {
            cout << "Up: " << "(x: " << x << " y: " << y << ")" << endl;
        }
        break;
    default:
        break;
    }
}

int main(int argc, char **argv)
{
    cout << "Micro Engine" << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

    glutInitWindowPosition(960 - 550, 0);
    glutInitWindowSize(mainCamera.getWidth(), mainCamera.getHeight());
    glutCreateWindow("Micro Engine");

    init();

    glutDisplayFunc(render);
    glutIdleFunc(animate);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrow_button);
    glutMouseFunc(mouse_input);

    glutMainLoop();

    return 0;
}
