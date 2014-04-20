#ifndef LAYOUTDESIGNER_H
#define LAYOUTDESIGNER_H

#include <QWidget>
#include <QPainter>

class layoutDesigner : public QWidget
{
    Q_OBJECT
public:
    explicit layoutDesigner(QWidget *parent = 0);

signals:

public slots:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
};

#endif // LAYOUTDESIGNER_H
