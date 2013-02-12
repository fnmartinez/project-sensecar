package info_module;

import java.io.IOException;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;

public class InfoModuleServer implements Runnable {

	private ServerSocket socket;
	private Socket connection = null;
	private OutputStream out;
	// private InputStream in;
	private int infoPort = 8088;

	private BlockingQueue<String> messages;
	private ExecutorService socketExecutor = Executors.newCachedThreadPool();

	public InfoModuleServer() {
		this.messages = new LinkedBlockingQueue<String>();
	}

	private void newSocket(final Socket connection) {
		socketExecutor.execute(new Runnable() {
			@Override
			public void run() {
				do {
					try {
						String msg = messages.take();
						sendMessage(msg);
					} catch (InterruptedException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				} while (socket.isBound() && !socket.isClosed()
						&& !Thread.interrupted());
			}
		});
	}

	void sendMessage(String msg) {
		try {
			out.write(msg.getBytes());
			// out.flush();
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

	@Override
	public void run() {
		try {
			// 1. creating a server socket
			socket = new ServerSocket(infoPort);
			// 2. Wait for connection
			System.out.println("Waiting for info connection on port "
					+ infoPort);
			do {
				connection = socket.accept();
				System.out.println("Connection received from "
						+ connection.getInetAddress().getHostName());
				out = connection.getOutputStream();
				newSocket(connection);
			} while (!Thread.interrupted());
		} catch (IOException ioException) {
			ioException.printStackTrace();
		} finally {
			// 4: Closing connection
			try {
				// in.close();
				out.close();
				socket.close();
			} catch (IOException ioException) {
				ioException.printStackTrace();
			}
		}
	}
}
