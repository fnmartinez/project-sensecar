package info_module;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

public class InfoModuleControllersServer implements Runnable {

	private DatagramSocket socket;
	private int infoPort;
	private byte[] buf;
	private DatagramPacket packet;
	private InfoModuleServer infoServer;
	private int bufferSize;
	

	public InfoModuleControllersServer(InfoModuleServer infoModuleServer, int infoPort, int bufferSize) {
		this.infoPort = infoPort;
		this.bufferSize = bufferSize;
		this.infoServer = infoModuleServer;
		try {
			socket = new DatagramSocket(infoPort);
		} catch (SocketException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public void run() {
		StringBuilder str;
		try {
			System.out.println("Waiting for info packets on port " + infoPort);
			do {
				str = new StringBuilder();
				buf = new byte[bufferSize];
				packet = new DatagramPacket(buf, buf.length);
				socket.receive(packet);
				byte[] data = packet.getData();
				int quantity = ((char)data[0]) - 48;
				System.out.println("quantity: " + (char)data[0]);
				System.out.println("byte[0] = " + (char)data[0]);
				System.out.println("byte[1] = " + (char)data[1]);
				System.out.println("byte[2] = " + (char)data[2]);
//				System.out.println("byte[3] = " + data[3]);
				str.append("Data from:");
				str.append(packet.getAddress());
				str.append("\n");
				for (int i = 0; i<quantity && i < data.length && data[i] != '\n' && data[i+1] != '\r'; i++) {
					str.append("Sensor ");
					str.append(i+1);
					str.append(" state is: ");
					str.append((char)data[i+1]);
					str.append("\n");
				}
				str.append("\r\n");
				System.out.println(str.toString());
				String message = str.toString();
				infoServer.addMessage(message.toString());
			} while (!Thread.interrupted());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
