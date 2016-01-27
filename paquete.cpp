#include "paquete.h"

paquete::paquete(int _secuencia, char _valor, std::clock_t _reloj, bool _abierto)
{
    secuencia = _secuencia;
    valor = _valor;
    reloj = _reloj;
    abierto = _abierto;
    recibido = false;
}

void paquete::comenzar_timer()
{
    reloj = std::clock();
}

void paquete::abrir_canal()
{
    abierto=true;
}

void paquete::cerrar_canal()
{
    abierto=false;
}

int paquete::obtener_secuencia()
{
    return secuencia;
}

char paquete::obtener_valor()
{
    return valor;
}

clock_t paquete::obtener_reloj()
{
    return reloj;
}

bool paquete::esta_abierto()
{
    return abierto;
}

bool paquete::ack_recibido()
{
    return recibido;
}

void paquete::colocar_ack_recibido()
{
    recibido = true;
}


