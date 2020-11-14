#include "playgrounditems.h"
#include "playground.h"
#include <iostream>


GeneralRect::GeneralRect(const QPoint& p, int w, int h,
                         const QPen& pen, const QBrush& brush):
    QGraphicsRectItem((-1)*w/2, (-1)*h/2, w, h)
  /*хотим работать с центром прямоугольника, поэтому так отодвинем
  нижнюю левую точку прямоугольника в лок. коорд-х*/
{
    setPen(pen);
    setBrush(brush);
    setPos(p);
    _centerPos = p;
}




Platform::Platform(const QPoint& p):
    GeneralRect(p, 150, 30,
                QPen(Qt::black), QBrush(Qt::yellow))
{
        for(int i = 0; i < 4; ++i){
            _colliedBorders[i] = false;
        }
}

QPointF Platform::getCoords()const{
    return mapToScene(rect().center());
}

void Platform::setCoords(const std::pair<qreal, qreal>& p) {
    setPos(p.first, p.second);
}

void Platform::setCoords(const QPointF& p){
    setPos(p);
}


BorderLine::BorderLine(std::pair<qreal, qreal> p1, std::pair<qreal, qreal> p2, Borders kind):
    QGraphicsLineItem(p1.first, p1.second, p2.first, p2.second)
{
    setPen(QPen(QColor(Qt::red)));
    setPos(mapToScene(0,0));
    _kind = kind;
}

QPointF BorderLine::getPointF()const{
    return QPointF(x(), y());
}


void Platform::collisionBehavior(const QVector<BorderLine*>& borders, const GeneralRect* net){
    for(int i = 0; i < borders.size(); ++i){
        if(collidesWithItem(borders[i])){
            _colliedBorders[i] = true;
        }
        else{
            _colliedBorders[i] = false;
        }
    }
}
