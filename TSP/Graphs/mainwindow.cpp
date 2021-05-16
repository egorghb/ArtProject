#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myglwidget.h"
#include <QPainter>
#include <QGridLayout>
#include <QPushButton>
#include <mypainter.h>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myGLWidget *openGLW=new myGLWidget(this);
    QGridLayout *grid=new QGridLayout();
    QPushButton *btn1 = new QPushButton();
    btn1->setText("Print Matrix");
    QPushButton *btn2 = new QPushButton();
    btn2->setText("Input Matrix");
    grid->addWidget(openGLW,0,0);
    grid->addWidget(btn1, 1, 0);
    grid->addWidget(btn2, 2, 0);
    ui->centralwidget->setLayout(grid);
    connect(btn1, &QPushButton::clicked, openGLW,&myGLWidget::read_from_file);
    connect(btn2, &QPushButton::clicked, openGLW, &myGLWidget::make_file);
}
MainWindow::~MainWindow()
{
    delete ui;
}
