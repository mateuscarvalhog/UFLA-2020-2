import java.net.*; 
import java.io.*; 

public class UploadServer extends Thread
{ 
 protected Socket clientSocket;
 public static final int PORTA = 2000;

 public static void main(String[] args) throws IOException 
   { 
    ServerSocket serverSocket = null;

    try { 
         serverSocket = new ServerSocket(PORTA); 
         System.out.println ("Connection Socket Created");
         try { 
              while (true)
                 {
                  System.out.println ("Waiting for Connection");
                  new UploadServer (serverSocket.accept()); 
                 }
             } 
         catch (IOException e) 
             { 
              System.err.println("Accept failed."); 
              System.exit(1); 
             } 
        } 
    catch (IOException e) 
        { 
         System.err.println("Could not listen on port: "+ PORTA); 
         System.exit(1); 
        } 
    finally
        {
         try {
              serverSocket.close(); 
             }
         catch (IOException e)
             { 
              System.err.println("Could not close port: "+ PORTA); 
              System.exit(1); 
             } 
        }
   }

 private UploadServer (Socket clientSoc)
   {
    clientSocket = clientSoc;
    start();
   }

 public void run()
   {
    System.out.println ("New Communication Thread Started");

    try { 
         PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("file.txt")));
         PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true); 
         BufferedReader in = new BufferedReader(new InputStreamReader( clientSocket.getInputStream())); 

         String inputLine; 

         while ((inputLine = in.readLine()) != null) { 
              fout.println(inputLine); 
         } 

         out.close(); 
         in.close();
         fout.close();
         clientSocket.close(); 
			
        } 
    catch (IOException e) 
        { 
         System.err.println("Problem with Communication Server");
         System.exit(1); 
        } 
    }
} 
