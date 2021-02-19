import java.io.*;
import java.net.*;

public class UploadClient {
    public static void main(String[] args) throws IOException {

        String serverHostname = new String ("127.0.0.1");
        int porta = 2000;

              System.out.println ("Attemping to connect to host " +
                serverHostname + " on port "+ porta);

        Socket echoSocket = null;
        PrintWriter out = null;
        BufferedReader in = null;

        try {
            echoSocket = new Socket(serverHostname, porta);
            out = new PrintWriter(echoSocket.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(
                                        echoSocket.getInputStream()));
        } catch (UnknownHostException e) {
            System.err.println("Don't know about host: " + serverHostname);
            System.exit(1);
        } catch (IOException e) {
            System.err.println("Couldn't get I/O for "
                               + "the connection to: " + serverHostname);
            System.exit(1);
        }

	      BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
	      
	    System.out.println ("Informe o nome do arquivo:");

	        String fileName = stdIn.readLine();
	        
	      BufferedReader fin = new BufferedReader(new FileReader(fileName));
	      
	      
	      String line; 

              while ((line = fin.readLine()) != null) {
	          out.println(line);
	          System.out.println(line);
	      }

	      out.close();
	      in.close();
	      stdIn.close();
	      echoSocket.close();
    }
}

