#include "servidor.h"
#include <iostream>
using namespace std;

/*
 * El constructor del servidor se encarga de conectar la SIGNAL de newConnection, propia de QTCPServer, con el SLOT de buscarConexion.
 * Posteriormente, escucha al puerto 8888.
*/
Servidor::Servidor()
{
  connect(&servidor, SIGNAL(newConnection()),
    this, SLOT(buscarConexion()));

  servidor.listen(QHostAddress::Any, 8888);
}

/*
 * Destructor para el servidor.
*/
Servidor::~Servidor()
{
  servidor.close();
}

/*
 * Se utiliza el QTCPSocket "cliente" para que tome el lugar del cliente que se quiera conectar al servidor, buscarConexion se llama
 * justo cuando se inicializa el objeto servidor, esto es importante porque nextPendingConnection hace el papel de un ciclo que siempre
 * busca conexiones nuevas que quiera comunicarse con el servidor, por lo que no es necesario tener un loop que siempre escuche.
 * Al encontrar un cliente, se procede a recibir lo que él envíe, esto gracias al SIGNAL readyRead propio de QTCPSocket y al SLOT
 * destinado para recibir data: escucharCliente.
*/
void Servidor::buscarConexion()
{
  cliente = servidor.nextPendingConnection(); //Devuelve 0 si no hay clientes

  connect(cliente, SIGNAL(readyRead()),
    this, SLOT(escucharCliente()));
}

/*
 * Se comienza a ejecutar el hilo para el servidor
*/
void Servidor::run()
{
    qDebug() << "[Servidor] : El servidor está corriendo ahora.";
    if(servidor.isListening())
    {
        qDebug() << "[Servidor] : Escuchando, usa la línea de comandos para probarme\n telnet 127.0.0.1 8888\n Vivo en ese puerto.";
    }
}

/*
 * Recibe la data que envíe un cliente debidamente conectado a él por el puerto indicado
*/
void Servidor::escucharCliente()
{
  QByteArray lectura =   cliente->readAll();
  qDebug() << "[Servidor] : Recibí : " << lectura;
  //client->close();
}
