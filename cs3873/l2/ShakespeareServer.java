/**
 * I warrant that this is my own work.
 * Jacob Smith (3534295)
 */ 

import java.net.*;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.DataOutputStream;
import java.io.IOException;

public class ShakespeareServer {
  private static int PORT = 6789;

  /**
   * The goal of this method is to open up a server socket, accept incoming connections, read in a Shakespeare poem 
   * line by line and then to restart when finished.
   */
  public static void main(String[] args) throws Exception {
    System.out.println("Creating a server at localhost:" + ShakespeareServer.PORT);
    ServerSocket socket = new ServerSocket(ShakespeareServer.PORT);

		try {
      while (true) {
        System.out.println ("Waiting for connection...");
        Socket connection = socket.accept();
        System.out.println ("Connection successful!\n");

        BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        DataOutputStream out = new DataOutputStream(connection.getOutputStream());

        String line;
        while ((line = in.readLine()) != null) {
          if (line.equals("Done")) {
            System.out.println("\nClient has finished sending the poem.");
            System.out.println("Sending \"Bye\" :)");
            out.writeBytes("Bye\n");
            break;
          }

          System.out.println(line);
        }

        out.close();
        in.close();
        connection.close();
      }
    } catch(IOException e) {
      System.out.println("Unknown error: " + e);
    } finally {
      socket.close();
    }
  }
}