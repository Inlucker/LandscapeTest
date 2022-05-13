#include "BaseControllerTest.h"

#include <iostream>
using namespace std;

BaseControllerTest::BaseControllerTest()
{
    cout << noParamsConstrcutorTest() << endl;
    cout << userBLConstrcutorTest() << endl;
    cout << loginTest() << endl;
    cout << logoutTest() << endl;
    cout << getUserTest() << endl;
}

bool BaseControllerTest::noParamsConstrcutorTest()
{
    BaseController bc = BaseController();
    shared_ptr<UserBL> ubl = bc.getUser();
    UserBL an_ubl = UserBL();
    bool res = (*ubl == an_ubl);
    return res;
}

bool BaseControllerTest::userBLConstrcutorTest()
{
    shared_ptr<UserBL> ubl = make_shared<UserBL>(1, "login", "password", "role", NULL);
    BaseController bc = BaseController(ubl);
    shared_ptr<UserBL> bc_ubl = bc.getUser();
    bool res = (*bc_ubl == *ubl);
    return res;
}

bool BaseControllerTest::loginTest()
{
    BaseController bc = BaseController();
    shared_ptr<UserBL> ubl = make_shared<UserBL>(1, "login", "password", "role", NULL);
    bc.login(ubl);
    shared_ptr<UserBL> bc_ubl = bc.getUser();
    bool res = (*bc_ubl == *ubl);
    return res;
}

bool BaseControllerTest::logoutTest()
{
    BaseController bc = BaseController();
    shared_ptr<UserBL> ubl = make_shared<UserBL>(1, "login", "password", "role", NULL);
    bc.login(ubl);
    bc.logout();
    shared_ptr<UserBL> bc_ubl = bc.getUser();
    bool res = (bc_ubl == nullptr);
    return res;
}

bool BaseControllerTest::getUserTest()
{
    shared_ptr<UserBL> ubl = make_shared<UserBL>(1, "login", "password", "role", NULL);
    BaseController bc = BaseController(ubl);
    shared_ptr<UserBL> bc_ubl = bc.getUser();
    bool res = (*bc_ubl == *ubl);
    return res;
}
