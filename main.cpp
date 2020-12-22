
#include "playground.h"
#include <QApplication>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <iostream>

int main(int ac, char *av[]){
    QApplication a(ac, av);
    Playground gv; gv.show();
    QObject::connect(
            &a, SIGNAL(lastWindowClosed()),
            &a, SLOT(quit()));

    return a.exec();
}
