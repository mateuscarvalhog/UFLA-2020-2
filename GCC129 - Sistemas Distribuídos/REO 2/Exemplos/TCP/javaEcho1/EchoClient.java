import java.io.*;
import java.net.*;

public class EchoClient {
    public static void main(String[] args) throws IOException {

        String serverHostname = new String ("18.224.220.128");
		int porta = 3000;

		System.out.println ("Attemping to connect to host " + serverHostname + " on port " + porta + ".");

        Socket echoSocket = null;
        PrintWriter out = null;
        BufferedReader in = null;

        try {
            echoSocket = new Socket(serverHostname, porta );

			out = new PrintWriter(echoSocket.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(echoSocket.getInputStream()));

				} catch (UnknownHostException e) {
            System.err.println("Don't know about host: " + serverHostname);
            System.exit(1);
        } catch(IOException e) {
            System.err.println("Couldn't get I/O for "
                               + "the connection to: " + serverHostname);
            System.exit(1);
        }

	    BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));

		String userInput;

        System.out.print ("input: ");

	    while ((userInput = stdIn.readLine()) != null) {
	        out.println(userInput);
	        System.out.println("echo: " + in.readLine());
            System.out.print("input: ");
	    }

        out.close();
        in.close();
        stdIn.close();
        echoSocket.close();
    }
}
