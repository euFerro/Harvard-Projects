#ifndef __Camera__
#define __Camera__

#include "Point.h"
#include "Object.h"
#include "World.h"

class Camera : public Object
{
    // Camera vecs
    Point cameraPos;
    Point cameraTarget;
    Point cameraDir;
    Point worldUp;
    Point cameraRight;
    Point cameraUp;
    // Camera settings
    float width;
    float height;
    float fov;
    float ratio;
    float zNear;
    float zFar;
    float speed;
    float sensitivity;
public:
    Camera();
    void debug();
    void setWidth(float w);
    void setHeight(float h);
    void setPerspective();
    void setViewport(float w, float h);
    void setPosition(Point new_pos);
    void setTarget(Point new_target);
    void setFov(float new_fov);
    void setRatio(float w, float h);
    void setZnear(float distance);
    void setZfar(float distance);
    void setSpeed(float new_speed);
    void setSensitivity(float new_sens);
    float getWidth();
    float getHeight();
    void lookAt();
    void lookAt(Point pos, Point target);
};

#endif