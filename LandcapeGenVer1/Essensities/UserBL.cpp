#include "userbl.h"

UserBL::UserBL(string l, string p, string r, int m_id)
{
    login = l;
    password = p;
    role = r;
    moderator_id = m_id;
}

UserBL::UserBL()
{
    login = "";
    password = "";
    role = "";
    moderator_id = NULL;
}

/*UserBL &UserBL::operator =(UserBL &&u) noexcept
{
    login = u.getLogin();
    password = u.getPassword();
    role = u.getRole();
    moderator_id = u.getModeratorId();

    return *this;
}*/

string UserBL::getLogin()
{
    return login;
}

string UserBL::getPassword()
{
    return password;
}

string UserBL::getRole()
{
    return role;
}

int UserBL::getModeratorId()
{
    return moderator_id;
}
