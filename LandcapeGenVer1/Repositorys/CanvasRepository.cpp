#include "CanvasRepository.h"

CanvasRepository::CanvasRepository()
{
}

/*CanvasRepository::~CanvasRepository()
{

}*/

shared_ptr<CanvasBL> CanvasRepository::getCanvas(int id)
{
    connect();
    string query = "SELECT * FROM PPO.Canvas where id=" + to_string(id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res))
        {
            //auto ID = PQgetvalue (res, 0, 0);
            string name = PQgetvalue (res, 0, 2);
            string hm = PQgetvalue (res, 0, 3);
            string tpa = PQgetvalue (res, 0, 4);
            string c = PQgetvalue (res, 0, 5);
            //canvas = make_shared<CanvasBL>(hm, tpa, c);
            //return canvas;
            return make_shared<CanvasBL>(hm, tpa, c);
            //cout<< ID<<endl;
        }
        else //if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            cout << PQresultErrorMessage(res) << endl;
        }

        PQclear( res );
    }

    time_t t_time = time(NULL);
    throw GetCanvasError("No such canvas", __FILE__, __LINE__, ctime(&t_time));
    //return NULL;
}

void CanvasRepository::addCanvas(CanvasBL &canvas)
{
    connect();
    string tmp;
    canvas.getHeightsMap().toStr(tmp);
    string hm = tmp;
    canvas.getHeightsMapPoints().toStr(tmp);
    string hmp = tmp;
    int r, g, b;
    canvas.getColor(r, g, b);
    string c = to_string(r) + " " + to_string(g) + " " + to_string(b);

    string query = "insert into PPO.Canvas(user_id, name, HeightsMap, TriPolArray, Color) values(1, 'CanvasName', '";
    //string query = "insert into PPO.Canvas values(-1, 1, 'CanvasName', '";
    query += hm + "', '";
    query += hmp + "', '";
    query += c + "');";
    PQsendQuery(m_connection.get(), query.c_str());

    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            error_msg += "\n";
            error_msg += PQresultErrorMessage(res);
            flag = true;
        }
    }
    cout << error_msg;
    if (flag)
    {
        time_t t_time = time(NULL);
        throw InsertCanvasError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    }
}

void CanvasRepository::deleteCanvas(int id)
{
    connect();
    string query = "delete from PPO.Canvas where id=" + to_string(id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    bool flag = false;
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQcmdTuples(res)[0] == '0')
            flag = true;
    }
    if (flag)
    {
        time_t t_time = time(NULL);
        throw DeleteCanvasError("No such canvas", __FILE__, __LINE__, ctime(&t_time));
    }
}

void CanvasRepository::updateCanvas(CanvasBL &canvas_bl, int id)
{
    connect();
    string hm, hmp, c;
    canvas_bl.getHeightsMap().toStr(hm);
    canvas_bl.getHeightsMapPoints().toStr(hmp);
    canvas_bl.getColor(c);
    string query = "update PPO.Canvas set HeightsMap = '" + hm;
    query += "', TriPolArray = '" + hmp;
    query += "', Color = '" + c;
    query += "' where id = " + to_string(id) + ";";
    PQsendQuery(m_connection.get(), query.c_str());

    bool flag = false;
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQcmdTuples(res)[0] == '0')
            flag = true;
    }
    if (flag)
    {
        time_t t_time = time(NULL);
        throw UpdateCanvasError("No such canvas\nMaybe you should create it first", __FILE__, __LINE__, ctime(&t_time));
    }
}

void CanvasRepository::connect()
{
    m_connection.reset( PQsetdbLogin(m_dbhost.c_str(), to_string(m_dbport).c_str(), nullptr, nullptr, m_dbname.c_str(), m_dbuser.c_str(), m_dbpass.c_str()), &PQfinish );

    if (PQstatus( m_connection.get() ) != CONNECTION_OK && PQsetnonblocking(m_connection.get(), 1) != 0 )
    {
       time_t t_time = time(NULL);
       throw ConnectionError("m_connection", __FILE__, __LINE__, ctime(&t_time));
    }
}
