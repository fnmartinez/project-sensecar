package utils;

public enum State {
	FREE(0, "Free"), OCCUPIED(1, "Occupied"), OFF(2, "Off");
	
	int code;
	String description;
	
	State(int code, String description) {
		this.code = code;
		this.description = description;
	}
	
	public String getDescription() {
		return this.description;
	}
	
	public int getCode() {
		return this.code;
	}
	
//	0 es libre
//	1 es ocupado
//	2 es apagado
}
