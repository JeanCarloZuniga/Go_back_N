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
import javax.swing.JFrame;
import javax.swing.JTextArea;

/**
 *
 * @author jean
 */
public class Cliente extends Thread {
    /*
    Constructor para el cliente, recibe un JTextArea para pintar en la interfaz
    */
    public Cliente(JTextArea outputTB){
        this.outputTB = outputTB;
    }
    JTextArea outputTB;
    LinkedList<Paquete> cola_de_paquetes = new LinkedList<Paquete>();
    LinkedList<String> resultados = new LinkedList<String>();
    int tamano_ventana, puerto_intemediario, puerto_cliente;
    long total_tiempo_ejecucion = 0;
    long tiempo_inicial, tiempo_final, timeout;
    String archivo, paquete_a_enviar, nombre_archivo;
    Boolean modo;

    /*
    Verifica si se alcanza el timeout para el primer paquete enviado en el contexto
    */
    public Boolean timeout_alcanzado(long tiempo_paquete, long ahora) {
        long duracion = (ahora - tiempo_paquete);
        return duracion >= timeout;
    }
    
    /*
    Imprime si esta en modo debug, no imprime en caso contrario
    */
    public void imprimir(String a_imprimir){
        if(modo){
            this.outputTB.append(a_imprimir);
        }
    }
    
    /*
    Toma cada caracter del archivo a enviar y le pone un ID representarivo,
    luego lo encola en la lista de paquetes
    */
    public void enlistar_paquetes() {
        for (int i = 0; i < archivo.length(); i++) {
            Paquete nuevo_paquete = new Paquete(-1, '0', System.currentTimeMillis());
            nuevo_paquete.secuencia = i;
            nuevo_paquete.valor = archivo.charAt(i);
            imprimir("Encolando: " + nuevo_paquete.secuencia + ":" + nuevo_paquete.valor + "\n");
            cola_de_paquetes.addLast(nuevo_paquete);
        }
    }

    /*
    Se encarga de hacer el par secuencia:valor para enviarlo
    */
    public void ensamblar_paquete(int indice) {
        paquete_a_enviar = "";
        //Ensambla el paquete a enviar
        paquete_a_enviar = cola_de_paquetes.get(indice).secuencia
                + ":";
        paquete_a_enviar = paquete_a_enviar + cola_de_paquetes.get(indice).valor;
        cola_de_paquetes.get(indice).reloj = System.currentTimeMillis();
        if(cola_de_paquetes.get(indice).reenvios==0)
        {
            cola_de_paquetes.get(indice).reloj_inicial = cola_de_paquetes.get(indice).reloj;
        }
    }
    
    /*
    Envia un -1:~ para notificar que ya acabo de enviar los paquetes
    */
    public void enviar_ultimo_paquete(){
        paquete_a_enviar="-1:~";
        enviar();
    }

    /*
    envia un paquete
    */
    public void enviar() {
        try {
            Socket clientSocket = new Socket("localhost", puerto_intemediario);
            DataOutputStream outToServer
                    = new DataOutputStream(clientSocket.getOutputStream());
            outToServer.writeBytes(paquete_a_enviar + '\n');
            clientSocket.close();
        } catch (IOException ex) {
            Logger.getLogger(Cliente.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void guardar_dato(){
        Paquete dato = cola_de_paquetes.element();
        long tiempo_transcurrido = System.currentTimeMillis() - dato.reloj_inicial;
        resultados.addLast("Secuencia "+ Integer.toString(dato.secuencia) 
        + " -- Valor " + dato.valor
        + " -- Reenvios " + dato.reenvios
        + " -- Tiempo " 
        + Long.toString(tiempo_transcurrido)
        + "\n");
        total_tiempo_ejecucion+=(tiempo_transcurrido);
        //Pregunto si es el �ltimo paquete
        if(dato.secuencia == archivo.length()-1){
            tiempo_final = System.currentTimeMillis() - tiempo_inicial; 
        }
    }
    
    public void crear_documento(){
        try {
            File doc = new File("Informe.txt");

            FileWriter escribir = new FileWriter(doc, true);
            
            escribir.write("*---------  Informe para el archivo: " + nombre_archivo
                + " con un timeout de: " + timeout + " y una ventana de: " 
                + tamano_ventana + "  ---------*\n");
            
            while(!resultados.isEmpty())
            {
                escribir.write(resultados.pop());
            }
            escribir.write("\n\n**TOTAL TIEMPO TRANSCURRIDO: "
                    + Long.toString(tiempo_final)
                    + "\n**TOTAL RTT TRANSCURRIDO: "
                    + Long.toString(total_tiempo_ejecucion)
                    + "\n\n-------fin del informe-------\n\n");
            escribir.close();
        } 
        catch (Exception e) {
            System.out.println("Error al escribir");
        }
    }

    /*
    Metodo principal para el go back n
    */
    @Override
    public void run() {
        Servidor servidor = new Servidor(puerto_cliente);
        servidor.start();
        this.outputTB.append("[Cliente] : El cliente está corriendo ahora.\n");
        int tope_a_enviar=tamano_ventana;
        enlistar_paquetes();
        //Envia los primeros "tamaño ventana" paquetes
        if (!cola_de_paquetes.isEmpty()) {
            //Caso en el que la ventana sea más grande que el archivo a enviar.
            if (tamano_ventana > archivo.length()) {
                tope_a_enviar = archivo.length();
            }
            for (int i = 0; i < tope_a_enviar; i++) {
                ensamblar_paquete(i);
                if(i==0){
                    tiempo_inicial=cola_de_paquetes.element().reloj_inicial;
                }
                imprimir("Enviando: " + paquete_a_enviar + "\n");
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
                imprimir("Se venció el timeout\n");
                for(int i=0; i<tope_a_enviar; i++) 
                {
                    cola_de_paquetes.get(i).reenvios+=1;
                    ensamblar_paquete(i);
                    imprimir("Reenviando: " + paquete_a_enviar + "\n");
                    enviar();
                }
            //si se recibió el ACK
            } else {
                while(!servidor.cola_de_lecturas.isEmpty())
                {
                    String ack_leido = servidor.cola_de_lecturas.pop();

                    while ((!cola_de_paquetes.isEmpty()) 
                            && (Integer.parseInt(ack_leido) >= cola_de_paquetes.element().secuencia)){
                        imprimir("\n>>> Llego el ack: " + cola_de_paquetes.element().secuencia + "<<<\n\n");
                        //Para efectos del informe
                        guardar_dato();
                        cola_de_paquetes.pop();
                        //Si aun quedan paquetes, deslizo la ventana
                        if (!cola_de_paquetes.isEmpty()) {
                            if (cola_de_paquetes.size() < tamano_ventana) {
                                tope_a_enviar = cola_de_paquetes.size();
                            } else {
                                ensamblar_paquete(tamano_ventana - 1);
                                imprimir("Enviando: " + paquete_a_enviar + "\n");
                                enviar();
                            }
                        } 
                    }
                }
            }
        }
        enviar_ultimo_paquete();
        this.outputTB.append("\n Archivo enviado \n");
        crear_documento();
    }
}
