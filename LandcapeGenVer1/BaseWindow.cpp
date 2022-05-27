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

    base_controller = make_shared<BaseController>();

    //main_window = make_unique<MainWindow>();
    main_window.reset();
    //connect(main_window.get(), SIGNAL(exit()), this, SLOT(resetBaseWindow()));

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
        //canvas->login();
        string login = ui->login_lineEdit->text().toStdString();
        string password = ui->password_lineEdit->text().toStdString();

        shared_ptr<UserBL> user_bl = user_repository->getUser(login, password);
        base_controller->login(user_bl);
        main_window = make_unique<MainWindow>(user_bl);
        connect(main_window.get(), SIGNAL(exit()), this, SLOT(show()));
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
    this->disconnect(main_window.get());
    this->show();
    main_window.release();
}

