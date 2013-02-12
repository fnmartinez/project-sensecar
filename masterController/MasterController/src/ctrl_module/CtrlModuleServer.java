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

public class CtrlModuleServer implements Runnable {
	private ServerSocket socket;
	private OutputStream out;
	private InputStream in;
	private int ctrlPort = 2001;
	private int bufferSize = 256;
	private CtrlModuleClient ctrlModuleclient;
	private String badCommandErrorMessage = "-Err Bad command\r\n";
	
	private BlockingQueue<String> messages;
	
	private ExecutorService socketExecutor = Executors.newCachedThreadPool();
	
	public CtrlModuleServer(CtrlModuleClient ctrlModuleclient) {
		this.messages = new LinkedBlockingQueue<String>();
		this.ctrlModuleclient = ctrlModuleclient;
		ctrlModuleclient.setCtrlModuleServer(this);
	}

	@Override
	public void run() {
		Socket connection = null;
		try {
			socket = new ServerSocket(ctrlPort);
			do {
				System.out.println("Waiting to receive commands on port " + ctrlPort);
				connection = socket.accept();
				System.out.println("Connection received from "
						+ connection.getInetAddress().getHostName());
				newSocket(connection);
			} while (!Thread.interrupted());
		} catch (IOException ioException) {
			ioException.printStackTrace();
		} finally {
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
					do {
						byte[] a = new byte[bufferSize];
						int size = in.read(a);
						String cmd;
						if (size > 0) {
							cmd = newCommand(a,size);
							if(!cmd.equals(badCommandErrorMessage)) {
//								ctrlModuleclient.addMessage(cmd);
								String message = messages.take();
								sendMessage(message.toString());
							} else {
								sendMessage(cmd);
							}
						}
					} while (!socket.isClosed() && socket.isBound());
				} catch (IOException | InterruptedException ioException) {
					ioException.printStackTrace();
				} finally {
					try {
						if(in != null) {
							in.close();
						}
						if(out != null) {
							out.close();
						}
						if(socket != null) {
							socket.close();
						}
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			}
		});
	}
	
	private String getCommandSplitted(byte[] commandBytes, int size) {
		StringBuilder cmd = new StringBuilder();
		for (int i = 0; i < size; i++) {
			cmd.append((char) commandBytes[i]); 
		}
		return cmd.toString().trim();
	}
	
	//TODO falta validar los comandos
	private String newCommand(byte[] commandBytes, int size) {
		String cmd = getCommandSplitted(commandBytes, size);
		String[] command = cmd.split(" ");
		
		if(command[0].equalsIgnoreCase(Commands.SELECT_DEVICE.name())) {
			ctrlModuleclient.setServerIp(command[1] + '\n');
		} else if(command[0].equalsIgnoreCase(Commands.TURN_ON.name())) {
			ctrlModuleclient.addMessage(command[0] + '\n');
		} else if(command[0].equalsIgnoreCase(Commands.TURN_OFF.name())) {
			ctrlModuleclient.addMessage(command[0] + '\n');
		} else if(command[0].equalsIgnoreCase(Commands.EXIT.name())) {
			ctrlModuleclient.addMessage(command[0] + '\n');
		} else if(command[0].equalsIgnoreCase(Commands.SET_NETWORK_INFO.name())) {
			ctrlModuleclient.addMessage(command[0] + " " + command[1] + " " + command[2] + " " + command[3] + '\n');
		} else if(command[0].equalsIgnoreCase(Commands.SET_PORT.name())) {
			ctrlModuleclient.addMessage(command[0] + " " + command[1] + '\n');
		} else if(command[0].equalsIgnoreCase(Commands.SET_SERVER_IP.name())) {
			ctrlModuleclient.addMessage(command[0] + " " + command[1] + '\n');
		} else if(command[0].equalsIgnoreCase(Commands.SET_SERVER_PORT.name())) {
			ctrlModuleclient.addMessage(command[0] + " " + command[1] + '\n');
		} else if(command[0].equalsIgnoreCase(Commands.SENSOR_ON.name())) {
			ctrlModuleclient.addMessage(command[0] + " " + command[1] + '\n');
		} else if(command[0].equalsIgnoreCase(Commands.SENSOR_OFF.name())) {
			ctrlModuleclient.addMessage(command[0] + " " + command[1] + '\n');
		} else if(command[0].equalsIgnoreCase(Commands.GET_STATUS.name())) {
			ctrlModuleclient.addMessage(command[0] + '\n');
		} else if(command[0].equalsIgnoreCase(Commands.INFORM_STATUS.name())) {
			ctrlModuleclient.addMessage(command[0] + '\n');
		} else {
			return badCommandErrorMessage;
		}
		return cmd;
	}
	
	public void addMessage(String message) {
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
}
