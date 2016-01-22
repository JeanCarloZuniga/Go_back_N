#ifndef CLIENTE_H
#define CLIENTE_H

#include "mainwindow.h"
#include <QtCore>

class Cliente : public QThread
{
    Q_OBJECT
public:
    Cliente();
    void run();

signals:
    void salude_cliente();
};

#endif // CLIENTE_H
