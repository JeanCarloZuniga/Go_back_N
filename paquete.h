#ifndef PAQUETE_H
#define PAQUETE_H

#include <cstdio>
#include <ctime>

class paquete
{
public:
    paquete(int _secuencia, char _valor, std::clock_t _reloj, bool _abierto);
    void comenzar_timer();
    void abrir_canal();
    void cerrar_canal();
    int obtener_secuencia() const;
    char obtener_valor() const;
    std::clock_t obtener_reloj() const;
    bool esta_abierto() const;
    bool ack_recibido() const;
    void colocar_ack_recibido();

private:
    int secuencia;
    char valor;
    double reloj;
    bool abierto;
    bool recibido;
};

#endif // PAQUETE_H
