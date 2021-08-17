#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->draw_variant_comboBox->addItem("Каркасный");
    //ui->draw_variant_comboBox->addItem("Заполненный");

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
    canvas->generateNewLandscape(ui->size_value_label->text().toInt());
}

void MainWindow::on_clean_btn_clicked()
{
    canvas->cleanQImage();
    canvas->resetHeightsMap();
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


void MainWindow::on_draw_variant_comboBox_activated(int index)
{
    if (index >= 1)
    {
        QMessageBox::information(this, "Error", "No such DrawAlg");
        return;
    }
    DrawAlg new_alg = static_cast<DrawAlg>(index);
    canvas->setDrawAlg(new_alg);
    //canvas->setDrawAlg(index);
}

