package utils;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Properties;

public class Utils {

	private static final String propertiesFolder = "resources/configuration.properties";
	
	private int bufferSize;
	private String serverIp;
	private int serverPort;
	private int ctrlPort;
	private int controllerInfoPort;
	private int infoPort;
	
	public Utils() {
		Properties properties = new Properties();
		
		try {
			properties.load(new FileInputStream(propertiesFolder));
		} catch (FileNotFoundException e) {
			System.out.println("ERROR: Configuration file not found");
			System.exit(0);
		} catch (IOException e) {
			System.out.println("ERROR: IOException");
			System.exit(0);
		}
		
		bufferSize = Integer.valueOf(properties.getProperty("bufferSize"));
		serverIp = properties.getProperty("serverIp");
		serverPort = Integer.valueOf(properties.getProperty("serverPort"));
		ctrlPort = Integer.valueOf(properties.getProperty("ctrlPort"));
		controllerInfoPort = Integer.valueOf(properties.getProperty("controllerInfoPort"));
		infoPort = Integer.valueOf(properties.getProperty("infoPort"));
	}

	public int getBufferSize() {
		return bufferSize;
	}

	public String getServerIp() {
		return serverIp;
	}

	public int getServerPort() {
		return serverPort;
	}

	public int getCtrlPort() {
		return ctrlPort;
	}

	public int getControllerInfoPort() {
		return controllerInfoPort;
	}

	public int getInfoPort() {
		return infoPort;
	}
	
}
