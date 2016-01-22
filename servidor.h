#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "mainwindow.h"
#include <QtCore>

class Servidor : public QThread
{
    Q_OBJECT
public:
    Servidor();
    void run();

signals:
    void salude_server();
};

#endif // SERVIDOR_H
