#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->size_value_label->setStyleSheet("border-style: solid; border-width: 1px; border-color: black; background-color: white");

    canvas = make_unique<Canvas>(new Canvas());
    ui->gridLayout->addWidget(&(*canvas));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_gen_btn_clicked()
{
    //canvas->generateNewLandscape(ui->size_value_label->text().toInt());
}

void MainWindow::on_clean_btn_clicked()
{
    canvas->cleanQImage();
    //canvas->resetHeightsMap();
}


void MainWindow::on_size_up_btn_released()
{
    QString text = ui->size_value_label->text();
    int n = text.toInt();
    n = (n - 1)*2+1;
    text = QString::number(n);
    ui->size_value_label->setText(text);
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
    }
}

