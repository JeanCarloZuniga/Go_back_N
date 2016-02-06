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
import javax.swing.JTextArea;

/**
 *
 * @author andre
 */
public class Servidor_Servidor extends Thread{
    
    private ServerSocket socket;
    
    private int puertoInterCliente;
    private double probabilidad;
    private JTextArea textArea;
    
    public Servidor_Servidor(boolean normal, JTextArea textArea, int puertoServidorInter, int puertoInterCliente, double probabilidad) throws IOException
    {
        socket = new ServerSocket(puertoServidorInter);
        this.puertoInterCliente = puertoInterCliente;
        this.probabilidad = probabilidad;
        this.textArea = textArea;
    }
    
    @Override
    public void run()
    {
        System.out.println("Inicia el Servidor_Servidor");
        String paquete;
        Socket coneccion;
        BufferedReader input;
        DataOutputStream output;
        
        Socket socketCliente;
        
        int rango;
        probabilidad = probabilidad * 10;
       
        try
        {
            while(true)
            {
               coneccion =  socket.accept();

               input = new BufferedReader(new InputStreamReader(coneccion.getInputStream())); 

               paquete = input.readLine();
               System.out.println("Recibido: "+paquete);
               
               /**Se convierte en cliente para enviar los datos al Cliente Principal**/
               rango = (int)(Math.random()*10); //Si la probabilidad es 0.5 => 5 y si el random está entre 0 y 5 se pierde el paquete
               if(rango >= probabilidad)
               {
                   System.out.println("Voy del servidor al cliente y estoy en el intermediario "+paquete);
                    socketCliente = new Socket("localhost", puertoInterCliente);
                    output = new DataOutputStream(socketCliente.getOutputStream());
                    output.writeBytes(paquete);
                    socketCliente.close();
               }
               else
               {
                   this.textArea.append("\nSe perdió el ACK: "+paquete);
               }                
            }
            
          
        }
        catch(Exception e)
        {
            System.err.println("Error al recibir los paquetes");
        }        
    }
    
    
}
