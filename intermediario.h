#ifndef INTERMEDIARIO_H
#define INTERMEDIARIO_H

#include <QtCore>
#include <QObject>

class Intermediario : public QThread
{
public:
    Intermediario();
};

#endif // INTERMEDIARIO_H
