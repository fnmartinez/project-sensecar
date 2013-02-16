package ctrl_module;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

import utils.Commands;

public class CtrlUtils {
	
	private CtrlModuleClient ctrlModuleClient;
	
	private String badCommandErrorMessage = "-Err Bad command\r\n";
	private String deviceSelectedOkMessage = "+OK device selected\r\n";
	
	public CtrlUtils(CtrlModuleClient ctrlModuleClient) {
		this.ctrlModuleClient = ctrlModuleClient;
	}
	
	private static final String PATTERN = 
	        "^([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\." +
	        "([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\." +
	        "([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\." +
	        "([01]?\\d\\d?|2[0-4]\\d|25[0-5])$";

	private String getCommandSplitted(byte[] commandBytes, int size) {
		StringBuilder cmd = new StringBuilder();
		for (int i = 0; i < size; i++) {
			cmd.append((char) commandBytes[i]); 
		}
		return cmd.toString().trim();
	}
	
	public String getCommandToSend(byte[] commandBytes, int size) {
		String cmd = getCommandSplitted(commandBytes, size);
		String[] command = cmd.split(" ");
		
		if(ctrlModuleClient.getServerIp() == null && !command[0].equalsIgnoreCase(Commands.SELECT_DEVICE.name())
				&& !command[0].equalsIgnoreCase(Commands.HELP.name())) {
			return badCommandErrorMessage;
		}
		
		if(command[0].equalsIgnoreCase(Commands.SELECT_DEVICE.name())) {
			if(validateIp(command[1])) {
				ctrlModuleClient.setServerIp(command[1]);
				return Commands.SELECT_DEVICE.name();
			}
		} else if(command[0].equalsIgnoreCase(Commands.TURN_ON.name())) {
			return command[0] + "\n\r";
		} else if(command[0].equalsIgnoreCase(Commands.TURN_OFF.name())) {
			return command[0] + "\n\r";
		} else if(command[0].equalsIgnoreCase(Commands.EXIT.name())) {
			return command[0] + "\n\r";
		} else if(command[0].equalsIgnoreCase(Commands.SET_NETWORK_INFO.name())) {
			if(validateIp(command[1]) && validateIp(command[2]) && validateIp(command[3])) {
				return command[0] + " " + command[1] + " " + command[2] + " " + command[3] + "\n\r";
			}
		} else if(command[0].equalsIgnoreCase(Commands.SET_PORT.name())) {
			if(validatePort(command[1])) {
				return command[0] + " " + command[1] + "\n\r";
			}
		} else if(command[0].equalsIgnoreCase(Commands.SET_SERVER_IP.name())) {
			if(validateIp(command[1])) {
				return command[0] + " " + command[1] + "\n\r";
			}
		} else if(command[0].equalsIgnoreCase(Commands.SET_SERVER_PORT.name())) {
			if(validatePort(command[1])) {
				return command[0] + " " + command[1] + "\n\r";
			}
		} else if(command[0].equalsIgnoreCase(Commands.SENSOR_ON.name())) {
			if(validateSensorNumber(command[1])) {
				return command[0] + " " + command[1] + "\n\r";
			}
		} else if(command[0].equalsIgnoreCase(Commands.SENSOR_OFF.name())) {
			if(validateSensorNumber(command[1])) {
				return command[0] + " " + command[1] + "\n\r";
			}
		} else if(command[0].equalsIgnoreCase(Commands.GET_STATUS.name())) {
			return command[0] + "\n\r";
		} else if(command[0].equalsIgnoreCase(Commands.INFORM_STATUS.name())) {
			return command[0] + "\n\r";
		} else if(command[0].equalsIgnoreCase(Commands.HELP.name())) {
			return Commands.HELP.name();
		} else {
			return badCommandErrorMessage;
		}
		
		return badCommandErrorMessage;
	}

	public String getBadCommandErrorMessage() {
		return badCommandErrorMessage;
	}
	
	public String getDeviceSelectedOkMessage() {
		return deviceSelectedOkMessage;
	}

	public String help() {
		StringBuilder strBuilder = new StringBuilder();
		strBuilder.append("These are the available commands: \n\n");
		strBuilder.append(Commands.SELECT_DEVICE.name() + " <device_ip>\t\t\t Selects the device to send the commands (WARNING: You must use this command to " +
				"select a device before using any other command)\n");
		strBuilder.append(Commands.TURN_ON.name() + "\t\t\t\t\t\t Turns on the selected device\n");
		strBuilder.append(Commands.TURN_OFF.name() + "\t\t\t\t\t Turns off the selected device\n");
		strBuilder.append(Commands.EXIT.name() + "\t\t\t\t\t\t Turns on the selected device\n");
		strBuilder.append(Commands.SET_NETWORK_INFO.name() + " <ip> <netmask> <gateway>\t Sets the network information of the selected device\n");
		strBuilder.append(Commands.SET_PORT.name() + " <portNumber>\t\t\t\t Sets the port used by the selected device to receive the commands\n");
		strBuilder.append(Commands.SET_SERVER_IP.name() + " <ip>\t\t\t\t Sets the ip used by the selected device to send the sensors information (Ip of the information server)\n");
		strBuilder.append(Commands.SET_SERVER_PORT.name() + " <port>\t\t\t\t Sets the port used by the selected device to send the sensors information (Port of the information server)\n");
		strBuilder.append(Commands.SENSOR_ON.name() + " <sensorNumber>\t\t\t Turns on a specific sensor in the selected device\n");
		strBuilder.append(Commands.SENSOR_OFF.name() + " <sensorNumber>\t\t\t Turns off a specific sensor in the selected device\n");
		strBuilder.append(Commands.GET_STATUS.name() + "\t\t\t\t\t Returns the sensor status of the selected device\n");
		strBuilder.append(Commands.INFORM_STATUS.name() + "\t\t\t\t\t Makes the selected device to send the sensors information to the information server\n");
		strBuilder.append('\n');
		return strBuilder.toString();
	}
	
	public boolean validateIp(String ip) {
		Pattern pattern = Pattern.compile(PATTERN);
		Matcher matcher = pattern.matcher(ip);
		return matcher.matches() || ip.equals("localhost");  
	}
	
	public boolean validatePort(String port) {
		int portNumber;
		try {
			portNumber = Integer.valueOf(port);
		} catch (Exception e) {
			return false;
		}
		if(portNumber < 1024 || portNumber > 49151) {
			return false;
		}
		return true;
	}
	
	public boolean validateSensorNumber(String sensor) {
		try {
			Integer.valueOf(sensor);
		} catch (Exception e) {
			return false;
		}
		return true;
	}
	
}
