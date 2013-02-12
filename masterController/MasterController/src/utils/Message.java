package utils;

public class Message {

	private String from;
	private String to;
	// Si esta en true es porque esta ocupada
	private String message;
	
	public Message(String from, String to, String message) {
		this.from = from;
		this.to = to;
		this.message = message;
	}
	
	public String getFrom() {
		return this.from;
	}
	
	public String getTo() {
		return this.to;
	}
	
	public String getMessage() {
		return this.message;
	}
	
	@Override
	public String toString() {
		StringBuilder str = new StringBuilder();
		str.append("Message from: ");
		str.append(this.from);
		str.append(" to: ");
		str.append(this.to);
		str.append("\n Message says: ");
		str.append(this.message);
		return str.toString();
	}
}
