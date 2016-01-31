#ifndef INTERMEDIARIO_H
#define INTERMEDIARIO_H

#include <QtCore>
#include <QObject>


#include "servidor.h"
#include "cliente.h"

class Intermediario : public QThread
{
Q_OBJECT
public:
    Intermediario(int, int, float, int);
    ~Intermediario();

    void run();

private:
    Servidor *servidor_intermediario;
    Cliente *cliente_intermediario;

    int puerto_servidor;
    int puerto_cliente;
    float probabilidad;
    int modo;

    /**Variables servidor_intermediario - Servidor**/
    QWaitCondition *intermediario_totem;
    QWaitCondition *servidor_totem;
    QList<QByteArray> *buffer;
    QMutex *mutex;

    void comunicacion();

};

#endif // INTERMEDIARIO_H
