package ctrl_module;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

public class CtrlModuleClient implements Runnable {
	private Socket serverSocket;
	private OutputStream out;
	private InputStream in;
	private int serverPort = 8888;
	private String serverIp = null;
	private CtrlModuleServer ctrlModuleServer; // Seteado desde CtrlModuleServer
	private int bufferSize = 256;
	
	private BlockingQueue<String> messages;
	
	public CtrlModuleClient() {
		this.messages = new LinkedBlockingQueue<String>();
	}

	@Override
	public void run() {
		do {
			try {
				do {
					byte[] buf = new byte[bufferSize];
					System.out.println("Trying to send commands to " + serverIp + " on port " + serverPort);
					String message = messages.take();
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
						ctrlModuleServer.addMessage(cmd.toString());
					}
					serverSocket.close();
				} while (!Thread.interrupted());
			} catch (IOException | InterruptedException ioException) {
				System.out.println("FATAL: Server with ip " + serverIp + " at port " + serverPort + " not found\n");
//				ioException.printStackTrace();
			} finally {
				try {
					if(in != null) {
						in.close();
					}
					if(out != null) {
						out.close();
					}
					if(serverSocket != null) {
						serverSocket.close();
					}
				} catch (IOException ioException) {
//					ioException.printStackTrace();
				}
			}
		} while(!Thread.interrupted());
	}

	void sendMessage(String msg) {
		try {
			out.write(msg.getBytes());
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
	
	public void setCtrlModuleServer(CtrlModuleServer ctrlModuleServer) {
		this.ctrlModuleServer = ctrlModuleServer;
	}
	
	public void setServerIp(String serverIp) {
		this.serverIp = serverIp;
		System.out.println("Trying to send commands to " + serverIp + " on port " + serverPort);
	}
	
	public String getServerIp() {
		return this.serverIp;
	}
}
