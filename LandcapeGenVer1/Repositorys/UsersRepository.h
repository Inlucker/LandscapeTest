#ifndef USERSREPOSITORY_H
#define USERSREPOSITORY_H

#include <iostream>
#include <libpq-fe.h>

using namespace std;

#include "IUsersRepository.h"
#include "Errors/RepositoryErrors.h"

class UsersRepository : public IUsersRepository
{
public:
    UsersRepository();
    UsersRepository(string dbuser, string dbpass, string dbschema = "PPO", string dbhost = "localhost", int dbport = 5432, string dbname = "postgres");
    virtual ~UsersRepository() = default;

    virtual shared_ptr<UserBL> getUser(string login, string password);
    virtual void addUser(UserBL& user);
    virtual void deleteUser(int id) ;
    virtual void updateUser(UserBL& user_bl, int id);

protected:
    void connect();

    string m_dbhost = "localhost";
    int m_dbport = 5432;
    string m_dbname = "postgres";
    string m_dbuser = "postgres";
    string m_dbpass = "postgres";
    string m_dbschema = "PPO";

    shared_ptr<PGconn> m_connection;
};

#endif // USERSREPOSITORY_H
