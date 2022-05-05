#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include "Essensities/UserBL.h"

class BaseController
{
public:
    BaseController();
    explicit BaseController(UserBL u);
    virtual ~BaseController() = default;

    virtual int login(string l, string p);
    virtual int logout() noexcept;
    virtual int registrate(string l, string p);

protected:
    UserBL user;
};

#endif // BASECONTROLLER_H
