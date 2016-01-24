#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <QObject>
#include <QtCore>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
class Servidor : public QThread
{
Q_OBJECT
public:
    Servidor();
    ~Servidor();
    void run();

public slots:
    void buscarConexion();
    void recibir();

private:
    QTcpServer servidor;
    QTcpSocket *cliente;
};

#endif // SERVIDOR_H
