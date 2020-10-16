#include "volleyball.h"

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QKeyEvent>
#include <iostream>

class Rect : public QGraphicsRectItem
{
    public:
    void setCoords(const std::pair<qreal, qreal>& p) { setPos(p.first, p.second); }
        Rect(double x, double y): QGraphicsRectItem(-5,-5,100,100)
        {
            setPen(QPen( Qt::black ));
            setBrush(QBrush(Qt::yellow));
            setPos(x,y);
        }
        ~Rect()=default;

};

class GazView : public QGraphicsView
{
    public:
        GazView(QWidget* parent = 0);
        void keyPressEvent(QKeyEvent *event);
        ~GazView()=default;
    private:
        QGraphicsScene _scene;
        Rect* _leftRect;
        Rect* _rightRect;
};

GazView::GazView(QWidget* parent)
    : QGraphicsView(parent)
    , _scene(this)
    , _leftRect(new Rect( 40, 40 ))
    , _rightRect(new Rect(80, 80))
{
    setMinimumSize(500,500);
    setScene(&_scene);
    centerOn(250,250);
    _scene.addItem(_leftRect);
    _scene.addItem(_rightRect);
    _rightRect->setBrush(Qt::green);
}

void GazView::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_W){
        //_leftRect->setBrush(Qt::gray);
        _leftRect->setCoords(std::make_pair(60,60));
    }
    if(e->key() == Qt::Key_Up){
//        _rightRect->setBrush(Qt::blue);
        _rightRect->setCoords(std::make_pair(70,70));
    }
}
int main(int ac, char *av[]){

    QApplication a(ac, av);
    GazView gv; gv.show();
    QObject::connect(
            &a, SIGNAL(lastWindowClosed()),
            &a, SLOT(quit()));

    return a.exec();
}
