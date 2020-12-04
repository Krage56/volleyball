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
                QPen(Qt::black), QBrush(Qt::yellow)){}

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
    _centralPoint = QPointF(p2.first - p1.first, p2.second - p1.second);
}

QPointF BorderLine::getPointF()const{
    return _centralPoint;
}

bool Platform::moveAcces(int key, const QPointF& currentCoords, Ball* ball, int top,
                         int left, int bottom, int right, int step)const{
    /*Запретим движение "в мяч"*/
    QPointF ballCenter = ball->getPosition();
    QPointF rectCenter = this->getCoords();
    if(collidesWithItem(ball) && ballCenter.y()+ball->r() < rectCenter.y() &&
            ((key == Qt::Key_W || key == 1062) || (key == Qt::Key_Up))){
        return false;
    }
    else if(collidesWithItem(ball) && ballCenter.y() - ball->r() > rectCenter.y() &&
            ((key == Qt::Key_S || key == 1067) || (key == Qt::Key::Key_Down))){
        return false;
    }
    else if (collidesWithItem(ball) && ballCenter.x() - ball->r() > rectCenter.x() &&
             ((key == Qt::Key_D || key == 1042) || (key == Qt::Key_Right))){
        return false;
    }
    else if (collidesWithItem(ball) && ballCenter.x() + ball->r() < rectCenter.x() &&
             ((key == Qt::Key_A || key == 1060) || (key == Qt::Key_Left))){
        return false;
    }
    /*Запрет на выход из гулага*/

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
    if((key == Qt::Key_A || key == 1060) || (key == Qt::Key_Left)){
        if(currentCoords.x() - step - w()/2 < left){
            return false;
        }
    }

    return true;
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
    _currentVelocity = new V2(pow(-1, (rand() % 2)), 6);
}


Ball::~Ball(){
    delete _currentVelocity;
    _currentVelocity = nullptr;
}

void Ball::setPosition(double x, double y){
    setPos(x, y);
}

void Ball::move(){
    _x += _currentVelocity->x();
    _y += _currentVelocity->y();
    setPosition(_x, _y);
}

V2 Ball::collProcess(BorderLine* border){
    V2* newVelocity;

    if(border->getKind() == Borders::top || border->getKind() == Borders::bottom){
        newVelocity = new V2(_currentVelocity->x(), _currentVelocity->y()*(-1));
    }
    else{
        newVelocity = new V2(_currentVelocity->x()*(-1), _currentVelocity->y());
    }
    delete _currentVelocity;
    _currentVelocity = newVelocity;
    return *newVelocity;
}

V2 Ball::collProcess(GeneralRect* rect){
    V2* newVelocity = nullptr;
    if(dynamic_cast<Platform*>(rect)){
        Platform* localRect = dynamic_cast<Platform*>(rect);
        QPointF rectCenter = localRect->getCoords();
        newVelocity = new V2(_x - rectCenter.x(), _y - rectCenter.y());
        newVelocity->normalize();
    }
    else{
        //std:: cout << _y << " " << rect->h() << std::endl << std::flush;
        if(_y < rect->h()/2){
            newVelocity = new V2(_x - rect->x(), _y - rect->y());
            newVelocity->normalize();
        }
        else{
            newVelocity = new V2((_x - rect->x())/abs(_x - rect->x()), 0);
        }
    }
    *newVelocity = *newVelocity * _currentVelocity->len();
    delete _currentVelocity;
    _currentVelocity = newVelocity;
    return *newVelocity;
}

bool Ball::isInteracted(QGraphicsItem* obj) const{
    if(dynamic_cast<BorderLine*>(obj)){
        BorderLine* border = dynamic_cast<BorderLine*>(obj);
        QPointF dest(_x + _currentVelocity->x(), _y + _currentVelocity->y());
        if(border->getKind() == Borders::top && dest.y() < border->getPointF().y()){
            return true;
        }
        if(border->getKind() == Borders::bottom && dest.y() > border->getPointF().y()){
            return true;
        }
        if(border->getKind() == Borders::left && dest.x() < border->getPointF().x()){
            return true;
        }
        if(border->getKind() == Borders::right && dest.x() > border->getPointF().x()){
            return true;
        }
    }
    else if(dynamic_cast<GeneralRect*>(obj)){
        if(dynamic_cast<Platform*>(obj)){
            Platform* p = dynamic_cast<Platform*>(obj);
            QPointF delta(_x - p->getCoords().x(), _y - p->getCoords().y());
            //Мяч над платформой
            if(_y + _r < p->getCoords().y() - p->h()/2){
                if(delta.y()*_currentVelocity->y() < 0){
                    return true;
                }
            }
            //Мяч под платформой
            else if(_y - _r > p->getCoords().y() + p->h()/2){
                if(delta.y()*_currentVelocity->y() < 0){
                    return true;
                }
            }
            //Мяч слева
            else if(_x + _r > p->getCoords().x() - p->w()/2){
                if(delta.x()*_currentVelocity->x() < 0){
                    return true;
                }
            }
            //Мяч справа
            else if(_x - _r > p->getCoords().x() + p->w()/2){
                if(delta.x()*_currentVelocity->x() < 0){
                    return true;
                }
            }
        }
        else{
            GeneralRect* rect = dynamic_cast<GeneralRect*>(obj);
            QPointF delta(_x - rect->getCoords().x(), _y - rect->getCoords().y());
            if(_y < rect->getCoords().y()){
                if(delta.y()*(_currentVelocity->y()) > 0){
                    return true;
                }
            }
            else{
                if(delta.x()*(_currentVelocity->x()) > 0){
                    return true;
                }
            }
        }
    }
    return false;
}

