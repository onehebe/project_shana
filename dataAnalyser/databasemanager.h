#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QWidget>
#include <QPainter>

class dataBaseManager : public QWidget
{
    Q_OBJECT
public:
    explicit dataBaseManager(QWidget *parent = 0);

signals:

public slots:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
};

#endif // DATABASEMANAGER_H
