package main_module;

import info_module.InfoModuleSensorsServer;
import info_module.InfoModuleServer;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import ctrl_module.CtrlModuleClient;
import ctrl_module.CtrlModuleServer;

public class MainModule {

	public static void main(String[] args) {
		ExecutorService executor = Executors.newFixedThreadPool(4);
		
		InfoModuleServer infoModuleServer = new InfoModuleServer();
		InfoModuleSensorsServer infoModule = new InfoModuleSensorsServer(infoModuleServer);
		CtrlModuleClient ctrlModuleClient = new CtrlModuleClient();
		CtrlModuleServer ctrlModuleServer = new CtrlModuleServer(ctrlModuleClient);
		
		executor.execute(infoModuleServer);
		executor.execute(infoModule);
		executor.execute(ctrlModuleClient);
		executor.execute(ctrlModuleServer);
	}
}
