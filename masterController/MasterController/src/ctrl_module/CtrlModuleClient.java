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
	private int serverPort;
	private String serverIp;
	private CtrlModuleServer ctrlModuleServer; // Seteado desde CtrlModuleServer
	private int bufferSize;
	
	private BlockingQueue<String> messages;
	
	
	public CtrlModuleClient(String serverIp, int serverPort, int bufferSize) {
		this.messages = new LinkedBlockingQueue<String>();
		this.serverIp = serverIp;
		this.serverPort = serverPort;
		this.bufferSize = bufferSize;
	}

	@Override
	public void run() {
		do {
			try {
				do {
					byte[] buf = new byte[bufferSize];
					System.out.println("Trying to send commands to " + serverIp + " on port " + serverPort);
					String message = messages.take();
					//TODO: si la ip no es accesible, no intentar conectar
//					InetAddress inet = InetAddress.getByName("192.168.1.108");
//					System.out.println("REACHABLE: " + inet.isReachable(5000));
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
				System.out.println("ERROR: Device with ip " + serverIp + " at port " + serverPort + " not found\n");
				ctrlModuleServer.addMessage(" Device with ip " + serverIp + " at port " + serverPort + " not found\n");
				ioException.printStackTrace();
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
					ioException.printStackTrace();
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
