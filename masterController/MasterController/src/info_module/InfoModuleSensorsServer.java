package info_module;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

public class InfoModuleSensorsServer implements Runnable {

	private DatagramSocket socket;
	private int infoPort = 2002;
	private byte[] buf;
	private DatagramPacket packet;
	private InfoModuleServer infoServer;
	private int bufferSize = 256;

	public InfoModuleSensorsServer(InfoModuleServer infoModuleServer) {
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
				for (int i = 0; i < data.length && (data[i] != '\n' && data[i+1] != '\r'); i++) {
					str.append((char) data[i]);
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
