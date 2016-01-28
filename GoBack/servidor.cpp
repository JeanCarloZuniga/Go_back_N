 #include "servidor.h"

/*
 * El constructor del servidor se encarga de conectar la SIGNAL de newConnection, propia de QTCPServer, con el SLOT de buscarConexion.
 * Posteriormente, escucha al puerto 8888.
*/
Servidor::Servidor(int puerto)
{
    connect(&servidor, SIGNAL(newConnection()),
      this, SLOT(buscarConexion()));

    servidor.listen(QHostAddress::Any, puerto);

    lecturas = new QList<QByteArray>();
    lecturas->append("-1:z"); //Default value used to avoid asking if the list is empty

    archivo = new QFile("Datos.txt");

    if(!archivo->open(QFile::WriteOnly | QFile::Text))
    {
        qDebug()<<"El archivo no se pudo abrir";
        return;
    }

    escribir = new QTextStream(archivo);
}

/*
 * Destructor para el servidor.
*/
Servidor::~Servidor()
{
  servidor.close();
  archivo->close();
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
    this, SLOT(recibir()));
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

/*
 * Recibe la data que envíe un cliente debidamente conectado a él por el puerto indicado
*/
void Servidor::recibir()
{
  lectura =   cliente->readAll();
  qDebug() << "[Servidor que escucha en " << servidor.serverPort() << "] : Recibí : " << lectura;


  if(es_paquete_esperado(lecturas->back(),lectura)) //Pregunta si es el esperado
  {
    lecturas->append(lectura); //Lo agrega
    (*escribir)<<QString(lectura); //Add the information in the file
    escribir->flush(); //Clean the buffer
  }

  //client->close();
}

QByteArray Servidor::obtener_ultima_lectura()
{
    QByteArray primero = lecturas->first();
    lecturas->pop_front();
    return primero;
}

bool Servidor::es_paquete_esperado(QByteArray ultimo, QByteArray nuevo)
{
    int ultimo_numero;
    int nuevo_numero;
    bool esperado = false;

    //TODO:Test this split
    QList<QByteArray> elementos = nuevo.split(':');
    elementos.append(ultimo.split(':'));

    //TODO:Test this convertion
    memcpy(&ultimo_numero, elementos[0],sizeof(int));
    memcpy(&nuevo_numero, elementos[2],sizeof(int));

    if((ultimo_numero+1) == nuevo_numero)
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
