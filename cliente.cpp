#include "cliente.h"

Cliente::Cliente()
{
    connect(&cliente, SIGNAL(connected()),
      this, SLOT(enviar()));

    servidor_cliente = new Servidor(8080); // 8080 mientras sirve el input del usuario
    servidor_cliente->start();

    cola_de_paquetes = new QList<paquete>();
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
 * Set para el total de paquetes a enviar
*/
void Cliente::colocar_total_paquetes(int total)
{
    total_paquetes = total;
}

/*
 * Get para el total de paquetes a enviar
*/
int Cliente::obtener_total_paquetes()
{
    return total_paquetes;
}

bool Cliente::timeout_alcanzado(double tiempo_paquete, clock_t ahora)
{
    double duracion = ( ahora - tiempo_paquete ) / (double) CLOCKS_PER_SEC;
    if(duracion >= timeout)
    {
        return true;
    } else {
        return false;
    }
}

/*
 * Envían data al puerto al que se conecta el cliente
*/
void Cliente::enviar()
{
  //TODO : hacer que envie lo que debe, recibe un paquete, lo ensambla y lo manda
  cliente.write("Hello, world", 13);
}

/*
 * Comienza la ejecución del hilo del cliente
*/
void Cliente::run()
{
    qDebug() << "[Cliente] : El cliente está corriendo ahora.";
    //TODO mandar los primeros maes
    while(!cola_de_paquetes->empty())
    {
        while(servidor_cliente->lecturas_vacia()
              && timeout_alcanzado(cola_de_paquetes->first().obtener_reloj(), std::clock()))
        {
            //El tiempo pasa
        }
        if(servidor_cliente->lecturas_vacia())
        {
            //TODO : reenviar
        } else {
            while(!servidor_cliente->lecturas_vacia())
            {
                servidor_cliente->obtener_ultima_lectura();
                //TODO imprimir "Llegó ACK de cola paquetes first.seq"
                cola_de_paquetes->pop_front();
            }
        }
    }
}

