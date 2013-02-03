package main_module;

import info_module.InfoModule;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;

import ctrl_module.CtrlModule;

import utils.Message;

public class MainModule {

	private BlockingQueue<Message> messages;
	private ExecutorService executor = Executors.newFixedThreadPool(1);
	private CtrlModule ctrlModule = new CtrlModule();
	private InfoModule infoModule = new InfoModule();
	
	public MainModule() {
		this.messages = new LinkedBlockingQueue<>();
		executor.execute(new Runnable() {
			@Override
			public void run() {
				while(!Thread.interrupted()) {
					try {
						Message message = messages.take();
						String info = buildMessage(message);
						infoModule.addMessage(info);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					
					
				}
			}
		});
	}
	
	private String buildMessage(Message message) {
		StringBuilder builder = new StringBuilder();
		builder.append("--------------------------------------------------------------------------------\n");
		builder.append("From: " + message.getFrom() + " To: " + message.getTo() + "\n");
		builder.append(message.getPlacesString());
		builder.append("--------------------------------------------------------------------------------\n");
		return builder.toString();
	}
	
	public void addMessage(Message message) {
		try {
			this.messages.put(message);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public Message getMessage() {
		Message message = null;
		try {
			message = this.messages.take();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return message;
	}
	
//	public static void main(String[] args) {
//		while(true) {
//			MainModule mainModule = new MainModule();
//			Message message = mainModule.getMessage();
//		}
//		
//	}
//	public static void main(String[] args) {
//		InfoModule info = new InfoModule();
//		info.addMessage("hola");
//	}
}
