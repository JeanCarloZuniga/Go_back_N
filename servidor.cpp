 #include "servidor.h"

/*
 * El constructor del servidor se encarga de conectar la SIGNAL de newConnection, propia de QTCPServer, con el SLOT de buscarConexion.
 * Posteriormente, escucha al puerto 8888.
*/
Servidor::Servidor(int puerto, int rol)
{


    this->rol = rol;

    if(!rol) // !0 = true
    {
        connect(&servidor, SIGNAL(newConnection()),
          this, SLOT(buscar_conexion()));

        archivo = new QFile("Datos.txt");
        if(!archivo->open(QFile::WriteOnly | QFile::Text))
        {
            qDebug()<<"El archivo no se pudo abrir";
            return;
        }

        escribir = new QTextStream(archivo);
    }
    else //!1 = false
    {
        connect(&servidor, SIGNAL(newConnection()),
          this, SLOT(buscar_conexion_intermediario()));
    }


    servidor.listen(QHostAddress::Any, puerto);

    lecturas = new QList<QByteArray>();
    lecturas->append("-1:z"); //Default value used to avoid asking if the list is empty


}

/*
 * Destructor para el servidor.
*/
Servidor::~Servidor()
{
  servidor.close();
  archivo->close();

  delete archivo;
  delete lecturas;
  delete escribir;
  delete cliente;
}

/*
 * Se utiliza el QTCPSocket "cliente" para que tome el lugar del cliente que se quiera conectar al servidor, buscarConexion se llama
 * justo cuando se inicializa el objeto servidor, esto es importante porque nextPendingConnection hace el papel de un ciclo que siempre
 * busca conexiones nuevas que quiera comunicarse con el servidor, por lo que no es necesario tener un loop que siempre escuche.
 * Al encontrar un cliente, se procede a recibir lo que él envíe, esto gracias al SIGNAL readyRead propio de QTCPSocket y al SLOT
 * destinado para recibir data: escucharCliente.
*/
void Servidor::buscar_conexion()
{
  cliente = servidor.nextPendingConnection(); //Devuelve 0 si no hay clientes

  connect(cliente, SIGNAL(readyRead()),
    this, SLOT(recibir()));
}




void Servidor::buscar_conexion_intermediario()
{
  cliente = servidor.nextPendingConnection(); //Devuelve 0 si no hay clientes

  connect(cliente, SIGNAL(readyRead()),
    this, SLOT(recibir_intermediario()));
}




/*
 * Se comienza a ejecutar el hilo para el servidor
*/
void Servidor::run()
{
    if(servidor.isListening())
    {
        qDebug() << "[Servidor que escucha en " << servidor.serverPort() << "] : Escuchando, usa la línea de comandos para probarme\n telnet 127.0.0.1 " << servidor.serverPort() << "\n Vivo en ese puerto.";
    }
}

void Servidor::set_variables_intermediario(QWaitCondition *intermediario, QWaitCondition *servidor, QList<QByteArray> *buffer, QMutex *mutex)
{
    this->intermediario_totem = intermediario;
    this->servidor_totem = servidor;
    this->buffer = buffer;
    this->mutex = mutex;

}


/*
 * Recibe la data que envíe un cliente debidamente conectado a él por el puerto indicado
*/
void Servidor::recibir()
{
  int nuevo;
  int ultimo;
  lectura =   cliente->readAll();
  qDebug() << "[Servidor que escucha en " << servidor.serverPort() << "] : Recibí : " << lectura;


  nuevo = convertir(&lectura);
  ultimo = convertir(&lecturas->back());

  if(es_paquete_esperado(ultimo,nuevo)) //Pregunta si es el esperado
  {
    lecturas->append(lectura); //Lo agrega
    (*escribir)<<QString(lectura); //Add the information in the file
    escribir->flush(); //Clean the buffer

    enviar_ack(nuevo+1);
  }

  //client->close();
}



void Servidor::recibir_intermediario()
{


    while(lectura == " ")
    {
        lectura =   cliente->readAll();

        mutex->lock();

        if(buffer->size() == 1000)
        {
            servidor_totem->wait(mutex);
        }

        buffer->append(lectura);

        mutex->unlock();

        mutex->lock();
        intermediario_totem->wakeAll();
        mutex->unlock();

    }
}

void Servidor::enviar_ack(int ack)
{
    cliente->write(QString::number(ack).toStdString().c_str());
}

int Servidor::convertir(QByteArray *paquete)
{
    int serie;
    QList<QByteArray> elementos = paquete->split(':');
    memcpy(&serie, elementos[0],sizeof(int));

    return serie;
}

QByteArray Servidor::obtener_ultima_lectura()
{
    QByteArray primero = lecturas->first();
    lecturas->pop_front();
    return primero;
}

bool Servidor::es_paquete_esperado(int ultimo, int nuevo)
{

    bool esperado = false;

    if((ultimo+1) == nuevo)
    {
        esperado = true;
    }

    return esperado;
}

bool Servidor::lecturas_vacia()
{
    if(lecturas->isEmpty())
    {
        return true;
    } else {
        return false;
    }
}
