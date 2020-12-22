#ifndef PLAYGROUND_H
#define PLAYGROUND_H
#include <playgrounditems.h>
#include <QTimerEvent>

class Playground : public QGraphicsView
{
    public:
        Playground(QWidget* parent = 0);
        void keyPressEvent(QKeyEvent *event);
        void timerEvent(QTimerEvent*event);
        ~Playground()=default;
    protected:
        void gameOver();
        void newGame();
    private:
        QGraphicsScene _scene;
        Platform* _leftPlatform;
        Platform* _rightPlatform;
        GeneralRect* _volleyballNet;
        Ball* _ball;
        bool waiting;
};

#endif // PLAYGROUND_H
