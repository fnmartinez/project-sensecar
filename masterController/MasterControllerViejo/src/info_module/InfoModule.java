package info_module;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;

import utils.Message;

public class InfoModule {

	private ServerSocket socket;
	private Socket connection = null;
	private ObjectOutputStream out;
	private ObjectInputStream in;
	private int infoPort = 8088;
	
	private BlockingQueue<String> messages;
	private ExecutorService executor = Executors.newFixedThreadPool(1);
	
	public InfoModule() {
		this.messages = new LinkedBlockingQueue<String>();
		executor.execute(new Runnable() {
			@Override
			public void run() {
				try {
					// 1. creating a server socket
					socket = new ServerSocket(infoPort);
					// 2. Wait for connection
					System.out.println("Waiting for connection");
					connection = socket.accept();
					System.out.println("Connection received from "
							+ connection.getInetAddress().getHostName());
					// 3. get Input and Output streams
					out = new ObjectOutputStream(connection.getOutputStream());
					out.flush();
					in = new ObjectInputStream(connection.getInputStream());
					sendMessage("Connection successful");
					// 4. The two parts communicate via the input and output streams
					do {
						try {
							String msg = messages.take();
							sendMessage(msg);
						} catch (InterruptedException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						}
					} while (!Thread.interrupted());
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
	
	public void addMessage(String message) {
		try {
			this.messages.put(message);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public static void main(String args[]) {
		new InfoModule();
	}
}
