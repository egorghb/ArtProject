#include "myglwidget.h"
#include "mypainter.h"
#include <QPainter>

myGLWidget::myGLWidget(QWidget *parent)
    :QOpenGLWidget(parent)
{
    mypainter=new myPainter;
}

void myGLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    mypainter->draw(&painter,event);
    painter.end();
}
