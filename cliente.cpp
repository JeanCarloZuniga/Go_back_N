#include "cliente.h"
#include <QDebug>
#include <QHostAddress>

/*
 * El constructor conecta la SIGNAL connected propia de QTcpSocket con el SLOT enviar
*/
Cliente::Cliente()
{
  connect(&cliente, SIGNAL(connected()),
    this, SLOT(enviar()));
}

/*
 * Destructor para el cliente
*/
Cliente::~Cliente()
{
  cliente.close();
}

/*
 * Conecta al cliente con un puerto
*/
void Cliente::conectar(QString ip, quint16 puerto)
{
  QHostAddress direccion_ip(ip);
  cliente.connectToHost(direccion_ip, puerto);
}

/*
 * Envían data al puerto al que se conecta el cliente
*/
void Cliente::enviar()
{
  cliente.write("Hello, world", 13);
}

/*
 * Comienza la ejecución del hilo del cliente
*/
void Cliente::run()
{
    qDebug() << "[Cliente] : El cliente está corriendo ahora.";
    emit salude_cliente();
    this->conectar("127.0.0.1", 8888);
}

