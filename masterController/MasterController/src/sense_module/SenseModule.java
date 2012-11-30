package sense_module;

import main_module.MainModule;
import utils.Message;

public class SenseModule {

	
	public static void main(String[] args) {
		MainModule mainModule = new MainModule();
		
		Boolean[] places = new Boolean[4];
		places[0] = true;
		places[1] = true;
		places[2] = false;
		places[3] = true;
		Message m1 = new Message("1.1.1.1", places);
		mainModule.addMessage(m1);
	}
}
