#ifndef CAMERA_H
#define CAMERA_H

#include "point.h"

//class ObjectVisitor;
class Canvas;

class Camera
{
public:
    Camera();
    Camera(const Point &pos, const Point &angs);
    ~Camera() = default;

     void transform(const Point moveK, const Point scaleK, const Point rotateK);
    //virtual void accept(shared_ptr<BaseVisitor> visitor);

    //virtual shared_ptr<Object> clone() override;

private:
    void rotate(Point move);
    const Point &getPosition() const;
    const Point &getAngles() const;
    friend Canvas;
    //friend void ObjectVisitor::visit(const Model &model);

private:
    Point position;
    Point angles;
};

#endif // CAMERA_H
