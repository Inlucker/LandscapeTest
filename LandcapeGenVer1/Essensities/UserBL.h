#ifndef USERBL_H
#define USERBL_H

#include <string>

using namespace std;

class UserBL
{
public:
    UserBL();
    //UserBL& operator =(UserBL&& vec) noexcept;
    UserBL(string l, string p, string r, int m_id);

    string getLogin();
    string getPassword();
    string getRole();
    int getModeratorId();

private:
    string login = "";
    string password = "";
    string role = "";
    int moderator_id = NULL;

};

#endif // USERBL_H
