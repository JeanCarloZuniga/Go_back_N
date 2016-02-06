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
import java.util.regex.Pattern;
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
    private ArrayList<String> secuencia;
    
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
        
        if(normal)
        {
            modoNormal();
        }
        else
        {
          modoDebug();   
        }
                
    }
    
    private void modoNormal()
    {
        String paquete = "";
        
        Socket coneccion;
        BufferedReader input;
        DataOutputStream output;
        Socket socketCliente;
        
        int rango;
        probabilidad = probabilidad * 10;
        
        try
           {
               while(paquete.compareTo("-1:~") != 0)
               {
                   coneccion =  socket.accept();

                  input = new BufferedReader(new InputStreamReader(coneccion.getInputStream())); 

                  paquete = input.readLine();
                  System.out.println("Recibido: "+paquete);


                  /**Se convierte en cliente para enviar los datos al Cliente Principal**/
                  rango = (int)(Math.random()*10); //Si la probabilidad es 0.5 => 5 y si el random está entre 0 y 5 se pierde el paquete

                  if((rango >= probabilidad) || (paquete.compareTo("-1:~") != 0))
                  {
                       socketCliente = new Socket("localhost", puertoInterServidor);
                       output = new DataOutputStream(socketCliente.getOutputStream());
                       output.writeBytes(paquete);
                       socketCliente.close();
                  }
                  else
                  {
                      pintar(paquete);
                  }
               }


           }
           catch(Exception e)
           {
               System.err.println("Error al recibir los paquetes");
           }   
    }
    
    private void modoDebug()
    {
       
        String paquete = "";
        
        Socket coneccion;
        BufferedReader input;
        DataOutputStream output;
        Socket socketCliente;
        
        int rango;
        probabilidad = probabilidad * 10;
        
        try
            {
                while(paquete.compareTo("~") != 0)
                {
                    coneccion =  socket.accept();

                   input = new BufferedReader(new InputStreamReader(coneccion.getInputStream())); 

                   paquete = input.readLine();
                   System.out.println("Recibido: "+paquete);


                   /**Se convierte en cliente para enviar los datos al Cliente Principal**/                  
                   
                   if(!buscar(paquete) || (paquete.compareTo("-1:~") != 0))
                  {
                        socketCliente = new Socket("localhost", puertoInterServidor);
                        output = new DataOutputStream(socketCliente.getOutputStream());
                        output.writeBytes(paquete);
                        socketCliente.close();
                  }
                 else
                 {
                    pintar(paquete);
                 }
                }

            }
            catch(Exception e)
            {
                System.err.println("Error al recibir los paquetes");
            }
        
    }
    
    private boolean buscar(String paquete)
    {
        boolean encontrado = false;
        int length = secuencia.size();
        
        for(int i = 0; (i < length) && !encontrado; ++i)
        {
            System.out.println(secuencia.get(i)+", "+paquete);
            if(Pattern.matches(secuencia.get(i), paquete))
            {
                encontrado = true;
                secuencia.remove(i);
            }
        }
        
        return encontrado;
    }
    
    private void pintar(String paquete)
    {
        textArea.append("\nSe perdió el paquete "+paquete);
    }
}
