#include "UsersRepositoryMySQL.h"
#include "Settings.h"
#include <QSqlQuery>
#include <QSqlError>

//#include <iostream>
//using namespace std;

UsersRepositoryMySQL::UsersRepositoryMySQL()
{
    m_schema = Settings::get(Settings::Schema, Settings::DataBase).toString().toStdString();
}

shared_ptr<UserBL> UsersRepositoryMySQL::getUser(string login, string password)
{
    string query = "SELECT * FROM " + m_schema + ".Users where login='" + login + "' and password = '" + password + "';";
    QSqlQuery q;
    q.exec(QString::fromStdString(query));
    if (q.next())
    {
        int ID = q.value(0).toInt();
        string login = q.value(1).toString().toStdString();
        string password = q.value(2).toString().toStdString();
        string role = q.value(3).toString().toStdString();
        int moderator_id = q.value(4).toInt();

        return make_shared<UserBL>(ID, login, password, role, moderator_id);
    }
    else
    {
        time_t t_time = time(NULL);
        throw LoginError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }
}

shared_ptr<UserBL> UsersRepositoryMySQL::getCanvasUser(string name)
{
    string query = "SELECT * FROM " + m_schema + ".Users where login='" + name + "';";

    QSqlQuery q;
    q.exec(QString::fromStdString(query));
    if (q.next())
    {
        int ID = q.value(0).toInt();
        string login = q.value(1).toString().toStdString();
        string password = q.value(2).toString().toStdString();
        string role = q.value(3).toString().toStdString();
        int moderator_id = q.value(4).toInt();

        return make_shared<UserBL>(ID, login, password, role, moderator_id);
    }
    else
    {
        time_t t_time = time(NULL);
        throw GetUsersError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }
}

vector<string> UsersRepositoryMySQL::getFreeCanvasUsers()
{
    string query = "select login FROM PPO.Users where role = 'canvas_user' and moderator_id is null;";

    vector<string> vec;

    QSqlQuery q;
    q.exec(QString::fromStdString(query));
    if (q.size())
        while (q.next())
        {
            string login = q.value(0).toString().toStdString();
            vec.push_back(login);
        }
    else
    {
        time_t t_time = time(NULL);
        throw GetUsersError(q.lastError().text().toStdString(), __FILE__, __LINE__, ctime(&t_time));
    }

    return vec;
}

vector<string> UsersRepositoryMySQL::getCanvasUsersByMid(int m_id)
{
}

void UsersRepositoryMySQL::addUser(UserBL &user_bl)
{

}

void UsersRepositoryMySQL::deleteUser(int id)
{

}

void UsersRepositoryMySQL::updateUser(UserBL &user_bl, int id)
{

}
