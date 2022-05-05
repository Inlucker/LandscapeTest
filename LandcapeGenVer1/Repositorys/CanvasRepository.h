#ifndef CANVASREPOSITORY_H
#define CANVASREPOSITORY_H

#include <memory>
#include <libpq-fe.h>

#include "ICanvasRepository.h"
#include "Errors/ConnectionErrors.h"

class CanvasRepository : public ICanvasRepository
{
public:
    CanvasRepository();
    virtual ~CanvasRepository() = default;

    virtual shared_ptr<CanvasBL> getCanvas(int id);
    virtual void addCanvas(shared_ptr<CanvasBL> canvas);
    //virtual void deleteCanvas(int id) = 0;

private:
    void connect();

private:
    string m_dbhost = "localhost";
    int m_dbport = 5432;
    string m_dbname = "postgres";
    string m_dbuser = "postgres";
    string m_dbpass = "postgres";

    shared_ptr<PGconn> m_connection;
};

#endif // CANVASREPOSITORY_H
