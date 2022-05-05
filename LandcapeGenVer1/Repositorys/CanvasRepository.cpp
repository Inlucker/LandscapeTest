#include "CanvasRepository.h"

CanvasRepository::CanvasRepository()
{
    string m_dbhost = "localhost";
    int         m_dbport = 5432;
    string m_dbname = "postgres";
    string m_dbuser = "postgres";
    string m_dbpass = "postgres";

    //m_connection.reset( PQsetdbLogin("localhost", "5432", nullptr, nullptr, "postgres", "postgres", "postgres"), &PQfinish );
    m_connection.reset( PQsetdbLogin(m_dbhost.c_str(), to_string(m_dbport).c_str(), nullptr, nullptr, m_dbname.c_str(), m_dbuser.c_str(), m_dbpass.c_str()), &PQfinish );

    if (PQstatus( m_connection.get() ) != CONNECTION_OK && PQsetnonblocking(m_connection.get(), 1) != 0 )
    {
       throw runtime_error( PQerrorMessage( m_connection.get() ) );
    }
}

/*CanvasRepository::~CanvasRepository()
{

}*/

shared_ptr<CanvasBL> CanvasRepository::getCanvas(int id)
{
    //string demo = "SELECT max(" + to_string(id) + ") FROM PPO.Users; " ;
    string query = "SELECT * FROM PPO.Canvas where id=" + to_string(id) + ";";
    PQsendQuery( m_connection.get(), query.c_str() );

    while ( auto res = PQgetResult( m_connection.get()) )
    {
        if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res))
        {
            //auto ID = PQgetvalue (res, 0, 0);
            string name = PQgetvalue (res, 0, 3);
            string hm = PQgetvalue (res, 0, 3);
            string tpa = PQgetvalue (res, 0, 4);
            string c = PQgetvalue (res, 0, 5);
            //canvas = make_shared<CanvasBL>(hm, tpa, c);
            //return canvas;
            return make_shared<CanvasBL>(hm, tpa, c);
            //cout<< ID<<endl;
        }

        else if (PQresultStatus(res) == PGRES_FATAL_ERROR)
        {
            cout<< PQresultErrorMessage(res)<<endl;
            return NULL;
        }

        PQclear( res );
    }

}
