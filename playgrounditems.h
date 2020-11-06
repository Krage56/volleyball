#ifndef PLAYGROUNDITEMS_H
#define PLAYGROUNDITEMS_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <iostream>

/*абстрактный класс прямоугольник*/

class GeneralRect: public QGraphicsRectItem{
    QPoint _centerPos;
    public:
        GeneralRect(const QPoint& p, int w, int h,
                    const QPen& pen, const QBrush& brush);
        virtual QPointF getCoords()const{return _centerPos;};
        virtual ~GeneralRect()=default;

};
class Platform : public GeneralRect{
    bool _colliedBorders[4];
    public:
        virtual QPointF getCoords()const override;
        void setCoords(const std::pair<qreal, qreal>& p);
        void setCoords(const QPointF& );
        Platform(const QPoint& p);
        ~Platform()=default;
};

//class Rect : public QGraphicsRectItem
//{
//    qreal _x, _y;
//    bool _colliedBorders[4];
//    public:
//    void setCoords(const std::pair<qreal, qreal>& p);
//    void setCoords(QPointF p);
//    QPoint getCoords()const;
//    Rect(qreal x, qreal y);
//    ~Rect()=default;
//};


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
        QPointF getPointF()const;
        ~BorderLine()=default;
};

#endif // PLAYGROUNDITEMS_H
