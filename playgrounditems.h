#ifndef PLAYGROUNDITEMS_H
#define PLAYGROUNDITEMS_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QVector>
#include <iostream>


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
        QPointF getPointF()const;
        Borders getKind()const{return _kind;}
        ~BorderLine()=default;
};



class Platform : public GeneralRect{
    bool _colliedBorders[4];
    public:
        QPointF getCoords()const override;
        void setCoords(const std::pair<qreal, qreal>& p);
        void setCoords(const QPointF&);
        bool moveAcces(int key, const QPointF& currentPos, int top,
                       int left, int bottom, int right, int step = 15)const;
        void collisionBehavior(const QVector<BorderLine*>& borders,
                               const GeneralRect* net = nullptr);
        bool leftBorderCol()const{return _colliedBorders[static_cast<int>(Borders::left)];}
        bool rightBorderCol()const{return _colliedBorders[static_cast<int>(Borders::right)];}
        bool topBorderCol()const{return _colliedBorders[static_cast<int>(Borders::top)];}
        bool bottomBorderCol()const{return _colliedBorders[static_cast<int>(Borders::bottom)];};
        Platform(const QPoint& p);
        ~Platform()=default;
};


#endif // PLAYGROUNDITEMS_H
