#ifndef CANVASREPOSITORY_H
#define CANVASREPOSITORY_H

#include "ICanvasRepository.h"

class CanvasRepository : public ICanvasRepository
{
public:
    CanvasRepository() = default;
    ~CanvasRepository() = default;

    virtual CanvasBL& getCanvas(int id);
};

#endif // CANVASREPOSITORY_H
