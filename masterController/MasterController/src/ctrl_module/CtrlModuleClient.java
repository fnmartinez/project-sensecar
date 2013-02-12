package ctrl_module;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

import utils.Message;

public class CtrlModuleClient implements Runnable {
	private Socket serverSocket;
	private OutputStream out;
	private InputStream in;
	private int serverPort = 8888;
	private String serverIp = "127.0.0.1";
	private CtrlModuleServer ctrlModuleServer; // Seteado desde CtrlModuleServer
	private int bufferSize = 256;
	
	private BlockingQueue<Message> messages;
	
	public CtrlModuleClient() {
		this.messages = new LinkedBlockingQueue<Message>();
	}

	@Override
	public void run() {
		try {
			do {
				byte[] buf = new byte[bufferSize];
				System.out.println("Trying to send commands to " + serverIp + " on port " + serverPort);
				Message message = messages.take();
				serverSocket = new Socket(serverIp, serverPort);
				out = serverSocket.getOutputStream();
				in = serverSocket.getInputStream();
				sendMessage(message.toString());
				int size = in.read(buf);
				StringBuilder cmd = new StringBuilder();
				if(size > 0) {
					for (int i = 0; i < size; i++) {
						cmd.append((char) buf[i]); 
					}
					ctrlModuleServer.addMessage(new Message("", "", cmd.toString()));
				}
				serverSocket.close();
			} while (!Thread.interrupted());
		} catch (IOException | InterruptedException ioException) {
			ioException.printStackTrace();
		} finally {
			// 4: Closing connection
			try {
				in.close();
				out.close();
				serverSocket.close();
			} catch (IOException ioException) {
				ioException.printStackTrace();
			}
		}
	}

	void sendMessage(String msg) {
		try {
			out.write(msg.getBytes());
			out.flush();
		} catch (IOException ioException) {
			ioException.printStackTrace();
		}
	}
	
	public void addMessage(Message message) {
		try {
			this.messages.put(message);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void setCtrlModuleServer(CtrlModuleServer ctrlModuleServer) {
		this.ctrlModuleServer = ctrlModuleServer;
	}
	
	//Main de prueba
//	public static void main(String[] args) {
//		Executor e = Executors.newFixedThreadPool(1);
//		e.execute(new CtrlModule());
//	}
}
