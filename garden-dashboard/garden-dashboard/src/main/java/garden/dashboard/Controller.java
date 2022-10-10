package garden.dashboard;

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
		channel = new SerialCommChannel(port, 115200);
		new MonitoringAgent(channel,view,logger).start();

		System.out.println("Waiting arduino for rebootin...");

		System.out.println("Ready");
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		try {
			temperature = rnd.nextInt(31);
			intensity = rnd.nextInt(8);
			System.out.println(temperature + " " + intensity);
			channel.sendMsg(Integer.toString(temperature) + "," + Integer.toString(intensity));
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}



}
