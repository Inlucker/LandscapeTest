#ifndef ICANVAS_REPOSITORY_H
#define ICANVAS_REPOSITORY_H

#include "Essensities/CanvasBL.h"

class ICanvasRepository
{
public:
    ICanvasRepository() = default;
    virtual ~ICanvasRepository() = 0;

    virtual CanvasBL& getCanvas(int id) = 0;
    //virtual void addCanvas(CanvasBL canvas) = 0;
    //virtual void deleteCanvas(int id) = 0;
    //virtual void updateHeightsMap(CanvasBL canvas, int id) = 0;
    //virtual void updateTriPolArray(CanvasBL canvas, int id) = 0;
    //virtual void updateColor(int r, int g, int b, int id) = 0;
};

#endif // ICANVAS_REPOSITORY_H
