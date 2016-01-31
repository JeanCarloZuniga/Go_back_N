#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <QObject>
#include <QtCore>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <QWaitCondition>

class Servidor : public QThread
{
Q_OBJECT
public:
    Servidor(int puerto, int);
    ~Servidor();
    void run();

    void set_variables_intermediario(QWaitCondition *, QWaitCondition *, QList<QByteArray>*, QMutex *);

public slots:
    void buscar_conexion();
    void buscar_conexion_intermediario();
    void recibir();
    void recibir_intermediario();
    QByteArray obtener_ultima_lectura();
    bool lecturas_vacia();

private:
    QTcpServer servidor;
    QTcpSocket *cliente;
    QByteArray lectura;

    int rol;

    QList<QByteArray> *lecturas;

    QFile *archivo;
    QTextStream *escribir;

/**Variables para sincronizar el flujo con el intermediario**/
    QWaitCondition *intermediario_totem;
    QWaitCondition *servidor_totem;
    QList<QByteArray> *buffer;
    QMutex *mutex;


    bool es_paquete_esperado(int,int);
    void enviar_ack(int);
    int convertir(QByteArray *);

};

#endif // SERVIDOR_H
