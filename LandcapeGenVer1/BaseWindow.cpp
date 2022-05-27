#include "BaseWindow.h"
#include "ui_BaseWindow.h"

#include <QMessageBox>

#include "Errors/BaseError.h"

BaseWindow::BaseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BaseWindow)
{
    ui->setupUi(this);

    base_controller = make_shared<BaseController>();

    main_window = make_unique<MainWindow>();
    connect(main_window.get(), SIGNAL(exit()), this, SLOT(ResetBaseWindow()));
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

void BaseWindow::ResetBaseWindow()
{
    this->disconnect(main_window.get());
    this->show();
    main_window = make_unique<MainWindow>();
    connect(main_window.get(), SIGNAL(exit()), this, SLOT(show()));
}

