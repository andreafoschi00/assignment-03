package garden.dashboard;

import gui.GUI;
import io.vertx.core.Vertx;

public class Main {

	public static void main(String[] args) {
		GUI gui = new GUI(); // Swing GUI
		Vertx vertx = Vertx.vertx();
		vertx.deployVerticle(new DataEndPointVerticle(gui));
	}
}
