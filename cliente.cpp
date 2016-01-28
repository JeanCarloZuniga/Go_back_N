#include "cliente.h"

Cliente::Cliente(int _rol)
{
    connect(&cliente, SIGNAL(connected()),
      this, SLOT(enviar()));

    rol = _rol;

    if(rol == 1)
    {
    servidor_cliente = new Servidor(8080); // 8080 mientras sirve el input del usuario
    servidor_cliente->start();

    cola_de_paquetes = new QList<paquete>();
    }
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
 * Toma el QString "archivo" que contiene la frase a enviar y la parsea en paquetes,
 * posteriormente encola esos paquetes en la cola de paquetes.
*/
void Cliente::enlistar_paquetes()
{
    paquete nuevo_paquete(-1, '0', std::clock(), true);
    for(int i=0; i<archivo.length(); i++)
    {
        nuevo_paquete.colocar_secuencia(i);
        nuevo_paquete.colocar_valor(archivo.at(i).toLatin1());
        cola_de_paquetes->append(nuevo_paquete);
    }
}

/*
 * Envían data al puerto al que se conecta el cliente
*/
void Cliente::enviar(QString paquete_a_enviar)
{
    if(rol==1)
    {
        //manda el paquete
        const char *enviar = paquete_a_enviar.toStdString().c_str();
        cliente.write(enviar, paquete_a_enviar.length());
    }
}

/*
 * Comienza la ejecución del hilo del cliente
*/
void Cliente::run()
{
    qDebug() << "[Cliente] : El cliente está corriendo ahora.";
    if(rol==1)
    {
        //envia los primeros paquetes
        if(!cola_de_paquetes->empty())
        {
            for(int i=0; i<tamano_ventana; i++)
            {
                //Comienza el timer
                //TODO: buscar takeAt
                //cola_de_paquetes->at(i).comenzar_timer();
                //Ensambla paquete a enviar
                QString paquete_a_enviar=cola_de_paquetes->at(i).obtener_secuencia() + ":"
                        + cola_de_paquetes->at(i).obtener_valor();
                emit enviar(paquete_a_enviar);
            }
        }
        while(!cola_de_paquetes->empty())
        {
            while(servidor_cliente->lecturas_vacia()
                  && !timeout_alcanzado(cola_de_paquetes->first().obtener_reloj(), std::clock()))
            {
                //El tiempo pasa
            }
            //si se venció el timeout
            if(servidor_cliente->lecturas_vacia())
            {
                for(int i=0; i<tamano_ventana; i++)
                {
                    //Reinicia el timer
                    //TODO: buscar takeAt
                    //cola_de_paquetes->at(i).comenzar_timer();
                    //Ensambla el paquete a enviar
                    QString paquete_a_enviar=cola_de_paquetes->at(i).obtener_secuencia() + ":"
                            + cola_de_paquetes->at(i).obtener_valor();
                    emit enviar(paquete_a_enviar);
                }
            //si se recibió el ACK
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
}

