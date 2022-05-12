#ifndef UNITTESTSWINDOW_H
#define UNITTESTSWINDOW_H

#include <QWidget>
#include "Controllers/UserControllerTest.h"

namespace Ui {
class UnitTestsWindow;
}

class UnitTestsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UnitTestsWindow(QWidget *parent = nullptr);
    ~UnitTestsWindow();

private slots:
    void on_user_controller_test_btn_clicked();

private:
    Ui::UnitTestsWindow *ui;
};

#endif // UNITTESTSWINDOW_H
