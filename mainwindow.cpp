#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv2/highgui.hpp"
#include <QDebug>
#include "testthread.h"

TestThread testThread;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}
