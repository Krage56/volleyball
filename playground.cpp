#include "playground.h"
#include "playgrounditems.h"
#include <iostream>
#include <cmath>
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
    Ball* ball = new Ball(width/2, _scene.sceneRect().top()+50, 30);
    _scene.addItem(ball);
    _ball = ball;
//    std::cout <<  _volleyballNet->getCoords().x()<< std::flush;
    startTimer(30);
}

void Playground::keyPressEvent(QKeyEvent *e){
    const int step = 15,
    bottom = _scene.sceneRect().bottom(),
    top = _scene.sceneRect().top();
    int left = 0,
    right = _scene.sceneRect().right();

    if((e->key() == Qt::Key_W || e->key() == 1062)){
        QPointF currentCoords = _leftPlatform->getCoords();

        if(!_leftPlatform->moveAcces(e->key(), currentCoords, top, left, bottom, right)){
            return;
        }
        _leftPlatform->setCoords(std::make_pair(currentCoords.x(),currentCoords.y()-step));
    }
    if((e->key() == Qt::Key_S || e->key() == 1067)){
        QPointF currentCoords = _leftPlatform->getCoords();
        if(!_leftPlatform->moveAcces(e->key(), currentCoords, top, left, bottom, right)){
            return;
        }
        _leftPlatform->setCoords(std::make_pair(currentCoords.x(),currentCoords.y()+step));
    }
    if((e->key() == Qt::Key_D || e->key() == 1042)){
        QPointF currentCoords = _leftPlatform->getCoords();
        right = _volleyballNet->getCoords().x() - _volleyballNet->w()/2;
        if(!_leftPlatform->moveAcces(e->key(), currentCoords, top, left, bottom, right)){
            return;
        }
        _leftPlatform->setCoords(std::make_pair(currentCoords.x()+step,currentCoords.y()));
    }
    if(e->key() == Qt::Key_A || e->key() == 1060){
        QPointF currentCoords = _leftPlatform->getCoords();
        if(!_leftPlatform->moveAcces(e->key(), currentCoords, top, left, bottom, right)){
            return;
        }
        _leftPlatform->setCoords(std::make_pair(currentCoords.x()-step,currentCoords.y()));
    }


    if(e->key() == Qt::Key_Up){
        QPointF currentCoords = _rightPlatform->getCoords();
        if(!_rightPlatform->moveAcces(e->key(), currentCoords, top, left, bottom, right)){
            return;
        }
        _rightPlatform->setCoords(std::make_pair(currentCoords.x(),currentCoords.y()-step));

    }
    if(e->key() == Qt::Key_Down){
        QPointF currentCoords = _rightPlatform->getCoords();
        if(!_rightPlatform->moveAcces(e->key(), currentCoords, top, left, bottom, right)){
            return;
        }
        _rightPlatform->setCoords(std::make_pair(currentCoords.x(),currentCoords.y()+step));
    }
    if(e->key() == Qt::Key_Left){
        QPointF currentCoords = _rightPlatform->getCoords();
        left = _volleyballNet->getCoords().x() + _volleyballNet->w()/2;
        if(!_rightPlatform->moveAcces(e->key(), currentCoords, top, left, bottom, right)){
            return;
        }
        _rightPlatform->setCoords(std::make_pair(currentCoords.x()-step,currentCoords.y()));
    }
    if(e->key() == Qt::Key_Right){
        QPointF currentCoords = _rightPlatform->getCoords();
        if(!_rightPlatform->moveAcces(e->key(), currentCoords, top, left, bottom, right)){
            return;
        }
        _rightPlatform->setCoords(std::make_pair(currentCoords.x()+step,currentCoords.y()));
    }
}


void Playground::timerEvent(QTimerEvent* event){
    Q_UNUSED(event);
    //координаты центра окружности при следующей отрисовке

    QList<QGraphicsItem*> collideWith = _ball->collidingItems();
    for(auto* c_item: collideWith){
        GeneralRect* rect = dynamic_cast<GeneralRect*>(c_item);
        if(!rect){
            BorderLine* borderCollied = dynamic_cast<BorderLine*>(c_item);
            if(borderCollied &&
                (borderCollied->getKind() == Borders::bottom ||
                 borderCollied->getKind() == Borders::top)){
                _ball->setVec(V2(_ball->getVec().x(), _ball->getVec().y()*(-1)));
            }
            else if(borderCollied &&
                    (borderCollied->getKind() == Borders::left ||
                     borderCollied->getKind() == Borders::right)){
                _ball->setVec(V2(_ball->getVec().x()*(-1), _ball->getVec().y()));
            }
        }
        else{
            if(rect && dynamic_cast<Platform*>(rect)){
                QPointF pCenter = rect->getCoords();
                QPointF bCenter = _ball->getCoords();
                V2* newV = new V2((bCenter.x()-pCenter.x()), (bCenter.y()-pCenter.y()));
                if(_ball->getVec().operator bool()){
                    newV->normalize();
                    (*newV) = (*newV) * _ball->getVec().len();
                    _ball->setVec(newV);
                }
            }
        }
    }

//    bool velocityChanged = false;
//    double oldLen = _ball->getVec().len();
//    if(dest.x() - _ball->r() < 0){
//        double distX = 0, distY = 0;
//        distX = _ball->getCoords().x();
//        distY = sqrt(pow(_ball->getVec().len()/_ball->getVec().x(), 2) - 1) * distX;
//        velocityChanged = true;
//        _ball->setVec(V2(distX, distY));
//    }
//    else if(dest.y()/* - _ball->r()/oldLen*/ < 0){
//        double distX = 0, distY = 0;
//        distY = _ball->getCoords().y();
//        distX = sqrt(pow(_ball->getVec().len()/_ball->getVec().y(), 2) - 1) * distY;
//        velocityChanged = true;
//        _ball->setVec(V2(distX, distY));
//    }
    QPointF dest(_ball->getCoords().x()+_ball->getVec().x(),
                 _ball->getCoords().y()+_ball->getVec().y());
    double oldLen = _ball->getVec().len();
    bool vectorChanged = false;
    if(dest.x() - _ball->r() < 0){
        //служебная величина, нужна для построения коррекции
        double dLen = sqrt(pow((_ball->getCoords().x()-dest.x()), 2)+pow((_ball->getCoords().y()-dest.y()), 2));
        //определяет, на сколько шар выкатился из гулага
        double delta = _ball->getCoords().x()-_ball->r();
        //коррекция - на сколько нужно откатить шарик назад по заданному направлению
        double correction = dLen * (delta / _ball->r());
        if(_ball->getVec().operator bool()){
            _ball->setVec(_ball->getVec().normalize()*(correction));
            if(qFuzzyCompare(correction, 0)){
                _ball->setVec(V2(1,6));
            }
            vectorChanged = true;
        }
        std::cout << correction << std::endl << std::flush;
    }
    _ball->move();
    if(vectorChanged && _ball->getVec().operator bool())
        _ball->setVec(_ball->getVec().normalize()*oldLen);

//    if(velocityChanged){
//        _ball->setVec(_ball->getVec().normalize()*oldLen);
//    }
}
