#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>
#include <iostream>

using namespace std;

#include <Canvas.h>

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

    void on_draw_variant_comboBox_activated(int index);

    void on_mult_spinBox_valueChanged(int arg1);

    void on_scale_doubleSpinBox_valueChanged(double arg1);

    void on_move_btn_clicked();

    void on_scale_btn_clicked();

    void on_rotate_btn_clicked();

    void on_range_doubleSpinBox_valueChanged(double arg1);

    void on_resolution_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;

    unique_ptr<Canvas> canvas;
};
#endif // MAINWINDOW_H
