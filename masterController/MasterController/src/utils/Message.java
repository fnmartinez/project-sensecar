package utils;

public class Message {

	private String ip;
	// Si esta en true es porque esta ocupada
	private Boolean[] places;
	
	public Message(String ip, Boolean[] places) {
		this.ip = ip;
		this.places = places;
	}
	
	public String getPlacesString() {
		StringBuilder str = new StringBuilder();
		for(int i = 0; i < places.length; i++) {
			str.append("Place " + i + ": ");
			if(places[i]) {
				str.append("occupied");
			} else {
				str.append("free");
			}
			str.append("\t");
		}
		str.append("\n");
		return str.toString();
	}
	
	public String getIp() {
		return ip;
	}
}
