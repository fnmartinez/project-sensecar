package sense_module;

import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;

public class SenseModule {

	private ServerSocket socket;
	private Socket connection = null;
	private ObjectOutputStream out;
	private InputStream in;
	private int sensePort = 8088;

	private BlockingQueue<String> messages;
	private ExecutorService executor = Executors.newFixedThreadPool(1);
	private ExecutorService socketExecutor = Executors.newCachedThreadPool();

	public SenseModule() {
		this.messages = new LinkedBlockingQueue<String>();
		executor.execute(new Runnable() {
			@Override
			public void run() {
				try {
					// 1. creating a server socket
					socket = new ServerSocket(sensePort);
					do {
						// 2. Wait for connection
						System.out.println("Waiting for connection");
						connection = socket.accept();
						System.out.println("Connection received from " + connection.getInetAddress().getHostName());
						newSocket(connection);
					} while (!Thread.interrupted());
				} catch (IOException ioException) {
					ioException.printStackTrace();
				} finally {
					// 4: Closing connection
					try {
						in.close();
						// out.close();
						socket.close();
					} catch (IOException ioException) {
						ioException.printStackTrace();
					}
				}
			}
		});
	}
	
	private void newSocket(final Socket connection) {
		socketExecutor.execute(new Runnable() {
			@Override
			public void run() {
				try {
					out = new ObjectOutputStream(connection.getOutputStream());
					in = connection.getInputStream();
					sendMessage("Connection successful FROM PC");
					do {
						// 3. get Input and Output streams
						byte[] a = new byte[1000];
						// 4. The two parts communicate via the input and output
						// streams
						int size = in.read(a);
						if (size > 0) {
							System.out.println("Received size" + size);
							for (int i = 0; i < size; i++) {
								System.out.print((char) a[i]);
							}
							System.out.println();
							System.out.flush();
						}
	//					in.close();
					} while (!socket.isClosed() && socket.isBound());
					socket.close();
				} catch (IOException ioException) {
					ioException.printStackTrace();
				}
			}
		});
	}

	private void sendMessage(String msg) {
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
