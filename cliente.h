#ifndef CLIENTE_H
#define CLIENTE_H

#include <QObject>
#include <QtCore>
#include <QHostAddress>
#include <QtNetwork/QTcpSocket>


class Cliente : public QThread
{
Q_OBJECT
public:
    Cliente();
    ~Cliente();

    void run();
    void conectar(QString ip, quint16 puerto);

signals:
  void salude_cliente();

public slots:
  void enviar();

private:
  QTcpSocket cliente;
};

#endif // CLIENTE_H
