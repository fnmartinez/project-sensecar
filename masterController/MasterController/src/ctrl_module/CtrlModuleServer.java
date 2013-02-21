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
	private int ctrlPort;
	private int bufferSize;
	private CtrlModuleClient ctrlModuleclient;
	
	private BlockingQueue<String> messages;
	
	private ExecutorService socketExecutor = Executors.newCachedThreadPool();
	
	private CtrlUtils ctrlUtils;
	
	public CtrlModuleServer(CtrlModuleClient ctrlModuleclient, int ctrlPort, int bufferSize) {
		this.ctrlPort = ctrlPort;
		this.bufferSize = bufferSize;
		this.messages = new LinkedBlockingQueue<String>();
		this.ctrlModuleclient = ctrlModuleclient;
		ctrlModuleclient.setCtrlModuleServer(this);
		this.ctrlUtils = new CtrlUtils(ctrlModuleclient);
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
					sendMessage("");
					do {
						byte[] a = new byte[bufferSize];
						int size = in.read(a);
						String cmd;
						if (size > 0) {
							cmd = ctrlUtils.getCommandToSend(a,size);
							if(cmd.equalsIgnoreCase(ctrlUtils.getBadCommandErrorMessage())) {
								sendMessage(cmd);
							} else if(cmd.equalsIgnoreCase(Commands.HELP.name())) {
								sendMessage(ctrlUtils.help());
							} else if(cmd.equalsIgnoreCase(Commands.SELECT_DEVICE.name())) {
								sendMessage(ctrlUtils.getDeviceSelectedOkMessage()); 
							} else {
								ctrlModuleclient.addMessage(cmd);
								String message = messages.take();
								sendMessage(message.toString());
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
			out.write("> ".getBytes());
			out.flush();
		} catch (IOException ioException) {
			ioException.printStackTrace();
		}
	}
}
