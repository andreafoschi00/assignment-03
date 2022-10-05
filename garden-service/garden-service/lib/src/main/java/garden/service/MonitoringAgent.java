package garden.service;

import SerialCommChannel.SerialCommChannel;

public class MonitoringAgent extends Thread {
	
	private final SerialCommChannel channel;
	private final GUI view;
	private final LogView logger;

	

	public MonitoringAgent(SerialCommChannel channel, GUI view, LogView logger) {
		this.channel = channel;
		this.view = view;
		this.logger = logger;
	}
	
	
}
