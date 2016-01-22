#include "cliente.h"
#include <QDebug>

Cliente::Cliente()
{

}

void Cliente::run()
{
    qDebug() << "CORRIENDO";
    emit salude_cliente();
}

