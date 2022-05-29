#include "CanvasRepositoryMySQL.h"
#include "Settings.h"
#include <QSqlQuery>
#include <QSqlError>

CanvasRepositoryMySQL::CanvasRepositoryMySQL()
{
    m_schema = Settings::get(Settings::Schema, Settings::DataBase).toString().toStdString();
}

shared_ptr<CanvasBL> CanvasRepositoryMySQL::getCanvas(int id)
{

}

vector<pair<int, string> > CanvasRepositoryMySQL::getCanvasesByUid(int u_id)
{
    string query = "select id, name FROM PPO.Canvas where user_id = " + std::to_string(u_id) + ";";

    vector<pair<int, string>> vec;
    QSqlQuery q;
    q.exec(QString::fromStdString(query));
    if (q.size())
        while (q.next())
        {
            int c_id = q.value(0).toInt();
            string name = q.value(1).toString().toStdString();
            vec.push_back(make_pair(c_id, name));
        }
    else
    {
        time_t t_time = time(NULL);
        throw GetCanvasError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }
    return vec;
}

void CanvasRepositoryMySQL::addCanvas(CanvasBL &canvas)
{

}

void CanvasRepositoryMySQL::deleteCanvas(int id)
{

}

void CanvasRepositoryMySQL::updateCanvas(CanvasBL &canvas_bl, int id)
{

}

void CanvasRepositoryMySQL::test(string &str)
{

}
