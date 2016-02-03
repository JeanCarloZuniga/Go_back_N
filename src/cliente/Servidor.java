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
/**
 *
 * @author jean
 */
public class Servidor extends Thread {
    LinkedList<String> cola_de_lecturas = new LinkedList<String>();
    public void imprimir(){
        System.out.println("Me llamaron desde el run");
    }
    
    public void run(){
        try {
            String clientSentence;
            //String capitalizedSentence;
            ServerSocket welcomeSocket = new ServerSocket(6789);
            
            while(true){
                Socket connectionSocket = welcomeSocket.accept();
                BufferedReader inFromClient =
                        new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
                //  DataOutputStream outToClient =
                //          new DataOutputStream(connectionSocket.getOutputStream());
                clientSentence = inFromClient.readLine();
                if(clientSentence != null){
                    System.out.println("Received: " + clientSentence);
                    cola_de_lecturas.addLast(clientSentence);
                }
                // capitalizedSentence = clientSentence.toUpperCase() + '\n';
                // outToClient.writeBytes(capitalizedSentence);
            }
        } catch (IOException ex) {
            Logger.getLogger(Servidor.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
