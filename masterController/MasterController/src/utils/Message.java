package utils;

public class Message {

	private String ip;
	// Si esta en true es porque esta ocupada
	private Boolean[] places;
	
	public String getPlacesString() {
		StringBuilder str = new StringBuilder();
		for(int i = 0; i < places.length; i++) {
			str.append("Place " + i + ": ");
			if(places[i]) {
				str.append("is occupied");
			} else {
				str.append("is not occupied");
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
