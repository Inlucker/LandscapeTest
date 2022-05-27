#ifndef IUSERSREPOSITORY_H
#define IUSERSREPOSITORY_H

#include <memory>

using namespace std;

#include "Essensities/UserBL.h"

class IUsersRepository
{
public:
    IUsersRepository();
    virtual ~IUsersRepository() = 0;

    virtual shared_ptr<UserBL> getUser(int id) = 0;
    virtual void addUser(UserBL& canvas) = 0;
    virtual void deleteUser(int id) = 0;
    virtual void updateUser(UserBL& heights_map, int id) = 0;
};

#endif // IUSERSREPOSITORY_H
