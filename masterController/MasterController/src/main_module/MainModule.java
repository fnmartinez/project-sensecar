package main_module;

import info_module.InfoModuleControllersServer;
import info_module.InfoModuleServer;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import utils.Utils;

import ctrl_module.CtrlModuleClient;
import ctrl_module.CtrlModuleServer;

public class MainModule {

	public static void main(String[] args) {
		ExecutorService executor = Executors.newFixedThreadPool(4);
		
		Utils utils = new Utils();
		
		int bufferSize = utils.getBufferSize();
		
		InfoModuleServer infoModuleServer = new InfoModuleServer(utils.getInfoPort());
		InfoModuleControllersServer infoModule = new InfoModuleControllersServer(infoModuleServer, utils.getControllerInfoPort(), bufferSize);
		CtrlModuleClient ctrlModuleClient = new CtrlModuleClient(utils.getServerIp(), utils.getServerPort(), bufferSize);
		CtrlModuleServer ctrlModuleServer = new CtrlModuleServer(ctrlModuleClient, utils.getCtrlPort(), bufferSize);
		
		executor.execute(infoModuleServer);
		executor.execute(infoModule);
		executor.execute(ctrlModuleClient);
		executor.execute(ctrlModuleServer);
	}
}
