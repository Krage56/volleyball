#include "playgrounditems.h"
#include "playground.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

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
    _w = w;
    _h = h;
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

bool Platform::moveAcces(int key, const QPointF& currentCoords, int top,
                         int left, int bottom, int right, int step)const{
    if((key == Qt::Key_W || key == 1062) || (key == Qt::Key_Up)){
        if(currentCoords.y() - step - h()/2 < top){
            return false;
        }
    }
    if((key == Qt::Key_S || key == 1067) || (key == Qt::Key::Key_Down)){
        if(currentCoords.y() + step + h()/2 > bottom){
            return false;
        }
    }
    if((key == Qt::Key_D || key == 1042) || (key == Qt::Key_Right)){
        if(currentCoords.x() + step + w()/2 > right){
            return false;
        }
    }
    if(key == Qt::Key_A || key == 1060 || (key == Qt::Key_Left)){
        if(currentCoords.x() - step - w()/2 < left){
            return false;
        }
    }
    return true;
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

Ball::Ball(double x, double y, double r):
    QGraphicsEllipseItem(-r, -r, 2*r, 2*r)
{
    _r = r;
    _x = x;
    _y = y;
    setBrush(QColor(153,102,204));
    setPos(x, y);
    srand(time(0));
    //определим вектор движения при появлении
    //к кому из игроков полетит мяч в начале игры определяется случайно
    _impulses.emplace_back(new V2(pow(-1, (rand() % 2)), 4));
}


Ball::~Ball(){
    cleanImpulses();
}

void Ball::setPosition(double x, double y){
    setPos(x, y);
}

void Ball::cleanImpulses(){
    for(auto* item: _impulses){
        delete item;
        item = nullptr;
    }
}

void Ball::move(){
    V2 resulted;
    for(auto* item: _impulses){
        resulted = resulted + *item;
    }
    _x += resulted.x();
    _y += resulted.y();
    setPosition(_x,  _y);
}

