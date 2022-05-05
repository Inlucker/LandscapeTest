#ifndef CANVASREPOSITORY_H
#define CANVASREPOSITORY_H

#include <memory>
#include <libpq-fe.h>

#include "ICanvasRepository.h"

class CanvasRepository : public ICanvasRepository
{
public:
    CanvasRepository();
    virtual ~CanvasRepository() = default;

    virtual shared_ptr<CanvasBL> getCanvas(int id);

private:
    //shared_ptr<PGConnection> connecteion;
    shared_ptr<PGconn>  m_connection;
    //shared_ptr<CanvasBL> canvas;
};

#endif // CANVASREPOSITORY_H
