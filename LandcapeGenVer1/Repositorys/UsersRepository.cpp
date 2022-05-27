#include "UsersRepository.h"

UsersRepository::UsersRepository() : m_dbhost("localhost"), m_dbport(5432), m_dbname("postgres"), m_dbuser("canvas_user"), m_dbpass("canvasuser"), m_dbschema("PPO")
{

}

UsersRepository::UsersRepository(string dbuser, string dbpass, string dbschema, string dbhost, int dbport, string dbname)
    : m_dbhost(dbhost), m_dbport(dbport), m_dbname(dbname), m_dbuser(dbuser), m_dbpass(dbpass), m_dbschema(dbschema)
{

}

shared_ptr<UserBL> UsersRepository::getUser(string login, string password)
{
    connect();
    string query = "SELECT * FROM " + m_dbschema + ".Users where login='" + login + "' and password = '" + password + "';";
    PQsendQuery(m_connection.get(), query.c_str());

    bool flag = false;
    string error_msg = "";
    while (auto res = PQgetResult( m_connection.get()))
    {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res))
        {
            int ID = atoi(PQgetvalue (res, 0, 0));
            string login = PQgetvalue (res, 0, 1);
            string password = PQgetvalue (res, 0, 2);
            string role = PQgetvalue (res, 0, 3);
            int moderator_id = atoi(PQgetvalue (res, 0, 4));

            return make_shared<UserBL>(ID, login, password, role, moderator_id);
        }
        else if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            error_msg += "\n";
            error_msg += PQresultErrorMessage(res);
            flag = true;
        }

        PQclear( res );
    }

    time_t t_time = time(NULL);
    if (flag)
        throw GetUserError(error_msg, __FILE__, __LINE__, ctime(&t_time));
    else
        throw GetUserError("login or password", __FILE__, __LINE__, ctime(&t_time));
    return NULL;
}

void UsersRepository::addUser(UserBL &user)
{
    cout << "addUser" << endl;
}

void UsersRepository::deleteUser(int id)
{
    cout << "deleteUser" << endl;
}

void UsersRepository::updateUser(UserBL &user_bl, int id)
{
    cout << "updateUser" << endl;
}

void UsersRepository::connect()
{
    m_connection.reset( PQsetdbLogin(m_dbhost.c_str(), to_string(m_dbport).c_str(), nullptr, nullptr, m_dbname.c_str(), m_dbuser.c_str(), m_dbpass.c_str()), &PQfinish );

    if (PQstatus( m_connection.get() ) != CONNECTION_OK && PQsetnonblocking(m_connection.get(), 1) != 0 )
    {
       time_t t_time = time(NULL);
       throw ConnectionError("m_connection", __FILE__, __LINE__, ctime(&t_time));
    }
}
