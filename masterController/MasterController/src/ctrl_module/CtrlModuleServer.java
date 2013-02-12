package ctrl_module;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;

import utils.Commands;
import utils.Message;

public class CtrlModuleServer implements Runnable {
	private ServerSocket socket;
	private OutputStream out;
	private InputStream in;
	private int ctrlPort = 2001;
	private int bufferSize = 256;
	private CtrlModuleClient ctrlModuleclient;
	
	private BlockingQueue<Message> messages;
	
	private ExecutorService socketExecutor = Executors.newCachedThreadPool();
	
	public CtrlModuleServer(CtrlModuleClient ctrlModuleclient) {
		this.messages = new LinkedBlockingQueue<Message>();
		this.ctrlModuleclient = ctrlModuleclient;
		ctrlModuleclient.setCtrlModuleServer(this);
	}

	@Override
	public void run() {
		Socket connection = null;
		try {
			// 1. creating a server socket
			socket = new ServerSocket(ctrlPort);
			do {
				// 2. Wait for connection
				System.out.println("Waiting to receive commands on port " + ctrlPort);
				connection = socket.accept();
				System.out.println("Connection received from "
						+ connection.getInetAddress().getHostName());
				newSocket(connection);
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

	private void newSocket(final Socket connection) {
		socketExecutor.execute(new Runnable() {
			@Override
			public void run() {
				try {
					out = connection.getOutputStream();
					in = connection.getInputStream();
					sendMessage("Connection successful");
					do {
						// 3. get Input and Output streams
						byte[] a = new byte[bufferSize];
						// 4. The two parts communicate via the input and output
						// streams
						int size = in.read(a);
						String cmd;
						if (size > 0) {
							cmd = newCommand(a,size);
							ctrlModuleclient.addMessage(new Message("", "", cmd));
						}
						Message message = messages.take();
						sendMessage(message.toString());
					} while (!socket.isClosed() && socket.isBound());
				} catch (IOException | InterruptedException ioException) {
					ioException.printStackTrace();
				} finally {
					try {
						in.close();
						out.close();
						socket.close();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		});
	}
	
	private String newCommand(byte[] commandBytes, int size) {
		System.out.println("Received size" + size);
		StringBuilder cmd = new StringBuilder();
		for (int i = 0; i < size; i++) {
			cmd.append((char) commandBytes[i]); 
		}
		System.out.println(cmd);
		
		String command = cmd.toString().trim() + "\r\n";
		System.out.println("------------------------------------------");
		if(command.equalsIgnoreCase(Commands.TURN_ON.name() + "\r\n")) {
			System.out.println("RECIBI TURN ON");
		} else if(command.equalsIgnoreCase(Commands.TURN_OFF.name() + "\r\n")) {
			System.out.println("RECIBI TURN off");
		} else if(command.equalsIgnoreCase(Commands.SET_IP.name() + "\r\n")) {
			System.out.println("RECIBI set ip");
		} else if(command.equalsIgnoreCase(Commands.SET_PORT.name() + "\r\n")) {
			System.out.println("RECIBI SET PORT");
		} else if(command.equalsIgnoreCase(Commands.SET_SERVER_IP.name() + "\r\n")) {
			System.out.println("RECIBI SET SERVER IP");
		} else if(command.equalsIgnoreCase(Commands.SET_SERVER_PORT.name() + "\r\n")) {
			System.out.println("RECIBI SET SERVER PORT");
		} else if(command.equalsIgnoreCase(Commands.SENSOR_ON.name() + "\r\n")) {
			System.out.println("RECIBI SENSOR ON");
		} else if(command.equalsIgnoreCase(Commands.SENSOR_OFF.name() + "\r\n")) {
			System.out.println("RECIBI SENSOR OFF");
		} else {
			System.out.println("-ERR Bad command");
		}
		System.out.println("------------------------------------------");
		return cmd.toString();
	}
	
	public void addMessage(Message message) {
		try {
			this.messages.put(message);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
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
	
	//Main de prueba
//	public static void main(String[] args) {
//		Executor e = Executors.newFixedThreadPool(1);
//		e.execute(new CtrlModule());
//	}
}
