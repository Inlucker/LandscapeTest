#ifndef MODERATORWINDOW_H
#define MODERATORWINDOW_H

#include <QWidget>

#include "Controllers/ModeratorController.h"
#include "Repositorys/CanvasRepository.h"
#include "Repositorys/UsersRepository.h"
#include "Repositorys/UsersRepositoryMySQL.h"
#include "Repositorys/CanvasRepositoryMySQL.h"

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
    void addUser(string name);
    void deleteUser(string name);

private slots:
    void on_exit_btn_clicked();

    void on_add_btn_clicked();

    void on_delete_btn_clicked();

    void on_delete_user_btn_clicked();

signals:
    void exit();

private:
    void updateFreeCanvasUsersList();
    void updateMyCanvasUsersList();
    void updateLists();

private:
    Ui::ModeratorWindow *ui;

    unique_ptr<ModeratorController> moderator_controller;
    shared_ptr<CanvasRepositoryMySQL> canvas_repository;
    shared_ptr<UsersRepositoryMySQL> users_repository;
};

#endif // MODERATORWINDOW_H
