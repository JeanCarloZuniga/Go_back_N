#include "cliente.h"
#include <QDebug>

Cliente::Cliente()
{

}

void Cliente::run()
{
    qDebug() << "[Cliente] : El cliente está corriendo ahora.";
    emit salude_cliente();
}

