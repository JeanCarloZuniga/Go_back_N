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
        //Eliminar luego
        archivo = "hola mundo";
        enlistar_paquetes();
        tamano_ventana = 3;
        timeout=1;
        //
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
 * Compara el tiempo del inicio del primer paquete enviado con el tiempo actual
*/
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
    for(int i=0; i<archivo.length(); i++)
    {
        paquete *nuevo_paquete = new paquete(-1, '0', std::clock(), true);
        nuevo_paquete->colocar_secuencia(i);
        nuevo_paquete->colocar_valor(archivo.at(i));
        //
        qDebug() << "Encolando: " << nuevo_paquete->obtener_secuencia() << ":" << nuevo_paquete->obtener_valor();
        //
        cola_de_paquetes.push_back(nuevo_paquete);
    }
}

/*
 * Forma el paquete que será enviado
*/
void Cliente::ensamblar_paquete(int indice)
{
    paquete_a_enviar="";
    //Ensambla el paquete a enviar
    paquete_a_enviar = QString::number(cola_de_paquetes[indice]->obtener_secuencia()) + ":";
    paquete_a_enviar = paquete_a_enviar + cola_de_paquetes[indice]->obtener_valor();
    cola_de_paquetes[indice]->comenzar_timer();
}

/*
 * Envían data al puerto al que se conecta el cliente
*/
void Cliente::enviar()
{
    if(rol==1 && id==QThread::currentThreadId())
    {
        //manda el paquete
        qDebug() << "[Cliente:" << this->rol << "]" << "Ahora enviando: " << paquete_a_enviar;
        const char *enviar_str = paquete_a_enviar.toStdString().c_str();
        cliente.write(enviar_str, paquete_a_enviar.length());
    }
}

/*
 * Comienza la ejecución del hilo del cliente
*/
void Cliente::run()
{

    this->id = QThread::currentThreadId();
    qDebug() << "[Cliente] : El cliente " << this->rol << " está corriendo ahora.";
    if(rol==1)
    {
        int indice_ultimo_archivo_enviado;
        //Espera hasta que haya un archivo a enviar
        while(archivo.isEmpty())
        {
            //Esperando a que el usuario seleccione un archivo con la interfaz
        }
        //Envia los primeros "tamaño ventana" paquetes
       if(!cola_de_paquetes.empty())
        {
            int tope_de_primer_envio = tamano_ventana;
            //Caso en el que la ventana sea más grande que el archivo a enviar.
            if(tamano_ventana > archivo.length())
            {
                tope_de_primer_envio = archivo.length();
            }
            indice_ultimo_archivo_enviado = tope_de_primer_envio;
            for(int i=0; i<tope_de_primer_envio; i++)
            {
                ensamblar_paquete(i);
                emit enviar();
            }
            qDebug() << "Envié los primeros tamano_ventana paquetes";
        }
        //Ciclo principal que se encarga de enviar todos los paquetes
        while(!cola_de_paquetes.empty())
        {
            qDebug() << "----------------------Ciclo principal--------------------";
            while(servidor_cliente->lecturas_vacia()
                  && !timeout_alcanzado(cola_de_paquetes.front()->obtener_reloj(), std::clock()))
            {
                //El tiempo pasa
            }
            //si se venció el timeout
            if(servidor_cliente->lecturas_vacia())
            {
                qDebug() << "Se venció el timeout";
                for(int i=0; i<indice_ultimo_archivo_enviado; i++) //antes tamano ventana
                {
                    ensamblar_paquete(i);
                    emit enviar(); //Aqui
                }
            //si se recibió el ACK
            } else {
                while(!servidor_cliente->lecturas_vacia())
                {
                    QByteArray ack_leido = servidor_cliente->obtener_ultima_lectura();
                    if(ack_leido.toInt() == cola_de_paquetes.front()->obtener_secuencia())
                    {
                        //TODO imprimir "Llegó ACK de cola paquetes first.seq"
                        cola_de_paquetes.erase(cola_de_paquetes.begin());
                        //Si aun quedan paquetes, deslizo la ventana
                        if(!cola_de_paquetes.empty())
                        {
                            indice_ultimo_archivo_enviado++;
                            ensamblar_paquete(indice_ultimo_archivo_enviado);
                            emit enviar();
                        }
                    }
                }
            }
        }
    }
}

