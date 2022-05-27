#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QMainWindow>
#include <memory>

using namespace std;

#include "mainwindow.h"
#include "Controllers/BaseController.h"
#include "Repositorys/IUsersRepository.h"

namespace Ui {
class BaseWindow;
}

class BaseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BaseWindow(QWidget *parent = nullptr);
    ~BaseWindow();

private slots:
    void on_login_btn_clicked();

    void resetBaseWindow();

private:
    Ui::BaseWindow *ui;

    unique_ptr<MainWindow> main_window;
    shared_ptr<BaseController> base_controller;
    shared_ptr<IUsersRepository> user_repository;
};

#endif // BASEWINDOW_H
