#include "databasemanager.h"

dataBaseManager::dataBaseManager(QWidget *parent) :
    QWidget(parent)
{
}

void dataBaseManager::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    QImage image(":/image/resource/psu.png");
    int x = (this->width()-image.width())/2;
    int y = (this->height()-image.height())/2;
    painter.drawImage(x,y,image);
}
