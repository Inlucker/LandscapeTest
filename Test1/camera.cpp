#include "camera.h"

Camera::Camera()
{
    position = Point(0, 0, 0);
    angles = Point(0, 0, 0);
}

Camera::Camera(const Point &pos, const Point &angs)
{
    position = pos;
    angles = angs;
}

void Camera::transform(const Point moveK, const Point scaleK, const Point rotateK)
{
    position.transform(moveK, scaleK, rotateK, position);
    rotate(rotateK);
}

/*void Camera::accept(shared_ptr<BaseVisitor> visitor)
{
    //if (isVisible())
    visitor->visit(*this);
}*/

/*shared_ptr<Object> Camera::clone()
{
    //return shared_ptr<Object>(new Camera(position, angles));
    return shared_ptr<Object>(new Camera(name, position, angles));
}*/

void Camera::rotate(Point rotateK)
{
    angles.setX(angles.getX()+rotateK.getX());
    angles.setY(angles.getY()+rotateK.getY());
    angles.setZ(angles.getZ()+rotateK.getZ());
}

const Point &Camera::getPosition() const
{
    return position;
}

const Point &Camera::getAngles() const
{
    return angles;
}

/*void Camera::move(Point moveK)
{
    position.setX(position.getX()+moveK.getX());
    position.setY(position.getY()+moveK.getY());
    position.setZ(position.getZ()+moveK.getZ());
}*/
