package info_module;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class InfoClient {

	private Socket socket;
	private ObjectOutputStream out;
	private ObjectInputStream in;
	private String message;
	private int clientPort = 2000;
	private String clientHost = "localhost";
	
	private ExecutorService executor = Executors.newFixedThreadPool(1);
	
	public InfoClient() {
		executor.execute(new Runnable() {
			@Override
			public void run() {
				try {
					// 1. creating a socket to connect to the server
					socket = new Socket(clientHost, clientPort);
					System.out.println("Connected to " + clientHost + " in port " + clientPort);
					// 2. get Input and Output streams
					out = new ObjectOutputStream(socket.getOutputStream());
					out.flush();
					in = new ObjectInputStream(socket.getInputStream());
					// 3: Communicating with the server
					do {
						try {
							message = (String) in.readObject();
							System.out.println(message);
						} catch (ClassNotFoundException classNot) {
							System.err.println("data received in unknown format");
						}
					} while (!Thread.interrupted());
				} catch (UnknownHostException unknownHost) {
					System.err.println("You are trying to connect to an unknown host!");
				} catch (IOException ioException) {
					ioException.printStackTrace();
				} finally {
					// 4: Closing connection
					try {
						in.close();
						out.close();
						socket.close();
					} catch (IOException ioException) {
						ioException.printStackTrace();
					}
				}
			}
		});
	}

	void sendMessage(String msg) {
		try {
			out.writeObject(msg);
			out.flush();
		} catch (IOException ioException) {
			ioException.printStackTrace();
		}
	}

	public static void main(String args[]) {
		new InfoClient();
	}
}
