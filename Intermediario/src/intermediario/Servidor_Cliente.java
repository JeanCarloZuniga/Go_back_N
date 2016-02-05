/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package intermediario;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import javax.swing.JTextArea;

/**
 *
 * @author andre
 */
public class Servidor_Cliente extends Thread{
    
    private JTextArea textArea;
    private double probabilidad;
    private ServerSocket socket;
    private int puertoInterServidor;
    private boolean normal;
    private ArrayList secuencia;
    
    public Servidor_Cliente(boolean normal,ArrayList secuencia,JTextArea textArea, double probabilidad, int puertoClienteInter, int puertoInterServidor) throws IOException
    {
        this.textArea = textArea;
        this.probabilidad = probabilidad;
        this.puertoInterServidor = puertoInterServidor;
        socket = new ServerSocket(puertoClienteInter);
        this.normal = normal;
        this.secuencia = secuencia;
    }
    
    @Override
    public void run()
    {
        System.out.println("Inicia el Servidor_Cliente");
         
        String paquete = "";

        Socket coneccion;
        BufferedReader input;
        DataOutputStream output;
        
        int rango;
        probabilidad = probabilidad * 10;
        
        Socket socketCliente;
        
        if(normal)
        {
            try
           {
               while(paquete.compareTo("~") != 0)
               {
                   coneccion =  socket.accept();

                  input = new BufferedReader(new InputStreamReader(coneccion.getInputStream())); 

                  paquete = input.readLine();
                  System.out.println("Recibido: "+paquete);


                  /**Se convierte en cliente para enviar los datos al Cliente Principal**/
                  rango = (int)(Math.random()*10); //Si la probabilidad es 0.5 => 5 y si el random está entre 0 y 5 se pierde el paquete

                  if(rango > probabilidad)
                  {
                    // System.out.println("Voy del cliente al servidor y estoy en el intermediario");
                       socketCliente = new Socket("localhost", puertoInterServidor);
                       output = new DataOutputStream(socketCliente.getOutputStream());
                       output.writeBytes(paquete);
                       socketCliente.close();
                  }
                  else
                  {
                      textArea.append("\nSe perdió el paquete "+paquete);
                  }
               }


           }
           catch(Exception e)
           {
               System.err.println("Error al recibir los paquetes");
           }   
        }
        else
        {
            try
            {
                while(paquete.compareTo("~") != 0)
                {
                    coneccion =  socket.accept();

                   input = new BufferedReader(new InputStreamReader(coneccion.getInputStream())); 

                   paquete = input.readLine();
                   System.out.println("Recibido: "+paquete);


                   /**Se convierte en cliente para enviar los datos al Cliente Principal**/                  

                   if(!secuencia.contains(paquete))
                   {
                        socketCliente = new Socket("localhost", puertoInterServidor);
                        output = new DataOutputStream(socketCliente.getOutputStream());
                        output.writeBytes(paquete);
                        socketCliente.close();
                   }
                   else
                   {
                       textArea.append("\nSe perdió el paquete "+paquete);
                   }
                }

            }
            catch(Exception e)
            {
                System.err.println("Error al recibir los paquetes");
            }
        }
                
    }
}
