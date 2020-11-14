#ifndef PLAYGROUND_H
#define PLAYGROUND_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QVector>
#include <playgrounditems.h>
#include <QTimerEvent>

class Playground : public QGraphicsView
{
    public:
        Playground(QWidget* parent = 0);
        void keyPressEvent(QKeyEvent *event);
        void timerEvent(QTimerEvent*event);
        QVector<BorderLine*> getBorders()const{return _borders;}
        ~Playground()=default;
    private:
        QGraphicsScene _scene;
        Platform* _leftPlatform;
        Platform* _rightPlatform;
        GeneralRect* _volleyballNet;
        QVector<BorderLine*> _borders;
};

#endif // PLAYGROUND_H