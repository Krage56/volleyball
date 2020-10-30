#ifndef PLAYGROUND_H
#define PLAYGROUND_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <iostream>
#include <playgrounditems.h>

class Playground : public QGraphicsView
{
    public:
        Playground(QWidget* parent = 0);
        void keyPressEvent(QKeyEvent *event);
        bool borderCollision(QGraphicsItem*)const;
        ~Playground()=default;
    private:
        QGraphicsScene _scene;
        Rect* _leftRect;
        Rect* _rightRect;
        enum BorderKinds{
            top = 0,
            left = 1,
            bottom = 2,
            right = 3,
            none = 4
        };
        QMap<BorderKinds, BorderLine*> _borders;

};

#endif // PLAYGROUND_H
