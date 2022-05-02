#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->draw_variant_comboBox->setCurrentIndex(2);

    ui->size_value_label->setStyleSheet("border-style: solid; border-width: 1px; border-color: black; background-color: white");
    ui->color_label->setStyleSheet("background-color: rgb(20, 150, 20)");

    canvas = make_unique<Canvas>(new Canvas());
    //canvas->setDrawAlg(ZBUFFER_PARAM);
    //ui->gridLayout->addWidget(&(*canvas));
    ui->scrollArea->setWidget(&(*canvas));

    ui->threads_spinBox->hide();
    ui->scale_groupBox->hide();
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
        //ui->level_spinBox->setValue((n-1));
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
        //ui->level_spinBox->setValue((n-1));
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
    case 4:
        canvas->setDrawAlg(ZBUFFER_PARAM_THREADS);
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

        //canvas->transform(Point(dX, dY, dZ), Point(1, 1, 1), Point(0, 0, 0));
        canvas->move(Point(dX, dY, dZ));

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

        //canvas->transform(Point(0, 0, 0), Point(kX, kY, kZ), Point(0, 0, 0));
        canvas->scale(Point(kX, kY, kZ));

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

        //canvas->transform(Point(0, 0, 0), Point(1, 1, 1), Point(oX, oY, oZ));
        canvas->rotate(Point(oX, oY, oZ));

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


void MainWindow::on_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(canvas->getColor());
    if (color.isValid())
    {
        canvas->setLandscapeColor(color.red(), color.green(), color.blue());
        QString str = QString("background-color: rgb(%1, %2, %3)").arg(color.red()).arg(color.green()).arg(color.blue());
        ui->color_label->setStyleSheet(str);
    }
    else
    {
        QMessageBox::information(this, "Error", "Color is not valid");
    }
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    canvas->setSmoothing(bool(arg1));
}


void MainWindow::on_threads_spinBox_valueChanged(int arg1)
{
    canvas->setThreadsNumber(arg1);
}


void MainWindow::on_read_file_btn_clicked()
{
    string file_name = ui->file_name_lineEdit->text().toStdString();

    canvas->readFromFile(file_name);
}


void MainWindow::on_write_file_btn_clicked()
{
    string file_name = ui->file_name_lineEdit_2->text().toStdString();

    canvas->writeToFile(file_name);
}

void MainWindow::on_load_canvas_btn_clicked()
{
    CanvasBL cbl("hm.txt", "tpa.txt");
    canvas->selectCanvas(make_shared<LandscapeCanvas>(cbl.getHeightsMap(), cbl.getTriPolArray()));
}


void MainWindow::on_write_file_btn_2_clicked()
{
    canvas->getHeightsMapPoints()->writeToFile("tpa.txt");
}

