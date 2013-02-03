package utils;

public class Message {

	private String from;
	private String to;
	// Si esta en true es porque esta ocupada
	private Boolean[] places;
	
	public Message(String from, String to, Boolean[] places) {
		this.from = from;
		this.to = to;
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
	
	public String getFrom() {
		return this.from;
	}
	
	public String getTo() {
		return this.to;
	}
	
	public Boolean[] getPlaces() {
		return this.places;
	}
}
