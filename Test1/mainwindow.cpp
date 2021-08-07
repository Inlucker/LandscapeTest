#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    canvas = make_unique<Canvas>(new Canvas());
    ui->gridLayout->addWidget(&(*canvas));
    //cout << "canvas width = " << canvas->width() << endl;
    //cout << "canvas height = " << canvas->height() << endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_gen_btn_clicked()
{
    canvas->generateNewLandscape();
}

void MainWindow::on_clean_btn_clicked()
{
    canvas->clean();
}

