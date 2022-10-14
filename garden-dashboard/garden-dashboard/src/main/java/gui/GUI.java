package gui;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

public class GUI extends JFrame {

	/**
	 * UID
	 */
	private static final long serialVersionUID = 2310054620902228975L;
	private final JLabel intensity;
	private final JLabel temperature;
	private final JLabel state;

	public GUI() {

		intensity = new JLabel();
		temperature = new JLabel();
		state = new JLabel();

		final JFrame frame = new JFrame();
		frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
		frame.setSize(500,500);
		frame.setTitle("Garden Dashboard");

		final JPanel panel = new JPanel();

		panel.add(intensity);
		panel.add(temperature);
		panel.add(state);

		frame.getContentPane().add(panel);

		frame.setVisible(true);
	}

	public void updateIntensity(int value) {
		SwingUtilities.invokeLater(() -> intensity.setText("Intensity: " + Integer.toString(value)));
	}

	public void updateTemperature(int value) {
		SwingUtilities.invokeLater(() -> temperature.setText("Temperature: " + Integer.toString(value)));
	}

	public void updateState(String value) {
		SwingUtilities.invokeLater(() -> state.setText("State: " + value));
	}
}
