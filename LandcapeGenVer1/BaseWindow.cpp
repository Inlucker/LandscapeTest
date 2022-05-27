#include "BaseWindow.h"
#include "ui_BaseWindow.h"

#include <QMessageBox>

#include "Errors/BaseError.h"
#include "Repositorys/UsersRepository.h"
#include "Essensities/UserBL.h"

BaseWindow::BaseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BaseWindow)
{
    ui->setupUi(this);

    main_window = make_unique<MainWindow>();
    connect(main_window.get(), SIGNAL(exit()), this, SLOT(resetBaseWindow()));

    moderator_window = make_unique<ModeratorWindow>();
    connect(moderator_window.get(), SIGNAL(exit()), this, SLOT(resetBaseWindow()));

    //user_repository = shared_ptr<IUsersRepository>(new UsersRepository());
    user_repository = make_shared<UsersRepository>();
}

BaseWindow::~BaseWindow()
{
    delete ui;
}

void BaseWindow::on_login_btn_clicked()
{
    try
    {
        string login = ui->login_lineEdit->text().toStdString();
        string password = ui->password_lineEdit->text().toStdString();
        shared_ptr<UserBL> user_bl = user_repository->getUser(login, password);
        if (user_bl->getRole() == "canvas_user")
        {
            main_window->login(user_bl);
            main_window->show();
            this->hide();
        }
        else if (user_bl->getRole() == "moderator")
        {
            moderator_window->login(user_bl);
            moderator_window->show();
            this->hide();
        }
        else
        {
            QMessageBox::information(this, "Error", "No such role");
        }
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

void BaseWindow::resetBaseWindow()
{
    this->show();
}


void BaseWindow::on_registrate_btn_clicked()
{
    try
    {
        string login = ui->login_lineEdit->text().toStdString();
        string password = ui->password_lineEdit->text().toStdString();
        string role = ui->role_comboBox->currentText().toStdString();
        UserBL user_bl(0, login, password, role, 0);
        user_repository->addUser(user_bl);
        QMessageBox::information(this, "Error", "Registration completed");
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

