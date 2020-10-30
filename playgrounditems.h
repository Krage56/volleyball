#ifndef PLAYGROUNDITEMS_H
#define PLAYGROUNDITEMS_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <iostream>

class Rect : public QGraphicsRectItem
{
    qreal _x, _y;
    public:
    void setCoords(const std::pair<qreal, qreal>& p);
    void setCoords(QPointF p);
    QPoint getCoords()const;
    Rect(qreal x, qreal y);
    ~Rect()=default;
};
class BorderLine: public QGraphicsLineItem{
    public:
        BorderLine(std::pair<qreal, qreal>, std::pair<qreal, qreal>);
        QPointF getPointF()const;
        ~BorderLine()=default;
};

#endif // PLAYGROUNDITEMS_H
