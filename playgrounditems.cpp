#include "playgrounditems.h"
#include "playground.h"
#include <iostream>

Rect::Rect(qreal x, qreal y):
    QGraphicsRectItem(x, y, 150, 30)
{
        setPen(QPen(Qt::black));
        setBrush(QBrush(Qt::yellow));
        setPos(x,y);
        _x = x;
        _y = y;
}

void Rect::setCoords(const std::pair<qreal, qreal>& p) {
    setPos(p.first, p.second);
    _x = p.first;
    _y = p.second;
}

void Rect::setCoords(QPointF p){
    setPos(p);
    _x = p.x();
    _y = p.y();
}

QPoint Rect::getCoords()const{
    return QPoint(_x, _y);
;}
BorderLine::BorderLine(std::pair<qreal, qreal> p1, std::pair<qreal, qreal> p2):
    QGraphicsLineItem(p1.first, p1.second, p2.first, p2.second)
{
    setPen(QPen(QColor(Qt::red)));
    setPos(mapToScene(0,0));
}

QPointF BorderLine::getPointF()const{
    return QPointF(x(), y());
}
