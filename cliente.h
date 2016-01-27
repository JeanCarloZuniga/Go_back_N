#ifndef CLIENTE_H
#define CLIENTE_H

#include <QObject>
#include <QtCore>
#include <QHostAddress>
#include <QtNetwork/QTcpSocket>
#include "servidor.h"
#include "paquete.h"
#include <QList>
#include <cstdio>
#include <ctime>


class Cliente : public QThread
{
Q_OBJECT
public:
    Cliente();
    ~Cliente();

    void run();
    void conectar(QString ip, quint16 puerto);
    void colocar_total_paquetes(int total);
    int obtener_total_paquetes();
    bool timeout_alcanzado(double tiempo_paquete, std::clock_t ahora);

signals:
  void salude_cliente();

public slots:
  void enviar();

private:
  QTcpSocket cliente;
  Servidor *servidor_cliente;
  QList<paquete> * cola_de_paquetes;
  int total_paquetes;
  int tamano_ventana;
  QString archivo;
  int puerto_intemediario;
  bool modo;
  int timeout;
};

#endif // CLIENTE_H
