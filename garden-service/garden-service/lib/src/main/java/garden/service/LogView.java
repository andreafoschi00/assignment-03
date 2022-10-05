package garden.service;

import java.util.Date;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.SwingUtilities;

public class LogView extends JFrame {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 7361708926641670567L;
	private JTextArea log;

	public LogView(){
		super("Log ");
		setSize(600,600);

		JPanel mainPanel = new JPanel();
		log = new JTextArea(30,40);
		log.setEditable(false);
		JScrollPane scrol = new JScrollPane(log);
		mainPanel.add(scrol);
		this.getContentPane().add(mainPanel);
		
		this.setVisible(true);
	}

	public void log(String msg){
		SwingUtilities.invokeLater(() -> {
			String date = new Date().toString();
			log.append("["+date+"] "+ msg +"\n");
		});
	}
}