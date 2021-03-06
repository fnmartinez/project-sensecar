package ctrl_module;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class CtrlClient {

	private Socket socket;
	private ObjectOutputStream out;
	private ObjectInputStream in;
	private String message;
	
	private ExecutorService executor = Executors.newFixedThreadPool(1);
	
	public CtrlClient() {
		executor.execute(new Runnable() {
			@Override
			public void run() {
				try {
					// 1. creating a socket to connect to the server
					socket = new Socket("localhost", 2004);
					System.out.println("Connected to localhost in port 2004");
					// 2. get Input and Output streams
					out = new ObjectOutputStream(socket.getOutputStream());
					out.flush();
					in = new ObjectInputStream(socket.getInputStream());
					// 3: Communicating with the server
					do {
						try {
							message = (String) in.readObject();
							System.out.println("server>" + message);
							sendMessage("Hi my server");
							message = "bye";
							sendMessage(message);
						} catch (ClassNotFoundException classNot) {
							System.err.println("data received in unknown format");
						}
					} while (!message.equals("bye"));
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
			System.out.println("client>" + msg);
		} catch (IOException ioException) {
			ioException.printStackTrace();
		}
	}

	public static void main(String args[]) {
		new CtrlClient();
	}
}
