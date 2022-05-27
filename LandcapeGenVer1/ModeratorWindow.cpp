#include "ModeratorWindow.h"
#include "ui_ModeratorWindow.h"

#include "Repositorys/UsersRepository.h"

ModeratorWindow::ModeratorWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModeratorWindow)
{
    ui->setupUi(this);

    moderator_controller = make_unique<ModeratorController>();
    //users_repository = shared_ptr<IUsersRepository>(new UsersRepository());
    users_repository = make_shared<UsersRepository>();
}

ModeratorWindow::~ModeratorWindow()
{
    delete ui;
}

void ModeratorWindow::login(shared_ptr<UserBL> user_bl)
{
    moderator_controller->login(user_bl);
    users_repository = make_shared<UsersRepository>(user_bl->getRole(), user_bl->getRole());

}

void ModeratorWindow::on_exit_btn_clicked()
{
    this->hide();
    moderator_controller->logout();
    emit exit();
}

