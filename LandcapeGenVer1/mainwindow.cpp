#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->draw_variant_comboBox->setCurrentIndex(2);

    ui->size_value_label->setStyleSheet("border-style: solid; border-width: 1px; border-color: black; background-color: white");

    canvas = make_unique<Canvas>(new Canvas());
    //canvas->setDrawAlg(ZBUFFER_PARAM);
    //ui->gridLayout->addWidget(&(*canvas));
    ui->scrollArea->setWidget(&(*canvas));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_gen_btn_clicked()
{
    canvas->generateNewLandscape(ui->size_value_label->text().toInt());
}

void MainWindow::on_clean_btn_clicked()
{
    cout << "Canvas Width = "<< canvas->width() << "; Canvas Height = " << canvas->height() << endl;
    canvas->cleanQImage();
    canvas->resetHeightsMap();
}


void MainWindow::on_size_up_btn_released()
{
    QString text = ui->size_value_label->text();
    int n = text.toInt();
    if (n < 1025)
    {
        n = (n - 1)*2+1;
        text = QString::number(n);
        ui->size_value_label->setText(text);
        ui->scale_doubleSpinBox->setValue(512./(n-1));
        ui->range_doubleSpinBox->setValue((n-1)*0.75);
        ui->level_spinBox->setValue((n-1));
    }
}


void MainWindow::on_size_down_btn_released()
{
    QString text = ui->size_value_label->text();
    int n = text.toInt();
    if (n > 3)
    {
        n = (n - 1)/2+1;
        text = QString::number(n);
        ui->size_value_label->setText(text);
        ui->scale_doubleSpinBox->setValue(512./(n-1));
        ui->range_doubleSpinBox->setValue((n-1)*0.75);
        ui->level_spinBox->setValue((n-1));
    }
}


void MainWindow::on_draw_variant_comboBox_activated(int index)
{
    switch (index)
    {
    case 0:
        canvas->setDrawAlg(CARCAS);
        break;
    case 1:
        canvas->setDrawAlg(TRIANGULAR);
        break;
    case 2:
        canvas->setDrawAlg(ZBUFFER_PARAM);
        break;
    case 3:
        canvas->setDrawAlg(ZBUFFER_INTERPOLATION);
        break;
    default:
        QMessageBox::information(this, "Error", "No such DrawAlg");
        ui->draw_variant_comboBox->setCurrentIndex(0);
        break;
    }
}

void MainWindow::on_mult_spinBox_valueChanged(int arg1)
{
    canvas->setMult(arg1);
}

void MainWindow::on_scale_doubleSpinBox_valueChanged(double arg1)
{
    canvas->setScale(arg1);
}


void MainWindow::on_move_btn_clicked()
{
    try
    {
        bool isDouble;

        double dX = ui->move_x->text().toDouble(&isDouble);
        if (!isDouble)
        {
            QMessageBox::information(this, "Error", "Параметры преобразовнний должны быть вещественным числами");
            return;
        }

        double dY = ui->move_y->text().toDouble(&isDouble);
        if (!isDouble)
        {
            QMessageBox::information(this, "Error", "Параметры преобразовнний должны быть вещественным числами");
            return;
        }

        double dZ = ui->move_z->text().toDouble(&isDouble);
        if (!isDouble)
        {
            QMessageBox::information(this, "Error", "Параметры преобразовнний должны быть вещественным числами");
            return;
        }

        canvas->transform(Point(dX, dY, dZ), Point(1, 1, 1), Point(0, 0, 0));

        canvas->draw();
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


void MainWindow::on_scale_btn_clicked()
{
    try
    {
        bool isDouble;

        double kX = ui->scale_x->text().toDouble(&isDouble);
        if (!isDouble)
        {
            QMessageBox::information(this, "Error", "Параметры преобразовнний должны быть вещественным числами");
            return;
        }

        double kY = ui->scale_y->text().toDouble(&isDouble);
        if (!isDouble)
        {
            QMessageBox::information(this, "Error", "Параметры преобразовнний должны быть вещественным числами");
            return;
        }

        double kZ = ui->scale_z->text().toDouble(&isDouble);
        if (!isDouble)
        {
            QMessageBox::information(this, "Error", "Параметры преобразовнний должны быть вещественным числами");
            return;
        }

        canvas->transform(Point(0, 0, 0), Point(kX, kY, kZ), Point(0, 0, 0));

        canvas->draw();
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


void MainWindow::on_rotate_btn_clicked()
{
    try
    {
        bool isDouble;

        double oX = ui->angle_x->text().toDouble(&isDouble);
        if (!isDouble)
        {
            QMessageBox::information(this, "Error", "Параметры преобразовнний должны быть вещественным числами");
            return;
        }

        double oY = ui->angle_y->text().toDouble(&isDouble);
        if (!isDouble)
        {
            QMessageBox::information(this, "Error", "Параметры преобразовнний должны быть вещественным числами");
            return;
        }

        double oZ = ui->angle_z->text().toDouble(&isDouble);
        if (!isDouble)
        {
            QMessageBox::information(this, "Error", "Параметры преобразовнний должны быть вещественным числами");
            return;
        }

        canvas->transform(Point(0, 0, 0), Point(1, 1, 1), Point(oX, oY, oZ));

        canvas->draw();
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


void MainWindow::on_range_doubleSpinBox_valueChanged(double arg1)
{
    canvas->setRange(arg1);
}


void MainWindow::on_level_spinBox_valueChanged(int arg1)
{
    canvas->setLevel(arg1);
}

void MainWindow::on_resolution_comboBox_currentTextChanged(const QString &arg1)
{
    qsizetype n = arg1.indexOf('x');

    QString width = "";
    for (int i = 0; i < n; i++)
    {
        width += arg1[i];
    }

    QString height = "";
    int str_size = arg1.size();
    for (int i = n+1; i < str_size; i++)
    {
        height += arg1[i];
    }
    int w = width.toInt();
    int h = height.toInt();

    canvas->setWidth(w);
    canvas->setHeight(h);
    canvas->updateResolution();
}

