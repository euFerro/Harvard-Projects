#include "Point.h"
#include "Object.h"
#include "Camera.h"

Camera::Camera()
{
    // Camera vectors
    cameraPos = Point(2.0f, 7.0f, -10.0f);
    cameraTarget = Point(0.0f, 0.0f, 0.0f);
    cameraDir = normalize(cameraPos - cameraTarget);
    worldUp = Point(0.0f, 1.0f, 0.0f);
    cameraRight = normalize(CrossProd(worldUp, cameraDir));
    cameraUp = CrossProd(cameraDir, cameraRight);
    // Camera settings
    width = 700.0f;
    height = 700.0f;
    fov = 70.0f;
    ratio = width / height;
    zNear = 0.1f;
    zFar = 1000.0f;
    speed = 1.0f;
    sensitivity = 1.0f;
}

void Camera::debug()
{
    cameraPos.debug();
}

void Camera::setWidth(float w)
{
    this->width = w;
}

void Camera::setHeight(float h)
{
    this->height = h;
}

void Camera::setPerspective()
{
    gluPerspective(fov, ratio, zNear, zFar);
}

void Camera::setViewport(float w, float h)
{
    glViewport(0, 0, w, h);
}

void Camera::setPosition(Point new_pos)
{
    this->cameraPos = new_pos;
}

void Camera::setTarget(Point new_target)
{
    this->cameraTarget = new_target;
}

void Camera::setFov(float new_fov)
{
    this->fov = new_fov;
}

void Camera::setRatio(float w, float h)
{
    this->ratio = w / h;
}

void Camera::setZnear(float distance)
{
    this->zNear = distance;
}

void Camera::setZfar(float distance)
{
    this->zFar = distance;
}

void Camera::setSpeed(float new_speed)
{
    this->speed = new_speed;
}

void Camera::setSensitivity(float new_sens)
{
    this->sensitivity = new_sens;
}

float Camera::getWidth()
{
    return this->width;
}

float Camera::getHeight()
{
    return this->height;
}

void Camera::lookAt()
{
    gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,
              cameraTarget.x, cameraTarget.y, cameraTarget.z,
              worldUp.x, worldUp.y, worldUp.z);
}

void Camera::lookAt(Point pos, Point target)
{
    gluLookAt(pos.x, pos.y, pos.z,
              target.x, target.y, target.z,
              0.0, 1.0, 0.0);
}

