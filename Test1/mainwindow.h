#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <canvas.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_gen_btn_clicked();

    void on_clean_btn_clicked();

    void on_size_up_btn_released();

    void on_size_down_btn_released();

private:
    Ui::MainWindow *ui;

    unique_ptr<Canvas> canvas;
};
#endif // MAINWINDOW_H
