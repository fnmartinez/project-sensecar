package sense_module;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;

public class SenseModule {

	
//	public static void main(String[] args) {
//		MainModule mainModule = new MainModule();
//		
//		Boolean[] places = new Boolean[4];
//		places[0] = true;
//		places[1] = true;
//		places[2] = false;
//		places[3] = true;
//		Message m1 = new Message("1.1.1.1", places);
//		mainModule.addMessage(m1);
//	}
	
	
	private ServerSocket socket;
	private Socket connection = null;
	private ObjectOutputStream out;
	private InputStream in;
	private int infoPort = 8088;
	
	private BlockingQueue<String> messages;
	private ExecutorService executor = Executors.newFixedThreadPool(1);
	
	public SenseModule() {
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
					in = connection.getInputStream();
					byte[] a = new byte[500];
					// 4. The two parts communicate via the input and output streams
					sendMessage("Connection successful");
					do {
						int size = in.read(a);
						if(size > 0) {
							System.out.println(size);
							for(int i = 0; i < size; i++) {
								System.out.print((char)a[i]);
							}
							System.out.println();
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
		new SenseModule();
	}
}
