#include "ModeratorWindow.h"
#include "ui_ModeratorWindow.h"

#include <QMessageBox>

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
    updateLists();
}

void ModeratorWindow::addUser(string name)
{
    shared_ptr<UserBL> user_bl = users_repository->getCanvasUser(name);
    UserBL new_user_bl(user_bl->getId(), user_bl->getLogin(), user_bl->getPassword(), user_bl->getRole(), moderator_controller->getUser()->getId());
    users_repository->updateUser(new_user_bl, user_bl->getId());
    updateLists();
}

void ModeratorWindow::deleteUser(string name)
{
    shared_ptr<UserBL> user_bl = users_repository->getCanvasUser(name);
    UserBL new_user_bl(user_bl->getId(), user_bl->getLogin(), user_bl->getPassword(), user_bl->getRole(), -1);
    users_repository->updateUser(new_user_bl, user_bl->getId());
    updateLists();
}

void ModeratorWindow::on_exit_btn_clicked()
{
    this->hide();
    moderator_controller->logout();
    emit exit();
}

void ModeratorWindow::updateFreeCanvasUsersList()
{
    ui->free_users_listWidget->clear();
    vector<string> free_users_names = users_repository->getFreeCanvasUsers();
    for (auto &elem : free_users_names)
        ui->free_users_listWidget->addItem(QString::fromStdString(elem));
}

#include "Essensities/UserBL.h"
#include "Controllers/ModeratorController.h"

void ModeratorWindow::updateMyCanvasUsersList()
{
    if (moderator_controller->getUser())
    {
        ui->my_users_listWidget->clear();
        vector<string> my_users_names = users_repository->getCanvasUsersByMid(moderator_controller->getUser()->getId());
        for (auto &elem : my_users_names)
            ui->my_users_listWidget->addItem(QString::fromStdString(elem));
    }
}

void ModeratorWindow::updateLists()
{
    try
    {
        updateFreeCanvasUsersList();
        updateMyCanvasUsersList();
    }
    catch (BaseError &er)
    {
        QMessageBox::information(this, "Error", er.what());
    }
    catch (...)
    {
        QMessageBox::information(this, "Error", "Unexpected Error");
    }
}


void ModeratorWindow::on_add_btn_clicked()
{
    try
    {
        QList list = ui->free_users_listWidget->selectedItems();
        for (auto &elem : list)
        {
            addUser(elem->text().toStdString());
        }
        updateLists();
    }
    catch (BaseError &er)
    {
        QMessageBox::information(this, "Error", er.what());
    }
    catch (...)
    {
        QMessageBox::information(this, "Error", "Unexpected Error");
    }
}


void ModeratorWindow::on_delete_btn_clicked()
{
    try
    {
        QList list = ui->my_users_listWidget->selectedItems();
        for (auto &elem : list)
        {
            deleteUser(elem->text().toStdString());
        }
        updateLists();
    }
    catch (BaseError &er)
    {
        QMessageBox::information(this, "Error", er.what());
    }
    catch (...)
    {
        QMessageBox::information(this, "Error", "Unexpected Error");
    }
}

