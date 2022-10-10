package garden.service;

import garden.service.http.DataService;
import io.vertx.core.Vertx;

public class GardenService {

	public static void main(String[] args) {
		Vertx vertx = Vertx.vertx();
        DataService service = new DataService(8080);
        vertx.deployVerticle(service);
	}
}
