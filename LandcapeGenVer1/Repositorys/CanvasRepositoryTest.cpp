#include "CanvasRepositoryTest.h"

CanvasRepositoryTest::CanvasRepositoryTest() :
    CanvasRepository("localhost", 5432, "postgres", "postgres", "postgres", "CanvasRepositoryTest")
{
    setupForTest();
    errors_count = testAll();
    output += "Errors count: " + to_string(errors_count) + "\n";
    output += "End of CanvasRepositoryTest";
}

CanvasRepositoryTest::~CanvasRepositoryTest()
{
    connect();
    string query = "drop schema " + m_dbschema + " cascade;";
    PQsendQuery(m_connection.get(), query.c_str());

    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            cout << PQresultErrorMessage(res);
        }
        PQclear(res);
    }
    //cout << "CanvasRepositoryTest destructor";
}

int CanvasRepositoryTest::testAll()
{
    int res = 0;

    res += addCanvasTest();

    return res;
}

/*CanvasRepositoryTest::CanvasRepositoryTest(string dbhost, int dbport, string dbname, string dbuser, string dbpass, string dbschema) :
    CanvasRepository(dbhost, dbport, dbname, dbuser, dbpass, dbschema)
{
    setupForTest();
}*/

int CanvasRepositoryTest::getCanvasTest()
{
    int res = 0;

    return res;
}

int CanvasRepositoryTest::addCanvasTest()
{
    int res = 0;

    int size = 33;
    HeightsMap hm = HeightsMap(size);
    hm.diamondSquare();
    //shared_ptr<HeightsMapPoints> hmp = hm.createPoints();
    CanvasBL canvas = CanvasBL(hm, *hm.createPoints(), 20, 150, 20);
    this->addCanvas(canvas);
    shared_ptr<CanvasBL> same_canvas = this->getCanvas(1);
    if (canvas != *same_canvas)
    {
        res++;
        output += "addCanvasTest error\n";
    }
    else
    {
        output += "addCanvasTest OK\n";
    }

    return res;
}

int CanvasRepositoryTest::deleteCanvasTest()
{
    int res = 0;

    return res;
}

int CanvasRepositoryTest::updateCanvasTest()
{
    int res = 0;

    return res;
}

const string &CanvasRepositoryTest::getOutput() const
{
    return output;
}

void CanvasRepositoryTest::setupForTest()
{
    connect();
    string query = "create schema "+ m_dbschema + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            cout << PQresultErrorMessage(res);
        }
        PQclear(res);
    }

    connect();
    query = "create table if not exists "+ m_dbschema + ".Canvas\
            (\
                id serial primary key,\
                user_id int,\
                FOREIGN KEY (user_id) REFERENCES PPO.Users (id),\
                name text,\
                HeightsMap text,\
                TriPolArray text,\
                Color text\
            );";
    PQsendQuery(m_connection.get(), query.c_str());

    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            cout << PQresultErrorMessage(res);
        }

        PQclear(res);
    }
}
