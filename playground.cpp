#include "playground.h"
#include "playgrounditems.h"
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

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    const QPoint leftRectPoint(150,_scene.sceneRect().bottomRight().y()/2),
            rightRectPoint(_scene.sceneRect().bottomRight().x()-150,
                           _scene.sceneRect().bottomRight().y()/2);

    _leftPlatform = new Platform(leftRectPoint);
    _rightPlatform = new Platform(rightRectPoint);
    _scene.addItem(_leftPlatform);
    _scene.addItem(_rightPlatform);

    _borders.push_back(new BorderLine(std::make_pair(0,0), std::make_pair(_scene.width(), 0), Borders::top));
    _borders.push_back(new BorderLine(std::make_pair(0,_scene.height()), std::make_pair(0, 0), Borders::left));
    _borders.push_back(new BorderLine(std::make_pair(0,_scene.height()),
                                      std::make_pair(_scene.width(), _scene.height()), Borders::bottom));
    _borders.push_back(new BorderLine(std::make_pair(_scene.width(), _scene.height()),
                                      std::make_pair(_scene.width(), 0), Borders::right));
    for(auto* el: _borders){
        _scene.addItem(el);
    }


    const int _volleyballNetH = 450, _volleyballNetW = 20;
    _volleyballNet = new GeneralRect(QPoint(_scene.sceneRect().center().x(),
                                            _scene.sceneRect().top()+(height-_volleyballNetH/2)),
                                     _volleyballNetW, _volleyballNetH, QPen(Qt::black), QBrush(Qt::black));
    _scene.addItem(_volleyballNet);
//    std::cout <<  _volleyballNet->getCoords().x()<< std::flush;
    startTimer(50);
}

void Playground::keyPressEvent(QKeyEvent *e){
    const int step = 30,
    bottom = _scene.sceneRect().bottom(),
    top = _scene.sceneRect().top(), /*top := 0*/
    left = 0,
    right = _scene.sceneRect().right();
    if((e->key() == Qt::Key_W || e->key() == 1062) && _leftPlatform->getCoords().y() - step >= top){
        auto current_coords = _leftPlatform->getCoords();
        _leftPlatform->setCoords(std::make_pair(current_coords.x(),current_coords.y()-step));
    }
    if((e->key() == Qt::Key_S || e->key() == 1067) && _leftPlatform->getCoords().y() + step <= bottom){
        auto current_coords = _leftPlatform->getCoords();
        _leftPlatform->setCoords(std::make_pair(current_coords.x(),current_coords.y()+step));
    }
    if((e->key() == Qt::Key_D || e->key() == 1042) && _leftPlatform->getCoords().x() + step <= right){
        auto current_coords = _leftPlatform->getCoords();
        _leftPlatform->setCoords(std::make_pair(current_coords.x()+step,current_coords.y()));
    }
    if(e->key() == Qt::Key_A || e->key() == 1060){
        auto current_coords = _leftPlatform->getCoords();
        _leftPlatform->setCoords(std::make_pair(current_coords.x()-step,current_coords.y()));
    }


    if(e->key() == Qt::Key_Up){
        auto current_coords = _rightPlatform->getCoords();
        _rightPlatform->setCoords(std::make_pair(current_coords.x(),current_coords.y()-step));

    }
    if(e->key() == Qt::Key_Down){
        auto current_coords = _rightPlatform->getCoords();
        _rightPlatform->setCoords(std::make_pair(current_coords.x(),current_coords.y()+step));
    }
    if(e->key() == Qt::Key_Left){
        auto current_coords = _rightPlatform->getCoords();
        _rightPlatform->setCoords(std::make_pair(current_coords.x()-step,current_coords.y()));
    }
    if(e->key() == Qt::Key_Right){
        auto current_coords = _rightPlatform->getCoords();
        _rightPlatform->setCoords(std::make_pair(current_coords.x()+step,current_coords.y()));
    }
}


void Playground::timerEvent(QTimerEvent* event){
    Q_UNUSED(event);
    _leftPlatform->collisionBehavior(_borders);
    _rightPlatform->collisionBehavior(_borders);
}
