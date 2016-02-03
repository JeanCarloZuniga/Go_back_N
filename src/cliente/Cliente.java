/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cliente;

import java.util.*;
import java.io.*;
import java.net.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.lang.*;

/**
 *
 * @author jean
 */
public class Cliente {

    Servidor servidor = new Servidor();
    LinkedList<Paquete> cola_de_paquetes = new LinkedList<Paquete>();
    int tamano_ventana = 3;
    String archivo = "Melissa";
    int puerto_intemediario;
    Boolean modo;
    long timeout = 1000;
    String paquete_a_enviar;

    public Boolean timeout_alcanzado(long tiempo_paquete, long ahora) {
        long duracion = (ahora - tiempo_paquete);
        return duracion >= timeout;
    }

    public void enlistar_paquetes() {
        for (int i = 0; i < archivo.length(); i++) {
            Paquete nuevo_paquete = new Paquete(-1, '0', System.currentTimeMillis());
            nuevo_paquete.secuencia = i;
            nuevo_paquete.valor = archivo.charAt(i);
            System.out.println("Encolando: " + nuevo_paquete.secuencia + ":" + nuevo_paquete.valor);
            cola_de_paquetes.addLast(nuevo_paquete);
        }
    }

    public void ensamblar_paquete(int indice) {
        paquete_a_enviar = "";
        //Ensambla el paquete a enviar
        paquete_a_enviar = cola_de_paquetes.get(indice).secuencia
                + ":";
        paquete_a_enviar = paquete_a_enviar + cola_de_paquetes.get(indice).valor;
        cola_de_paquetes.get(indice).reloj = System.currentTimeMillis();
    }

    public void enviar() {
        try {
            Socket clientSocket = new Socket("localhost", 6789);
            DataOutputStream outToServer
                    = new DataOutputStream(clientSocket.getOutputStream());
            outToServer.writeBytes(paquete_a_enviar + '\n');
            clientSocket.close();
        } catch (IOException ex) {
            Logger.getLogger(Cliente.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public void iniciar() {
        servidor.start();
//
        System.out.println("[Cliente] : El cliente está corriendo ahora.");
        int tope_a_enviar=tamano_ventana;
        //Espera hasta que haya un archivo a enviar
        while (archivo.isEmpty()) {
            //Esperando a que el usuario seleccione un archivo con la interfaz
        }
        enlistar_paquetes();
        //Envia los primeros "tamaño ventana" paquetes
        if (!cola_de_paquetes.isEmpty()) {
            int tope_de_primer_envio = tamano_ventana;
            //Caso en el que la ventana sea más grande que el archivo a enviar.
            if (tamano_ventana > archivo.length()) {
                tope_de_primer_envio = archivo.length();
            }
            for (int i = 0; i < tope_de_primer_envio; i++) {
                ensamblar_paquete(i);
                enviar();
            }
        }
        //Ciclo principal que se encarga de enviar todos los paquetes
        while (!cola_de_paquetes.isEmpty()) {
            while(servidor.cola_de_lecturas.isEmpty()
                    && !timeout_alcanzado(cola_de_paquetes.element().reloj, System.currentTimeMillis()))
            {
                //El tiempo pasa
            }
            //si se venció el timeout
            if(servidor.cola_de_lecturas.isEmpty())
            {
                System.out.println("Se venció el timeout\n");
                for(int i=0; i<tope_a_enviar; i++) 
                {
                    ensamblar_paquete(i);
                    enviar();
                }
            //si se recibió el ACK
            } else {
                while(!servidor.cola_de_lecturas.isEmpty())
                {
                    String ack_leido = servidor.cola_de_lecturas.pop();
                    if(ack_leido.equals(Integer.toString(cola_de_paquetes.element().secuencia)))
                    {
                        System.out.println("Llego el ack: " + ack_leido);
                        cola_de_paquetes.pop();
                        //Si aun quedan paquetes, deslizo la ventana
                        if(!cola_de_paquetes.isEmpty())
                        {
                            if(cola_de_paquetes.size() < tamano_ventana)
                            {
                                tope_a_enviar=cola_de_paquetes.size();
                            } else {
                                ensamblar_paquete(tamano_ventana - 1);
                                enviar();
                            }
                        } 
                    }
                }
            }
        }
    }
}
