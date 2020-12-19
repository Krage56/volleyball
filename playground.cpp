#include "playground.h"
#include "playgrounditems.h"
#include <iostream>
#include <cmath>
#include <set>
#include <QTest>
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

    Ball* ball = new Ball(width/2, _scene.sceneRect().top()+50, 30);
    _scene.addItem(ball);
    _ball = ball;

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

    //std::cout << _volleyballNet->getCoords().x() << std::flush;
    waiting = false;
    startTimer(50);
}

void Playground::keyPressEvent(QKeyEvent *e){
    const int step = 15,
    bottom = _scene.sceneRect().bottom(),
    top = _scene.sceneRect().top();
    int left = 0,
    right = _scene.sceneRect().right();
    //std::cout << "I was in key event\n" << std::flush;
    if((e->key() == Qt::Key_W || e->key() == 1062)){
        QPointF currentCoords = _leftPlatform->getCoords();

        if(!_leftPlatform->moveAcces(e->key(), currentCoords, _ball, top, left, bottom, right)){
            return;
        }
        _leftPlatform->setCoords(std::make_pair(currentCoords.x(),currentCoords.y()-step));
    }
    if((e->key() == Qt::Key_S || e->key() == 1067)){
        QPointF currentCoords = _leftPlatform->getCoords();
        if(!_leftPlatform->moveAcces(e->key(), currentCoords, _ball, top, left, bottom, right)){
            return;
        }
        _leftPlatform->setCoords(std::make_pair(currentCoords.x(),currentCoords.y()+step));
    }
    if((e->key() == Qt::Key_D || e->key() == 1042)){
        QPointF currentCoords = _leftPlatform->getCoords();
        right = _volleyballNet->getCoords().x() - _volleyballNet->w()/2;
        if(!_leftPlatform->moveAcces(e->key(), currentCoords, _ball, top, left, bottom, right)){
            return;
        }
        _leftPlatform->setCoords(std::make_pair(currentCoords.x()+step,currentCoords.y()));
    }
    if(e->key() == Qt::Key_A || e->key() == 1060){
        QPointF currentCoords = _leftPlatform->getCoords();
        if(!_leftPlatform->moveAcces(e->key(), currentCoords, _ball, top, left, bottom, right)){
            return;
        }
        _leftPlatform->setCoords(std::make_pair(currentCoords.x()-step,currentCoords.y()));
    }


    if(e->key() == Qt::Key_Up){
        QPointF currentCoords = _rightPlatform->getCoords();
        if(!_rightPlatform->moveAcces(e->key(), currentCoords, _ball, top, left, bottom, right)){
            return;
        }
        _rightPlatform->setCoords(std::make_pair(currentCoords.x(),currentCoords.y()-step));

    }
    if(e->key() == Qt::Key_Down){
        QPointF currentCoords = _rightPlatform->getCoords();
        if(!_rightPlatform->moveAcces(e->key(), currentCoords, _ball, top, left, bottom, right)){
            return;
        }
        _rightPlatform->setCoords(std::make_pair(currentCoords.x(),currentCoords.y()+step));
    }
    if(e->key() == Qt::Key_Left){
        QPointF currentCoords = _rightPlatform->getCoords();
        left = _volleyballNet->getCoords().x() + _volleyballNet->w()/2;
        if(!_rightPlatform->moveAcces(e->key(), currentCoords, _ball, top, left, bottom, right)){
            return;
        }
        _rightPlatform->setCoords(std::make_pair(currentCoords.x()-step,currentCoords.y()));
    }
    if(e->key() == Qt::Key_Right){
        QPointF currentCoords = _rightPlatform->getCoords();
        if(!_rightPlatform->moveAcces(e->key(), currentCoords, _ball, top, left, bottom, right)){
            return;
        }
        _rightPlatform->setCoords(std::make_pair(currentCoords.x()+step,currentCoords.y()));
    }
}


void Playground::timerEvent(QTimerEvent* event){
    Q_UNUSED(event);
    /*if(waiting){
        waiting = false;
        QTest::qSleep(4000);
        newGame();
        return;
    }
    QList<QGraphicsItem*> collideWith = _ball->collidingItems();
    for(auto* item: collideWith){
        BorderLine* p1 = dynamic_cast<BorderLine*>(item);
        GeneralRect* p2 = dynamic_cast<GeneralRect*>(item);
        if(p1){
            if(!(p1->getKind() == Borders::top)){
                gameOver();
                return;
            }
        }
        if(p2){
            if(!dynamic_cast<Platform*>(item)){
                if(_ball->getPosition().y() >= _scene.sceneRect().bottom() - p2->h()){
                    gameOver();
                    return;
                }
            }
        }
    }
    //Мяч взаимодействует соприкасается с одним объектом
    if(collideWith.empty()){
        _ball->move();
    }
    else if(collideWith.size() == 1){
        GeneralRect* p1 = dynamic_cast<GeneralRect*>(*collideWith.begin());
        BorderLine* p2 = dynamic_cast<BorderLine*>(*collideWith.begin());
        if(p1){
            _ball->collProcess(p1);
        }
        if(p2){
            _ball->collProcess(p2);
        }
        _ball->move();
    }
*/

    QList<QGraphicsItem*> collideWith = _ball->collidingItems();
    if(collideWith.empty()){
        _ball->move();
    }
    else if(collideWith.size() == 1){
        for(auto* item: collideWith){
            BorderLine* p1 = dynamic_cast<BorderLine*>(item);
            GeneralRect* p2 = dynamic_cast<GeneralRect*>(item);
            if(p2 && collideWith.size() == 1){
                _ball->collProcess(p2);
            }
            else if(p1 && collideWith.size() == 1){
                _ball->collProcess(p1);
            }
        }
        _ball->move();
    }
    else{
        std::set<BorderLine*> borders_collied;
        std::set<GeneralRect*> rects_collied;
        for(auto* item: collideWith){
            BorderLine* p1 = dynamic_cast<BorderLine*>(item);
            GeneralRect* p2 = dynamic_cast<GeneralRect*>(item);
            if(p2){
                rects_collied.insert(p2);
            }

            if(p1){
                borders_collied.insert(p1);
            }
        }
        bool processed = false;
        for(auto* item: rects_collied){
            if(_ball->isInteracted(item)){
                processed = true;
                _ball->collProcess(item);
                break;
            }
        }
        if(processed)
            return;
        for(auto* item: borders_collied){
            if(_ball->isInteracted(item)){
                processed = true;
                _ball->collProcess(item);
                break;
            }
        }
    }

//    for(auto* item: collideWith){
//        BorderLine* p1 = dynamic_cast<BorderLine*>(item);
//        GeneralRect* p2 = dynamic_cast<GeneralRect*>(item);
//        if(p2 && _ball->isInteracted(p2) && collideWith.size() > 1){
//             _ball->collProcess(p2);
//        }
//        else if(p2 && collideWith.size() == 1){
//            _ball->collProcess(p2);
//        }
//        else if(p1 && _ball->isInteracted(p1)){
//            _ball->collProcess(p1);
//        }
//        else if(p1 && collideWith.size() == 1){
//            _ball->collProcess(p1);
//        }
//    }
//    _ball->move();
}

void Playground::gameOver(){
    _scene.removeItem(_ball);
    _scene.removeItem(_leftPlatform);
    _scene.removeItem(_rightPlatform);
    delete _ball;
    delete _leftPlatform;
    delete  _rightPlatform;
    _ball = nullptr;
    _leftPlatform = nullptr;
    _rightPlatform = nullptr;
    waiting = true;
}

void Playground::newGame(){
    const QPoint leftRectPoint(150,_scene.sceneRect().bottomRight().y()/2),
            rightRectPoint(_scene.sceneRect().bottomRight().x()-150,
                           _scene.sceneRect().bottomRight().y()/2);

    _leftPlatform = new Platform(leftRectPoint);
    _rightPlatform = new Platform(rightRectPoint);
    _scene.addItem(_leftPlatform);
    _scene.addItem(_rightPlatform);

    Ball* ball = new Ball(_scene.sceneRect().width()/2, _scene.sceneRect().top()+50, 30);
    _scene.addItem(ball);
    _ball = ball;
}
