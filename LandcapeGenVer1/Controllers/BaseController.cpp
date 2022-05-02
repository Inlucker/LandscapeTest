#include "BaseController.h"

BaseController::BaseController()
{

}

BaseController::BaseController(UserBL u)
{
    user = u;
}

int BaseController::login(string l, string p)
{
    user = UserBL(l, p, "", NULL);
    return 0;
}

int BaseController::logout() noexcept
{
    user = UserBL();
    return 0;
}

int BaseController::registrate(string l, string p)
{
    user = UserBL(l, p, "", NULL);
    return 0;
}
