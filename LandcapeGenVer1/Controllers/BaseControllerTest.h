#ifndef BASECONTROLLERTEST_H
#define BASECONTROLLERTEST_H

#include "BaseController.h"

class BaseControllerTest
{
public:
    BaseControllerTest();

    bool noParamsConstrcutorTest();
    bool userBLConstrcutorTest();
    bool loginTest();
    bool logoutTest();
    bool getUserTest();
};

#endif // BASECONTROLLERTEST_H
