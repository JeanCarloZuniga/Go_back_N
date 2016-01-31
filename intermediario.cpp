#include "intermediario.h"



Intermediario::Intermediario(int puerto_servidor, int puerto_cliente, float perdida, int modo)
{
    this->puerto_servidor = puerto_servidor;
    this->puerto_cliente = puerto_cliente;
    this->probabilidad = perdida;
    this->modo = modo;

    intermediario_totem = new QWaitCondition();
    servidor_totem = new QWaitCondition();
    buffer = new QList<QByteArray>();
    mutex = new QMutex();


}

Intermediario::~Intermediario()
{
    delete servidor_intermediario;
    delete cliente_intermediario;
    delete intermediario_totem;
    delete servidor_totem;
    delete buffer;
    delete mutex;
}

void Intermediario::run()
{
    servidor_intermediario = new Servidor(puerto_servidor, 1); //Se crea al servidor que escucha en el intermediario
    cliente_intermediario = new Cliente(0);

    servidor_intermediario->set_variables_intermediario(intermediario_totem, servidor_totem, buffer, mutex);

    cliente_intermediario->start();
    cliente_intermediario->conectar("127.0.0.1", puerto_cliente); //Se conecta con el servidor al otro extremo

    comunicacion();
}

void Intermediario::comunicacion()
{
   servidor_intermediario->start();
   QByteArray lectura;

   while(lectura == " ")
   {
       mutex->lock();

       if(buffer->isEmpty())
       {
           intermediario_totem->wait(mutex);
       }

       mutex->unlock();



       mutex->lock();
       lectura = buffer->takeFirst();
       cliente_intermediario->enviar(lectura);
       servidor_totem->wakeAll();
       mutex->unlock();

   }
}

