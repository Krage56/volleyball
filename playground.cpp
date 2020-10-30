#include "playground.h"
#include <iostream>
Playground::Playground(QWidget* parent)
    : QGraphicsView(parent)
    , _scene(this)
{
    const int width = 1024, height = 648;
    setMinimumSize(width, height);

    setScene(&_scene);
    _scene.setSceneRect(0, 0, width, height);

    centerOn(_scene.width()/2, _scene.height()/2);

    _borders.insert(BorderKinds::top, new BorderLine(std::make_pair(0,0), std::make_pair(_scene.width(), 0)));
    _borders.insert(BorderKinds::left,
                    new BorderLine(std::make_pair(0,_scene.height()), std::make_pair(0, 0)));
    _borders.insert(BorderKinds::bottom,
                    new BorderLine(std::make_pair(0,_scene.height()),
                                   std::make_pair(_scene.width(), _scene.height())));
    _borders.insert(BorderKinds::right,
                    new BorderLine(std::make_pair(_scene.width(), _scene.height()),
                                   std::make_pair(_scene.width(), 0)));
    for (const auto iter: _borders){
        _scene.addItem(iter);
    }

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    const QPoint leftRectPoint(80,_scene.sceneRect().bottomRight().y()/4),
            rightRectPoint(_scene.sceneRect().bottomRight().x()/2-150,
                           _scene.sceneRect().bottomRight().y()/4);

    _leftRect = new Rect((leftRectPoint).x(), (leftRectPoint).y());
    _rightRect = new Rect((rightRectPoint).x(), (rightRectPoint).y());
    _scene.addItem(_leftRect);
    _scene.addItem(_rightRect);
}

void Playground::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_W){
        auto current_coords = _leftRect->getCoords();
        _leftRect->setCoords(std::make_pair(current_coords.x(),current_coords.y()-30));
    }
    if(e->key() == Qt::Key_S){
        auto current_coords = _leftRect->getCoords();
        _leftRect->setCoords(std::make_pair(current_coords.x(),current_coords.y()+30));
    }
    if(e->key() == Qt::Key_D){
        auto current_coords = _leftRect->getCoords();
        _leftRect->setCoords(std::make_pair(current_coords.x()+30,current_coords.y()));
    }
    if(e->key() == Qt::Key_A){
        auto current_coords = _leftRect->getCoords();
        _leftRect->setCoords(std::make_pair(current_coords.x()-30,current_coords.y()));
    }


    if(e->key() == Qt::Key_Up){
        auto current_coords = _rightRect->getCoords();
        _rightRect->setCoords(std::make_pair(current_coords.x(),current_coords.y()-30));
    }
    if(e->key() == Qt::Key_Down){
        auto current_coords = _rightRect->getCoords();
        _rightRect->setCoords(std::make_pair(current_coords.x(),current_coords.y()+30));
    }
    if(e->key() == Qt::Key_Left){
        auto current_coords = _rightRect->getCoords();
        _rightRect->setCoords(std::make_pair(current_coords.x()-30,current_coords.y()));
    }
    if(e->key() == Qt::Key_Right){
        auto current_coords = _rightRect->getCoords();
        _rightRect->setCoords(std::make_pair(current_coords.x()+30,current_coords.y()));
    }
}


