package garden.service;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class GUI extends JFrame {
	
	private final JButton random = new JButton("Random");
	
	public GUI() {
		
		final JFrame frame = new JFrame();
		frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
		frame.setSize(450,450);
		frame.setTitle("Garden Service");
		
		final JPanel panel = new JPanel();
		
		frame.getContentPane().add(panel);
		
		panel.add(random);
		
		frame.setVisible(true);
	}

	void registerController(Controller contr) {
		random.addActionListener(contr);
	}
}
