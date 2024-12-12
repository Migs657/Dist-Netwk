
//source for a lot of stuff
//https://www.geeksforgeeks.org/how-to-create-a-simple-tcp-client-server-connection-in-java/
//https://www.w3schools.com/java/java_methods.asp
//https://www.w3schools.com/java/java_threads.asp

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

//assume that they don't try creating two primary
public class DataServer extends Thread{

    //first argument is port and second(if it exists) is primaries port
    static boolean isPrime = true;
    static int parent = -1;
    static int storage = 0;
    static int mySocket = -1;
    static int[] backups = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    public static void main(String args[]) throws IOException {
        // put arg in eaiser place
        mySocket = Integer.parseInt(args[0]);

        //set up thread
        DataServer thread = new DataServer();
        

        //for hard coded testing for debugger
        //mySocket = 5000;

        //System.out.println(args[0]);
        if (args.length == 2) {
            isPrime = false;
            parent = Integer.parseInt(args[1]);
            System.out.println("I am a backup with port: " + mySocket);
            System.out.println("Primary port: " + parent);
        } else if (args.length < 2) {
            System.out.println("I am primary!");
        }

        
        //create a server socket on port number args[0]
        

        //if back send join
        if (!isPrime) {
            oneTimeCommunicate(parent, "JOIN:" + mySocket);
        }

        
        // Accept incoming client/backup connection
        while (true) {
            ServerSocket serverSocket = new ServerSocket(mySocket);
            System.out.println("Data Server is listening on port " + mySocket);
            Socket clientSocket = serverSocket.accept();
            System.out.println("Client connected!");

            //create thread here


            // Setup input and output streams for communication with the client/backup
            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);

            // Read message from client/backup
            String message = in.readLine();
            System.out.println("Client says: " + message);
            String[] inputVariables = message.split(":");
            if ("READ".equals(message)) {
                System.out.println("COMPLETE_READ:" + storage);
                // Send response to the client
                out.println("COMPLETE_READ:" + storage);
            } //has more more than 1 input variable
            else if (inputVariables.length == 2) {
                // Declare a string with comma delimiter
                // Split the string using comma as the delimiter
                
                //System.out.println(inputVariables[0]);
                //System.out.println(inputVariables[1]);
                if ("WRITE".equals(inputVariables[0])) {
                    if (isPrime) {
                        storage = Integer.parseInt(inputVariables[1]);
                        //update others
                        updateBackups();
                        out.println("COMPLETE_WRITE");
                    } 
                    else {
                        //send update request to primary
                        oneTimeCommunicate(parent, "UPDATE:" + inputVariables[1]);
                        //respond to client after
                        out.println("COMPLETE_WRITE");
                    }
                } 
                //Prime gests message
                else if ("JOIN".equals(inputVariables[0]) && !(inputVariables[1].equals(String.valueOf(mySocket)))) {
                    //System.out.println("JOIN recieve");
                    joinToPrime(Integer.parseInt(inputVariables[1]));
                    out.println("COMPLETE_JOIN");
                    //updateBackups();
                } //response for join
                else if ("JOIN".equals(inputVariables[0]) && inputVariables[1].equals(String.valueOf(mySocket))) {
                    System.out.println("Got response: COMPLETE_JOIN");
                    System.out.println("Data Server is listening on port " + mySocket);
                }
                else if ("UPDATE".equals(inputVariables[0])){
                    if(isPrime){
                        storage = Integer.parseInt(inputVariables[1]);
                        out.println("COMPLETE_UPDATE");
                        updateBackups();
                    }
                    else{
                        storage = Integer.parseInt(inputVariables[1]);
                        out.println("UPDATE_COMPLETE");
                    }
                }   
            }
            // Close the client socket
            serverSocket.close();
            clientSocket.close();
        }

    }

    public static void oneTimeCommunicate(int port, String message) {
        Socket socket = null;
        try {
            socket = new Socket("localhost", port);

            InputStream input = socket.getInputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(input));
            OutputStream output = socket.getOutputStream();
            PrintWriter writer = new PrintWriter(output, true);

            //send message
            writer.println(message);

            System.out.println("Just send out: " + message + " to port: " + port);

            //get response
            String line = reader.readLine();


            System.out.println("Got response: " + line);

            //close the socket
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    static void joinToPrime(int backup) {
        int i = 0;
        //System.out.println(backup);
        while (backups[i] != -1) {
            i++;
        }

        backups[i] = backup;
        //oneTimeCommunicate(backup, message);
    }

    static void updateBackups() {
        int i = 0;
        //System.out.println(backup);
        while (backups[i] != -1) {
            oneTimeCommunicate(backups[i], "UPDATE:" + storage);
            i++;
        }
    }

    public void run(){
        
    }
}
