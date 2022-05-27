#ifndef MODERATORWINDOW_H
#define MODERATORWINDOW_H

#include <QWidget>

#include "Controllers/ModeratorController.h"
#include "Repositorys/IUsersRepository.h"

namespace Ui {
class ModeratorWindow;
}

class ModeratorWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ModeratorWindow(QWidget *parent = nullptr);
    ~ModeratorWindow();

    void login(shared_ptr<UserBL> user_bl);

private slots:
    void on_exit_btn_clicked();

signals:
    void exit();

private:
    Ui::ModeratorWindow *ui;

    unique_ptr<ModeratorController> moderator_controller;
    shared_ptr<IUsersRepository> users_repository;
};

#endif // MODERATORWINDOW_H
