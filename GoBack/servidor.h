#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <QObject>
#include <QtCore>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QList>
#include <QFile>
#include <QTextStream>

class Servidor : public QThread
{
Q_OBJECT
public:
    Servidor(int puerto);
    ~Servidor();
    void run();

public slots:
    void buscarConexion();
    void recibir();
    QByteArray obtener_ultima_lectura();
    bool lecturas_vacia();

private:
    QTcpServer servidor;
    QTcpSocket *cliente;
    QByteArray lectura;
    QList<QByteArray> *lecturas;

    QFile *archivo;
    QTextStream *escribir;

    bool es_paquete_esperado(QByteArray,QByteArray);

};

#endif // SERVIDOR_H
