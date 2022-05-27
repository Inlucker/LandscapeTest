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
        main_window->login(user_bl);
        main_window->show();
        this->hide();
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

