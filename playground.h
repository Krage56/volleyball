#ifndef PLAYGROUND_H
#define PLAYGROUND_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <iostream>
#include <playgrounditems.h>
#include <QTimerEvent>

class Playground : public QGraphicsView
{
    public:
        Playground(QWidget* parent = 0);
        void keyPressEvent(QKeyEvent *event);
        void timerEvent(QTimerEvent*event){Q_UNUSED(event);};
        bool borderCollision(QGraphicsItem*)const;
        ~Playground()=default;
    private:
        QGraphicsScene _scene;
        Platform* _leftRect;
        Platform* _rightRect;
};

#endif // PLAYGROUND_H
