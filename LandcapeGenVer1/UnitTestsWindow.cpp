#include "UnitTestsWindow.h"
#include "ui_UnitTestsWindow.h"

#include <QMessageBox>

UnitTestsWindow::UnitTestsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnitTestsWindow)
{
    ui->setupUi(this);
}

UnitTestsWindow::~UnitTestsWindow()
{
    delete ui;
}

void UnitTestsWindow::on_user_controller_test_btn_clicked()
{
    try
    {
        UserControllerTest uct;
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

