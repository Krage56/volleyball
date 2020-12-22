#ifndef PLAYGROUNDITEMS_H
#define PLAYGROUNDITEMS_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include "v2.h"


class GeneralRect: public QGraphicsRectItem{
    QPoint _centerPos;
    int _w, _h;
    public:
        GeneralRect(const QPoint& p, int w, int h,
                    const QPen& pen, const QBrush& brush);
        int w()const{return _w;};
        int h()const{return _h;};
        virtual QPointF getCoords()const{return _centerPos;};
        virtual ~GeneralRect()=default;

};
enum class Borders{
    top = 0,
    left = 1,
    bottom = 2,
    right = 3
};
class BorderLine: public QGraphicsLineItem{
    Borders _kind;
    public:
        BorderLine(std::pair<qreal, qreal>, std::pair<qreal, qreal>, Borders);
        Borders getKind()const{return _kind;}
        ~BorderLine()=default;
};

class Ball: public QGraphicsEllipseItem{
    int _r;
    double _x, _y;
    V2* _currentVelocity;
    public:
        //Принимает координаты центра мячика и его радиус
        Ball(double x, double y, double r);
        //двигает мячик на 1 такт
        void move();
        //Возвращает текущий вектор скорости
        V2 getVec()const{return *_currentVelocity;}
        //Возвращает позицию центра мяча на сцене
        QPointF getPosition()const{return QPointF(_x, _y);}
        //Меняют вектор движения для мяча после столкновения
        V2 collProcess(GeneralRect* rect);
        V2 collProcess(BorderLine* border);
        //Возвращает радиус мячика
        int r()const{return _r;}
        ~Ball();
    protected:
        //Обёртка над setPos()
        void setPosition(double x, double y);
        //задаёт вектор движения в обход обсчёта взаимодействий
        void setVec(const V2& v){delete _currentVelocity; _currentVelocity = new V2(v);}
};


class Platform : public GeneralRect{
    public:
        QPointF getCoords()const override;
        void setCoords(const std::pair<qreal, qreal>& p);
        void setCoords(const QPointF&);
        bool moveAcces(int key, const QPointF& currentPos, Ball* ball, int top,
                       int left, int bottom, int right, int step = 15)const;
        Platform(const QPoint& p);
        ~Platform()=default;
};



#endif // PLAYGROUNDITEMS_H
