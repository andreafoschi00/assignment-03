package garden.service;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

import SerialCommChannel.SerialCommChannel;

public class Controller implements ActionListener {

	SerialCommChannel channel;
	GUI view;
	Random rnd = new Random();
	int temperature;
	int intensity;

	public Controller(String port, GUI view, LogView logger) throws Exception {
		this.view = view;
		channel = new SerialCommChannel(port, 9600);
		new MonitoringAgent(channel,view,logger).start();

		System.out.println("Waiting arduino for rebootin...");
		
		System.out.println("Ready");
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		try {
			temperature = rnd.nextInt(30);
			intensity = rnd.nextInt(100);
			channel.sendMsg(Integer.toString(intensity) + "," + Integer.toString(temperature));
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}



}
