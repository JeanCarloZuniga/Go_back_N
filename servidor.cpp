#include "servidor.h"

Servidor::Servidor()
{

}

void Servidor::run()
{
    qDebug() << "CORRIENDO SERVER";
    emit salude_server();
}
