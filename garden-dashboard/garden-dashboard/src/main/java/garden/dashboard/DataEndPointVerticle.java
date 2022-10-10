package garden.dashboard;

import gui.GUI;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.client.HttpRequest;
import io.vertx.ext.web.client.WebClient;
import io.vertx.ext.web.codec.BodyCodec;

public class DataEndPointVerticle extends AbstractVerticle {

	private final GUI gui;
	private HttpRequest<JsonArray> jsonRequest;

	public DataEndPointVerticle(GUI gui) {
		this.gui = gui;
	}

	@Override
	public void start() {
		String host = "localhost";
		int port = 8080;

		this.jsonRequest = WebClient.create(vertx)
							 		.get(port, host, "/api/data")
							 		.as(BodyCodec.jsonArray());

		vertx.setPeriodic(3000, handler->fecthData());
	}

	private void fecthData() {
		this.jsonRequest.send()
						.onSuccess(result -> {
							System.out.println("GET - Status: " + result.statusCode());

							JsonArray myArray = result.body();

							if(!myArray.isEmpty()) {
								JsonObject response = myArray.getJsonObject(0);

								int intensity = response.getInteger("intensity");
								int temperature = response.getInteger("temperature");
								String state = response.getString("state");


								gui.updateIntensity(intensity);
								gui.updateTemperature(temperature);
								gui.updateState(state);
							}
						})
						.onFailure(result -> System.out.println("GET - Error: " + result.getMessage()));
	}

}
