

package servidor;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;


/**
 *
 * @author andre
 */
public class Interfaz extends javax.swing.JFrame {

    private int puerto;
    private int puertoEnvio;
    private String linea;
    private String lineaSalida;
    private ServerSocket socket;
    private List<Integer> lista_secuencia;
    private List<String> lista_caracteres;
    private File archivo;
    private FileWriter escritor;
    private BufferedWriter buffer;
    

    
    /**
     * Creates new form Interfaz
     */
    public Interfaz() {
        initComponents();
        this.radio_normal.setSelected(true);
        this.radio_group.add(this.radio_normal);
        this.radio_group.add(this.radio_debug);
        

       
       lista_secuencia = new ArrayList();
       lista_secuencia.add(-1);
       lista_caracteres = new ArrayList();
      
    }

    
    private void crearArchivo()
    {
        try
        {
            archivo = new File("Mensaje.txt");
       
            if(!archivo.exists())
            {
                archivo.createNewFile();
            }
            
            escritor = new FileWriter(archivo.getName(), true); //El booleano es para que haga un append en vez de un write
            buffer = new BufferedWriter(escritor);
            
            
        }
        catch(Exception e)
        {
            System.err.println("Error fatal al abrir el archivo!!");
        }
    }
    
    public void escucharNormal() throws IOException 
    {
        try
        {
            linea = "";
            while(linea.compareTo("-1:~") != 0)
            {
                Socket coneccion =  socket.accept();

               BufferedReader input = new BufferedReader(
                       new InputStreamReader(coneccion.getInputStream())); 

               linea = input.readLine();
               System.out.println("Recibido: "+linea);

               if(validarPaquete(linea)) //Enviamos el ACK
               {
                   System.out.println("Validado!");
                   enviar(""+(lista_secuencia.get(lista_secuencia.size()-1)));
                   System.out.println("Enviando un ack de: " + lista_secuencia.get(lista_secuencia.size()-1));                                      
               }
            }
            
          
        }
        catch(Exception e)
        {
            System.err.println("Error en el método Escuchar");
        }
      
      buffer.close();  //Cerramos el buffer reader cuando terminamos de escuchar
      this.textArea.append("Se recibió el archivo completo");
    }
    

    
    public void escucharDebug() throws IOException 
    {
        try
        {
            linea = "";
            while(linea.compareTo("-1:~") != 0)
            {
                Socket coneccion =  socket.accept();

               BufferedReader input = new BufferedReader(
                       new InputStreamReader(coneccion.getInputStream())); 

               linea = input.readLine();
               
               this.textArea.append("Recibido: "+linea+"\n");
               
               this.textArea.update(this.textArea.getGraphics()); //Actualizamos la interfaz
               
               if(validarPaquete(linea)) //Enviamos el ACK
               {
                   enviar(""+(lista_secuencia.get(+lista_secuencia.size()-1)));                   
                   linea = "";
               }
            }
            
          
        }
        catch(Exception e)
        {
            System.err.println("Error en el método Escuchar");
        }
      
      buffer.close();  //Cerramos el buffer reader cuando terminamos de escuchar
    }
    
    public boolean validarPaquete(String paquete) throws IOException
    {
        
        boolean valido = false;
        String nuevo_paquete[];
        int ultimo;
        int nuevo;
        
        
        nuevo_paquete = paquete.split(":",2);
        nuevo = Integer.parseInt(nuevo_paquete[0]);
        ultimo = lista_secuencia.get(lista_secuencia.size()-1);
        
        if(ultimo == nuevo) //Esto es para cuando se pierde un ack
        {
            return true;
        }

        if(ultimo == (nuevo-1))
        {
            valido = true;
            lista_secuencia.add(nuevo);
            lista_caracteres.add(nuevo_paquete[1]);
            buffer.write(lista_caracteres.get(lista_caracteres.size()-1)); //Si el paquete era el esperado, se escribe el caracter
        }
        
        
        /**
        ultimo = lista_secuencia.get(lista_secuencia.size()-1);
        if(Pattern.matches(""+ultimo+":.", paquete))
        {
            return true;
        }
        
        if(Pattern.matches(""+(ultimo+1)+":.", paquete))
        {
            nuevo_paquete = paquete.split(":",2);
            nuevo = Integer.parseInt(nuevo_paquete[0]);
            lista_secuencia.add(nuevo);
            lista_caracteres.add(nuevo_paquete[1]);
            valido = true;
        }
**/
         
        return valido;
    }
    
    
    
    public void enviar(String ack) {
        try {
            Socket clientSocket = new Socket("localhost", puertoEnvio);
            DataOutputStream outToServer
                    = new DataOutputStream(clientSocket.getOutputStream());
            outToServer.writeBytes(ack);
            clientSocket.close();
        } catch (IOException ex) {
            System.err.println("Error al enviar el ack");
        }
    }
    
    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        radio_group = new javax.swing.ButtonGroup();
        jScrollPane1 = new javax.swing.JScrollPane();
        textArea = new javax.swing.JTextArea();
        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        puerto_text = new javax.swing.JTextField();
        jLabel3 = new javax.swing.JLabel();
        radio_normal = new javax.swing.JRadioButton();
        radio_debug = new javax.swing.JRadioButton();
        jButton1 = new javax.swing.JButton();
        jLabel4 = new javax.swing.JLabel();
        puerto_envio = new javax.swing.JTextField();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        textArea.setColumns(20);
        textArea.setRows(5);
        jScrollPane1.setViewportView(textArea);

        jLabel1.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
        jLabel1.setText("Servidor");

        jLabel2.setFont(new java.awt.Font("Tahoma", 1, 14)); // NOI18N
        jLabel2.setText("Puerto de escucha");

        puerto_text.setText("10003");

        jLabel3.setFont(new java.awt.Font("Tahoma", 1, 14)); // NOI18N
        jLabel3.setText("Modo");

        radio_normal.setText("Normal");

        radio_debug.setText("Debug");

        jButton1.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
        jButton1.setText("Listo");
        jButton1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jButton1ActionPerformed(evt);
            }
        });

        jLabel4.setFont(new java.awt.Font("Tahoma", 1, 14)); // NOI18N
        jLabel4.setText("Puerto de envío");

        puerto_envio.setText("10002");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(24, 24, 24)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jLabel2)
                        .addGap(50, 50, 50)
                        .addComponent(puerto_text))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jLabel1)
                        .addGap(0, 0, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jLabel4)
                            .addComponent(jLabel3)
                            .addGroup(layout.createSequentialGroup()
                                .addGap(78, 78, 78)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                    .addComponent(radio_normal)
                                    .addComponent(jButton1))))
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addGap(68, 68, 68)
                                .addComponent(puerto_envio, javax.swing.GroupLayout.DEFAULT_SIZE, 59, Short.MAX_VALUE))
                            .addGroup(layout.createSequentialGroup()
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(radio_debug)
                                .addGap(0, 0, Short.MAX_VALUE)))))
                .addGap(10, 10, 10)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 351, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jLabel1)
                        .addGap(37, 37, 37)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(jLabel2)
                            .addComponent(puerto_text, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(27, 27, 27)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(jLabel4)
                            .addComponent(puerto_envio, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(58, 58, 58)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(jLabel3)
                            .addComponent(radio_normal)
                            .addComponent(radio_debug))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 124, Short.MAX_VALUE)
                        .addComponent(jButton1))
                    .addComponent(jScrollPane1))
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void jButton1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jButton1ActionPerformed
        try
        {
            this.puerto = Integer.parseInt(this.puerto_text.getText());
            this.puertoEnvio = Integer.parseInt(this.puerto_envio.getText());
        }
        catch(Exception e)
        {
            System.err.println("Error fatal al tratar de parsear la entrada. Verifique los datos que escribió e intentelo de nuevo");
        }
        
        try
        {
            socket = new ServerSocket(puerto);  
            crearArchivo();
            if(this.radio_debug.isSelected())
            {
              escucharDebug();
            }
            else
            {
              escucharNormal();
            } 
        }
        catch(Exception e)
        {
            System.err.println("Error fatal al tratar de crear el socket");
        }

       
    }//GEN-LAST:event_jButton1ActionPerformed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(Interfaz.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(Interfaz.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(Interfaz.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Interfaz.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new Interfaz().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jButton1;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JTextField puerto_envio;
    private javax.swing.JTextField puerto_text;
    private javax.swing.JRadioButton radio_debug;
    private javax.swing.ButtonGroup radio_group;
    private javax.swing.JRadioButton radio_normal;
    private javax.swing.JTextArea textArea;
    // End of variables declaration//GEN-END:variables
}
