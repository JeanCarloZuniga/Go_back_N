#ifndef CLIENTE_H
#define CLIENTE_H

#include <QObject>
#include <QtCore>
#include <QHostAddress>
#include <QtNetwork/QTcpSocket>
#include "servidor.h"
#include "paquete.h"
#include <vector>
#include <cstdio>
#include <ctime>

class Cliente : public QThread
{
Q_OBJECT
public:
    Cliente(int _rol);
    ~Cliente();

    void run();
    void conectar(QString ip, quint16 puerto);
    bool timeout_alcanzado(double tiempo_paquete, std::clock_t ahora);
    void enlistar_paquetes();
    void ensamblar_paquete(int indice);

signals:
  void salude_cliente();

public slots:
  void enviar();

private:
  Qt::HANDLE id;
  QTcpSocket cliente;
  Servidor *servidor_cliente;
  std::vector<paquete*> cola_de_paquetes;
  int total_paquetes;
  int tamano_ventana;
  QString archivo;
  int puerto_intemediario;
  bool modo;
  int timeout;
  int rol;
  QString paquete_a_enviar;
};

#endif // CLIENTE_H
