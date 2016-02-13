/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cliente;

/**
 *
 * @author jean
 */

/*
Estructura que llevan los paquetes.
*/
public class Paquete {
    int secuencia;
    char valor;
    long reloj;
    long reloj_inicial;
    int reenvios;
    Paquete(int _secuencia, char _valor, long _reloj){
        this.reenvios=0;
        this.reloj_inicial=0;
    }
    
}
